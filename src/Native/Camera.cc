#include <Native/Camera.h>

#include <Coder/Writer.h>
#include <Const/Fields.h>
#include <Game.h>
#include <Native/Entity.h>

template <class Component>
void AddComponentFieldsToEntity(std::vector<FieldId> &vector)
{
    for (FieldId id : Component::fields)
        vector.push_back(id);
}

CameraEntity::CameraEntity(diep::server::GameServer *gameServer)
    : Entity(gameServer)
{
}

CameraEntity::~CameraEntity()
{
    CameraComponent &camera = gameServer->entities.registry.get<CameraComponent>(entity);

    if (camera.Player() != nullptr)
        delete camera.Player();
}

Camera::Camera(diep::server::client::Client *client)
    : CameraEntity(client->gameServer),
      client(client)
{
    isClientCamera = true;
    std::cout << "Camera::Camera()" << std::endl;
}

void CameraEntity::Tick(uint32_t tick)
{
}

void Camera::AddToView(Entity *entity)
{
    view.push_back(entity);
}

void Camera::RemoveFromView(entityId id)
{
    auto entityIterator = std::find_if(view.begin(), view.end(), [id](Entity *entity)
                                       { return entity->id == id; });
    if (entityIterator != view.end())
        view.erase(entityIterator);
    else
        std::cout << "removed nonexistant entity id " << std::to_string(id) << " from view" << std::endl;
}

void Camera::UpdateView(uint32_t tick)
{
    diep::coder::writer::Writer *writer = diep::coder::writer::Writer().Vu(0)->Vu(tick);

    std::vector<Deletion> deletes = {};
    std::vector<Entity *> updates = {};
    std::vector<Entity *> creations = {};

    std::vector<Entity *> entitiesInView{};

    for (size_t i = 0; i < 16384; i++)
        if (gameServer->entities.inner[i] != nullptr)
            if (!gameServer->entities.registry.all_of<CameraComponent>(gameServer->entities.inner[i]->entity) || gameServer->entities.inner[i] == this)
                entitiesInView.push_back(gameServer->entities.inner[i]);

    for (Entity *entity : view)
        if (std::find(entitiesInView.begin(), entitiesInView.end(), entity) == entitiesInView.end())
        {
            view.erase(std::find(view.begin(), view.end(), entity));
            deletes.push_back(Deletion{entity->id, entity->hash});
        }

    for (Entity *entity : entitiesInView)
    {
        bool isCreation = std::find(view.begin(), view.end(), entity) == view.end();

        if (isCreation)
        {
            creations.push_back(entity);
            view.push_back(entity);
        }
        else
            updates.push_back(entity);
    }

    writer->Vu((uint32_t)deletes.size());
    for (size_t i = 0; i < deletes.size(); i++)
    {
        Deletion &deletion = deletes.at(i);
        writer->EntityId(deletion.id, deletion.hash);
        if (!deletion.noDelete)
            RemoveFromView(deletion.id);
    }

    writer->Vu((uint32_t)(creations.size() + updates.size()));
    for (size_t i = 0; i < updates.size(); i++)
        CompileUpdate(writer, updates.at(i));
    for (size_t i = 0; i < creations.size(); i++)
        CompileCreation(writer, creations.at(i));

    client->Send(*writer);
}

