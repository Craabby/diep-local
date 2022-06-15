#include <Native/Component/Physics.h>

#include <Native/Entity.h>

PhysicsComponent::PhysicsComponent(Entity *entity)
    : entity(entity)
{
}

void PhysicsComponent::ApplyPhysics()
{
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
