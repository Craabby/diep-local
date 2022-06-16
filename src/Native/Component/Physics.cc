#include <Native/Component/Physics.h>

#include <Game.h>
#include <Native/Entity.h>

PhysicsComponent::PhysicsComponent(Entity *entity)
    : entity(entity)
{
}

void PhysicsComponent::Tick(uint32_t tick)
{
    for (entityId i = 0; i < 16384; i++)
    {
        if (i == entity->id)
            continue;
        if (!entity->gameServer->entities.Exists(i))
            continue;

        Entity *entity = this->entity->gameServer->entities.inner[i];

        if (!entity->gameServer->entities.registry.all_of<PhysicsComponent>(entity->entity))
            continue;

        PositionComponent &otherPosition = entity->gameServer->entities.registry.get<PositionComponent>(entity->entity);
        PhysicsComponent &otherPhysics = entity->gameServer->entities.registry.get<PhysicsComponent>(entity->entity);
        PositionComponent &position = entity->gameServer->entities.registry.get<PositionComponent>(this->entity->entity);

        Vector<float> delta = *otherPosition.position.Clone().Subtract(position.position);

        if (delta.Distance() < Size() + otherPhysics.Size())
        {
            OnCollision(otherPhysics);
        }
    }
}

void PhysicsComponent::OnCollision(PhysicsComponent &other)
{
    std::cout << "collision lol" << std::endl;
}

void PhysicsComponent::Wipe()
{
    state.objectFlags = 0;
    state.sides = 0;
    state.size = 0;
    state.width = 0;
    state.absorbtionFactor = 0;
    state.pushFactor = 0;
}

void PhysicsComponent::Size(float x)
{
    if (Size() == x)
        return;

    state.size |= 1;
    entity->state |= 1;
    netProperties.size = x;
}

void PhysicsComponent::Sides(uint32_t x)
{
    if (Sides() == x)
        return;

    state.sides |= 1;
    entity->state |= 1;
    netProperties.sides = x;
}

std::vector<FieldId> PhysicsComponent::FindUpdates()
{
    std::vector<FieldId> found;

    if (state.objectFlags != 0)
        found.push_back(FieldId::ObjectFlags);
    if (state.sides != 0)
        found.push_back(FieldId::Sides);
    if (state.size != 0)
        found.push_back(FieldId::Size);
    if (state.width != 0)
        found.push_back(FieldId::Width);
    if (state.absorbtionFactor != 0)
        found.push_back(FieldId::AbsorbtionFactor);
    if (state.pushFactor != 0)
        found.push_back(FieldId::PushFactor);

    return found;
}

uint32_t PhysicsComponent::ObjectFlags()
{
    return netProperties.objectFlags;
}

uint32_t PhysicsComponent::Sides()
{
    return netProperties.sides;
}

float PhysicsComponent::Size()
{
    return netProperties.size;
}

float PhysicsComponent::Width()
{
    return netProperties.width;
}

float PhysicsComponent::AbsorbtionFactor()
{
    return netProperties.absorbtionFactor;
}

float PhysicsComponent::PushFactor()
{
    return netProperties.pushFactor;
}