void Camera::CompileCreation(diep::coder::writer::Writer *writer, Entity *entity)
{
    writer->EntityId(entity->id, entity->hash);
    writer->U8(1);

    int8_t at = -1;
    for (FieldGroupId id : entity->fieldGroups)
    {
        int8_t componentId = (int8_t)id;

        writer->U8((uint8_t)((componentId - at) ^ 1));
        at = componentId;
    }

    writer->U8(0 ^ 1); // null terminate components

    std::vector<FieldId> fields;
    for (FieldGroupId id : entity->fieldGroups)
    {
#define ADD_COMPONENT_FIELDS_TO_ENTITY(enumeration, component) \
    if (id == enumeration)                                     \
        AddComponentFieldsToEntity<component>(fields);

        ADD_COMPONENT_FIELDS_TO_ENTITY(FieldGroupId::arena, ArenaComponent);
        ADD_COMPONENT_FIELDS_TO_ENTITY(FieldGroupId::barrel, BarrelComponent);
        ADD_COMPONENT_FIELDS_TO_ENTITY(FieldGroupId::camera, CameraComponent);
        ADD_COMPONENT_FIELDS_TO_ENTITY(FieldGroupId::health, HealthComponent);
        ADD_COMPONENT_FIELDS_TO_ENTITY(FieldGroupId::name, NameComponent);
        ADD_COMPONENT_FIELDS_TO_ENTITY(FieldGroupId::physics, PhysicsComponent);
        ADD_COMPONENT_FIELDS_TO_ENTITY(FieldGroupId::position, PositionComponent);
        ADD_COMPONENT_FIELDS_TO_ENTITY(FieldGroupId::relations, RelationsComponent);
        ADD_COMPONENT_FIELDS_TO_ENTITY(FieldGroupId::score, ScoreComponent);
        ADD_COMPONENT_FIELDS_TO_ENTITY(FieldGroupId::style, StyleComponent);
        ADD_COMPONENT_FIELDS_TO_ENTITY(FieldGroupId::team, TeamComponent);

#undef ADD_COMPONENT_FIELDS_TO_ENTITY
    }

    std::sort(fields.begin(), fields.end());

    for (FieldId id : fields)
    {
        FieldDefinition &fieldDefinition = GetFieldList()[(size_t)id];
#define SEND_FIELD(fieldName, Component, encodingType) \
    if (id == FieldId::fieldName)                      \
        writer->encodingType(gameServer->entities.registry.get<Component>(entity->entity).fieldName());

        SEND_FIELD(Y, PositionComponent, Vi)
        SEND_FIELD(X, PositionComponent, Vi)
        SEND_FIELD(Angle, PositionComponent, Radians)
        SEND_FIELD(Size, PhysicsComponent, Float)
        SEND_FIELD(Player, CameraComponent, EntityId)
        SEND_FIELD(Gui, ArenaComponent, Vu)
        SEND_FIELD(Color, StyleComponent, Vu)
        SEND_FIELD(KilledBy, CameraComponent, StringNT)
        SEND_FIELD(PlayersNeeded, ArenaComponent, Vi)
        SEND_FIELD(Sides, PhysicsComponent, Vu)
        SEND_FIELD(Mothership, TeamComponent, Vu)
        SEND_FIELD(Healthbar, HealthComponent, Vu)
        SEND_FIELD(RespawnLevel, CameraComponent, Vi)
        SEND_FIELD(LevelbarProgress, CameraComponent, Float)
        SEND_FIELD(SpawnTick, CameraComponent, Vi)
        SEND_FIELD(AbsorbtionFactor, PhysicsComponent, Float)
        SEND_FIELD(LeaderX, ArenaComponent, Float)
        SEND_FIELD(MaxHealth, HealthComponent, Float)
        SEND_FIELD(StyleFlags, StyleComponent, Vu)
        SEND_FIELD(TrapezoidalDir, BarrelComponent, Float)
        SEND_FIELD(Motion, PositionComponent, Vu)
        SEND_FIELD(Scorebar, CameraComponent, Float)
        SEND_FIELD(MothershipY, TeamComponent, Float)
        SEND_FIELD(Nametag, NameComponent, Vu)
        SEND_FIELD(MovementSpeed, CameraComponent, Float)
        SEND_FIELD(LeaderY, ArenaComponent, Float)
        SEND_FIELD(BottomY, ArenaComponent, Float)
        SEND_FIELD(Team, RelationsComponent, EntityId)
        SEND_FIELD(Level, CameraComponent, Vi)
        SEND_FIELD(TeamColor, TeamComponent, Vu)
        SEND_FIELD(Fov, CameraComponent, Float)
        SEND_FIELD(LeftX, ArenaComponent, Float)
        SEND_FIELD(TankOverride, CameraComponent, StringNT)
        SEND_FIELD(Tank, CameraComponent, Vi)
        SEND_FIELD(BorderThickness, StyleComponent, Vi)
        SEND_FIELD(DeathTick, CameraComponent, Vi)
        SEND_FIELD(Width, PhysicsComponent, Float)
        SEND_FIELD(StatsAvailable, CameraComponent, Vi)
        SEND_FIELD(Shooting, BarrelComponent, Vu)
        SEND_FIELD(LevelbarMax, CameraComponent, Float)
        SEND_FIELD(Name, NameComponent, StringNT)
        SEND_FIELD(Owner, RelationsComponent, EntityId)
        SEND_FIELD(Health, HealthComponent, Float)
        SEND_FIELD(CameraY, CameraComponent, Float)
        SEND_FIELD(Opacity, StyleComponent, Float)
        SEND_FIELD(ReloadTime, BarrelComponent, Float)
        SEND_FIELD(CameraX, CameraComponent, Float)
        SEND_FIELD(MothershipX, TeamComponent, Float)
        SEND_FIELD(GuiUnknown, CameraComponent, Vu)
        SEND_FIELD(Parent, RelationsComponent, EntityId)
        SEND_FIELD(Zindex, StyleComponent, Vu)
        SEND_FIELD(Camera, CameraComponent, Vu)
        SEND_FIELD(RightX, ArenaComponent, Float)
        SEND_FIELD(PushFactor, PhysicsComponent, Float)
        SEND_FIELD(ObjectFlags, PhysicsComponent, Vu)
        SEND_FIELD(ScoreboardAmount, ArenaComponent, Vu)
        SEND_FIELD(TicksUntilStart, ArenaComponent, Float)
        SEND_FIELD(TopY, ArenaComponent, Float)
        SEND_FIELD(Score, ScoreComponent, Float)
        if (id == FieldId::StatNames)
            for (uint8_t i = 0; i < GetFieldList()[(size_t)FieldId::StatNames].amount; i++)
                writer->StringNT(gameServer->entities.registry.get<CameraComponent>(entity->entity).StatNames()->At(i));
        if (id == FieldId::ScoreboardTanks)
            for (uint8_t i = 0; i < GetFieldList()[static_cast<size_t>(FieldId::ScoreboardTanks)].amount; i++)
                writer->Vi(gameServer->entities.registry.get<ArenaComponent>(gameServer->entities.inner[0]->entity).ScoreboardTanks()->At(i));
        if (id == FieldId::ScoreboardNames)
            for (uint8_t i = 0; i < GetFieldList()[static_cast<size_t>(FieldId::ScoreboardNames)].amount; i++)
                writer->StringNT(gameServer->entities.registry.get<ArenaComponent>(gameServer->entities.inner[0]->entity).ScoreboardNames()->At(i));
        if (id == FieldId::ScoreboardSuffixes)
            for (uint8_t i = 0; i < GetFieldList()[static_cast<size_t>(FieldId::ScoreboardSuffixes)].amount; i++)
                writer->StringNT(gameServer->entities.registry.get<ArenaComponent>(gameServer->entities.inner[0]->entity).ScoreboardSuffixes()->At(i));
        if (id == FieldId::StatLimits)
            for (uint8_t i = 0; i < GetFieldList()[static_cast<size_t>(FieldId::StatLimits)].amount; i++)
                writer->Vi(gameServer->entities.registry.get<CameraComponent>(entity->entity).StatLimits()->At(i));
        if (id == FieldId::ScoreboardScores)
            for (uint8_t i = 0; i < GetFieldList()[static_cast<size_t>(FieldId::ScoreboardScores)].amount; i++)
                writer->Float(gameServer->entities.registry.get<ArenaComponent>(entity->entity).ScoreboardScores()->At(i));
        if (id == FieldId::StatLevels)
            for (uint8_t i = 0; i < GetFieldList()[static_cast<size_t>(FieldId::StatLevels)].amount; i++)
                writer->Vi(gameServer->entities.registry.get<CameraComponent>(entity->entity).StatLevels()->At(i));
        if (id == FieldId::ScoreboardColors)
            for (uint8_t i = 0; i < GetFieldList()[static_cast<size_t>(FieldId::ScoreboardColors)].amount; i++)
                writer->Vu(gameServer->entities.registry.get<ArenaComponent>(entity->entity).ScoreboardColors()->At(i));

#undef SEND_FIELD
    }
}

