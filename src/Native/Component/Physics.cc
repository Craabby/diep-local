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

std::vector<FieldId> PhysicsComponent::FindUpdates()
{
    std::vector<FieldId> found;
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
