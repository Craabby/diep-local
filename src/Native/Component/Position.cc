#include <Native/Component/Position.h>

#include <Native/Entity.h>

PositionComponent::PositionComponent(Entity *entity)
    : entity(entity)
{
}

void PositionComponent::Wipe()
{
    state.x = 0;
    state.y = 0;
    state.angle = 0;
    state.motion = 0;
}

int32_t PositionComponent::X()
{
    return netProperties.x;
}

int32_t PositionComponent::Y()
{
    return netProperties.y;
}

float PositionComponent::Angle()
{
    return netProperties.angle;
}

uint32_t PositionComponent::Motion()
{
    return netProperties.motion;
}
