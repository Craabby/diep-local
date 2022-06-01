#include <Native/Camera.h>

#include <Coder/Writer.h>
#include <Const/Fields.h>
#include <Game.h>
#include <Native/Entity.h>

CameraEntity::CameraEntity(diep::server::GameServer *gameServer)
    : Entity(gameServer)
{
}

void Camera::AddToView(Entity *entity)
{
    view.push_back(entity);
}

void Camera::RemoveFromView(entityId id)
{
    view.vector::erase(std::find_if(view.begin(), view.end(), [id](Entity *entity)
                                    { return entity->id == id; }));
}

void Camera::UpdateView(uint32_t tick)
{
    diep::coder::writer::Writer *writer = diep::coder::writer::Writer().Vu(tick);

    std::vector<Deletion> deletes = {};
    std::vector<Entity *> updates = {};
    std::vector<Entity *> creations = {};

    if (view.size() == 0)
    {
        creations.push_back(gameServer->entities.inner[0]);
        view.push_back(gameServer->entities.inner[0]);
        creations.push_back(this);
        view.push_back(this);
    }

    CameraComponent &camera = gameServer->entities.registry.get<CameraComponent>(entity);
    float fov = camera.Fov();
    float width = 1200 / fov;
    float height = 800 / fov;

    std::vector<Entity *> entitiesNearRange = gameServer->entities.collisionManager.Retrieve(
        camera.CameraX(), camera.CameraY(), width, height);
    std::vector<Entity *> entitiesInRange = {};

    float l = camera.CameraX() - width;
    float r = camera.CameraX() + width;
    float t = camera.CameraY() - height;
    float b = camera.CameraY() + height;

    for (size_t i = 0; i < entitiesNearRange.size(); i++)
    {
        Entity *entity = entitiesNearRange.at(i);
        PhysicsComponent &physics = gameServer->entities.registry.get<PhysicsComponent>(entity->entity);
        PositionComponent &position = gameServer->entities.registry.get<PositionComponent>(entity->entity);
        float width = physics.Sides() == 2 ? physics.Width() / 2 : physics.Size();
        float size = physics.Sides() == 2 ? physics.Size() / 2 : physics.Size();

        if (position.X() + width < r &&
            position.Y() - size > t &&
            position.X() - width > l &&
            position.Y() + size < b)
        {
            StyleComponent &style = gameServer->entities.registry.get<StyleComponent>(entity->entity);
            if (entity != camera.Player() && !(style.Opacity() == 0))
            {
                entitiesInRange.push_back(entity);
            }
        }
    }

    for (entityId id = 0; id < gameServer->entities.lastId; id++)
    {
        Entity *entity = gameServer->entities.inner[id];
        if (entity == nullptr)
            continue;
        if (!gameServer->entities.registry.all_of<PhysicsComponent>(entity->entity))
            continue;
        PhysicsComponent &physics = gameServer->entities.registry.get<PhysicsComponent>(entity->entity);
        if (physics.ObjectFlags() & 2)
            entitiesInRange.push_back(entity);
    }

    if (camera.Player() != nullptr)
    {
        entitiesInRange.push_back(camera.Player());
    }

    for (size_t i = 0; i < view.size(); i++)
    {
        Entity *entity = view[i];

        if (gameServer->entities.registry.all_of<RelationsComponent>(entity->entity))
        {
            RelationsComponent &relations = gameServer->entities.registry.get<RelationsComponent>(entity->entity);
            if (std::find(entitiesInRange.begin(), entitiesInRange.end(), relations.rootParent) == entitiesInRange.end())
            {
                deletes.emplace_back(Deletion{entity->id, entity->preservedHash});
                continue;
            }
        }

        if (entity->hash == 0)
        {
            deletes.emplace_back(Deletion{entity->id, entity->preservedHash});
        }
        else if (entity->state & 2)
        {
            if (entity->state & 4)
                deletes.emplace_back(Deletion{entity->id, entity->preservedHash, true});

            creations.push_back(entity);
        }
        else if (entity->state & 1)
        {
            updates.push_back(entity);
        }
    }

    writer->Vu((uint32_t)deletes.size());
    for (size_t i = 0; i < deletes.size(); i++)
    {
        Deletion &deletion = deletes.at(i);
        writer->EntityId(deletion.id, deletion.hash);
        if (!deletion.noDelete)
            RemoveFromView(deletion.id);
    }

    EntityManager &entities = gameServer->entities;
    for (size_t i = 0; i < entities.otherEntities.size(); i++)
    {
        entityId id = entities.otherEntities.at(i);
        if (std::find_if(view.begin(), view.end(), [id](Entity *entity)
                         { return entity->id == id; }) == view.end())
        {
            Entity *entity = entities.inner[id];
            if (entity == nullptr)
                continue;
            if (entities.registry.any_of<CameraComponent>(entity->entity))
                continue;

            creations.push_back(entity);
            AddToView(entity);
        }
    }

    for (Entity *entity : entitiesInRange)
    {
        if (std::find(view.begin(), view.end(), entity) == view.end())
        {
            creations.push_back(entity);
            AddToView(entity);

            if (entities.registry.any_of<RelationsComponent>(entity->entity))
            {
                RelationsComponent &relations = entities.registry.get<RelationsComponent>(entity->entity);
                if (!relations.isChild)
                {
                    for (Entity *child : relations.children)
                    {
                        view.push_back(child);
                        creations.push_back(child);
                    }
                }
            }
        }
        else
        {
            if (entities.registry.any_of<RelationsComponent>(entity->entity))
            {
                RelationsComponent &relations = entities.registry.get<RelationsComponent>(entity->entity);
                if (!relations.isChild)
                {
                    for (Entity *entity : relations.children)
                    {
                        if (std::find(view.begin(), view.end(), entity) == view.end())
                        {

                            if (entities.registry.any_of<RelationsComponent>(entity->entity))
                            {
                                RelationsComponent &relations = entities.registry.get<RelationsComponent>(entity->entity);
                                for (Entity *child : relations.children)
                                {
                                    view.push_back(child);
                                    creations.push_back(child);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    writer->Vu((uint32_t)(creations.size() + updates.size()));
    for (size_t i = 0; i < updates.size(); i++)
        CompileUpdate(writer, updates.at(i));
    for (size_t i = 0; i < creations.size(); i++)
        CompileCreation(writer, creations.at(i));

    client->Send(std::move(*writer));
}

void Camera::CompileCreation(diep::coder::writer::Writer *writer, Entity *entity)
{
    writer->EntityId(entity->id, entity->hash);

    int8_t at = -1;
    for (FieldGroupId id : entity->fieldGroups)
    {
        int8_t componentId = (int8_t)id;

        writer->U8((uint8_t)((componentId - at) ^ 1));
        at = componentId;
    }

    writer->U8(0 ^ 1); // null terminate components
}

uint32_t Camera::CalculateStatCount(int32_t level)
{
    if (level <= 0)
        return 0;
    if (level <= 28)
        return level - 1;

    return level / 3 + 18;
}