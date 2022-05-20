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

float PhysicsComponent::Width()
{
    return netProperties.width;
}

float PhysicsComponent::Size()
{
    return netProperties.size;
}

uint32_t PhysicsComponent::Sides()
{
    return netProperties.sides;
}