void Camera::CompileUpdate(diep::coder::writer::Writer *writer, Entity *entity)
{
    writer->EntityId(entity);
    writer->U8(0);
    writer->U8(1);

    std::vector<FieldId> updatedFields;

#define ADD_UPDATED_FIELDS_FROM_COMPONENT(ComponentEnumValue, Component)                                                                       \
    if (entity->gameServer->entities.registry.all_of<Component>(entity->entity))                                                               \
    {                                                                                                                                          \
        std::vector<FieldId> updated##ComponentEnumValue = entity->gameServer->entities.registry.get<Component>(entity->entity).FindUpdates(); \
        for (FieldId updatedField : updated##ComponentEnumValue)                                                                               \
            updatedFields.push_back(updatedField);                                                                                             \
    }

    ADD_UPDATED_FIELDS_FROM_COMPONENT(relations, RelationsComponent);
    ADD_UPDATED_FIELDS_FROM_COMPONENT(barrel, BarrelComponent);
    ADD_UPDATED_FIELDS_FROM_COMPONENT(physics, PhysicsComponent);
    ADD_UPDATED_FIELDS_FROM_COMPONENT(health, HealthComponent);
    ADD_UPDATED_FIELDS_FROM_COMPONENT(arena, ArenaComponent);
    ADD_UPDATED_FIELDS_FROM_COMPONENT(name, NameComponent);
    ADD_UPDATED_FIELDS_FROM_COMPONENT(camera, CameraComponent);
    ADD_UPDATED_FIELDS_FROM_COMPONENT(position, PositionComponent);
    ADD_UPDATED_FIELDS_FROM_COMPONENT(style, StyleComponent);
    ADD_UPDATED_FIELDS_FROM_COMPONENT(score, ScoreComponent);
    ADD_UPDATED_FIELDS_FROM_COMPONENT(team, TeamComponent);

#undef ADD_UPDATED_FIELDS_FROM_COMPONENT

    std::sort(updatedFields.begin(), updatedFields.end());

    int8_t at = -1;
    for (size_t i = 0; i < static_cast<size_t>(FieldId::kMaxFieldId); i++)
    {
        FieldDefinition &field = GetFieldList()[i];
        FieldId fieldId = static_cast<FieldId>(i);

        bool updated = (std::find_if(updatedFields.begin(), updatedFields.end(), [i](FieldId x)
                                     { return static_cast<uint8_t>(x) == GetFieldList()[i].index; }) != updatedFields.end());

        if (!updated)
            continue;

        writer->U8((field.index - at) ^ 1);
        at = field.index;

#define SEND_FIELD(fieldName, Component, encodingType) \
    if (fieldId == FieldId::fieldName)                 \
        writer->encodingType(gameServer->entities.registry.get<Component>(entity->entity).fieldName());

#define SEND_FIELD_AMOUNT(fieldName, Component, EncodingType, amount)                                                           \
    if (fieldId == FieldId::fieldName)                                                                                          \
    {                                                                                                                           \
        int8_t at = -1;                                                                                                         \
        std::vector<uint8_t> updates = gameServer->entities.registry.get<Component>(entity->entity).fieldName()->FindUpdates(); \
        for (uint8_t updated : updates)                                                                                         \
        {                                                                                                                       \
            writer->U8((updated - at) ^ 1);                                                                                     \
            at = updated;                                                                                                       \
            writer->EncodingType(gameServer->entities.registry.get<Component>(entity->entity).fieldName()->At(i));              \
        }                                                                                                                       \
        writer->U8(1);                                                                                                          \
    }

        SEND_FIELD(Y, PositionComponent, Vi)
        SEND_FIELD(X, PositionComponent, Vi)
        SEND_FIELD(Angle, PositionComponent, Radians)
        SEND_FIELD(Size, PhysicsComponent, Float)
        SEND_FIELD(Player, CameraComponent, EntityId)
        SEND_FIELD(Gui, ArenaComponent, Vu)
        SEND_FIELD(Color, StyleComponent, Vu)
        SEND_FIELD(KilledBy, CameraComponent, StringNT)
        SEND_FIELD(PlayersNeeded, ArenaComponent, Vi)
        SEND_FIELD(Sides, PhysicsComponent, Vu)
        SEND_FIELD(Mothership, TeamComponent, Vu)
        SEND_FIELD(Healthbar, HealthComponent, Vu)
        SEND_FIELD(RespawnLevel, CameraComponent, Vi)
        SEND_FIELD(LevelbarProgress, CameraComponent, Float)
        SEND_FIELD(SpawnTick, CameraComponent, Vi)
        SEND_FIELD(AbsorbtionFactor, PhysicsComponent, Float)
        SEND_FIELD(LeaderX, ArenaComponent, Float)
        SEND_FIELD(MaxHealth, HealthComponent, Float)
        SEND_FIELD(StyleFlags, StyleComponent, Vu)
        SEND_FIELD(TrapezoidalDir, BarrelComponent, Float)
        SEND_FIELD(Motion, PositionComponent, Vu)
        SEND_FIELD(Scorebar, CameraComponent, Float)
        SEND_FIELD(MothershipY, TeamComponent, Float)
        SEND_FIELD(Nametag, NameComponent, Vu)
        SEND_FIELD(MovementSpeed, CameraComponent, Float)
        SEND_FIELD(LeaderY, ArenaComponent, Float)
        SEND_FIELD(BottomY, ArenaComponent, Float)
        SEND_FIELD(Team, RelationsComponent, EntityId)
        SEND_FIELD(Level, CameraComponent, Vi)
        SEND_FIELD(TeamColor, TeamComponent, Vu)
        SEND_FIELD(Fov, CameraComponent, Float)
        SEND_FIELD(LeftX, ArenaComponent, Float)
        SEND_FIELD(TankOverride, CameraComponent, StringNT)
        SEND_FIELD(Tank, CameraComponent, Vi)
        SEND_FIELD(BorderThickness, StyleComponent, Vi)
        SEND_FIELD(DeathTick, CameraComponent, Vi)
        SEND_FIELD(Width, PhysicsComponent, Float)
        SEND_FIELD(StatsAvailable, CameraComponent, Vi)
        SEND_FIELD(Shooting, BarrelComponent, Vu)
        SEND_FIELD(LevelbarMax, CameraComponent, Float)
        SEND_FIELD(Name, NameComponent, StringNT)
        SEND_FIELD(Owner, RelationsComponent, EntityId)
        SEND_FIELD(Health, HealthComponent, Float)
        SEND_FIELD(CameraY, CameraComponent, Float)
        SEND_FIELD(Opacity, StyleComponent, Float)
        SEND_FIELD(ReloadTime, BarrelComponent, Float)
        SEND_FIELD(CameraX, CameraComponent, Float)
        SEND_FIELD(MothershipX, TeamComponent, Float)
        SEND_FIELD(GuiUnknown, CameraComponent, Vu)
        SEND_FIELD(Parent, RelationsComponent, EntityId)
        SEND_FIELD(Zindex, StyleComponent, Vu)
        SEND_FIELD(Camera, CameraComponent, Vu)
        SEND_FIELD(RightX, ArenaComponent, Float)
        SEND_FIELD(PushFactor, PhysicsComponent, Float)
        SEND_FIELD(ObjectFlags, PhysicsComponent, Vu)
        SEND_FIELD(ScoreboardAmount, ArenaComponent, Vu)
        SEND_FIELD(TicksUntilStart, ArenaComponent, Float)
        SEND_FIELD(TopY, ArenaComponent, Float)
        SEND_FIELD(Score, ScoreComponent, Float)

        SEND_FIELD_AMOUNT(StatNames, CameraComponent, StringNT, 8)
        SEND_FIELD_AMOUNT(ScoreboardTanks, ArenaComponent, Vi, 10)
        SEND_FIELD_AMOUNT(ScoreboardNames, ArenaComponent, StringNT, 10)
        SEND_FIELD_AMOUNT(ScoreboardSuffixes, ArenaComponent, StringNT, 10)
        SEND_FIELD_AMOUNT(StatLimits, CameraComponent, Vi, 8)
        SEND_FIELD_AMOUNT(ScoreboardScores, ArenaComponent, Float, 10)
        SEND_FIELD_AMOUNT(StatLevels, CameraComponent, Vi, 8)
        SEND_FIELD_AMOUNT(ScoreboardColors, ArenaComponent, Vu, 10)

#undef SEND_FIELD_AMOUNT
#undef SEND_FIELD
    }

    writer->U8(1);
}

uint32_t Camera::CalculateStatCount(int32_t level)
{
    if (level <= 0)
        return 0;
    if (level <= 28)
        return level - 1;

    return level / 3 + 18;
}

void Camera::Tick(uint32_t tick)
{
    CameraEntity::Tick(tick);

    UpdateView(tick);
}
