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

std::vector<FieldId> PositionComponent::FindUpdates()
{
    std::vector<FieldId> found;

    if (state.x != 0)
        found.push_back(FieldId::X);
    if (state.y != 0)
        found.push_back(FieldId::Y);
    if (state.angle != 0)
        found.push_back(FieldId::Angle);
    if (state.motion != 0)
        found.push_back(FieldId::Motion);

    return found;
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
