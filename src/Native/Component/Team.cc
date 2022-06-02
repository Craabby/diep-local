#include <Native/Component/Team.h>

#include <Native/Entity.h>

TeamComponent::TeamComponent(Entity *entity)
    : entity(entity)
{
}

void TeamComponent::Wipe()
{
    state.teamColor = 0;
    state.mothershipX = 0;
    state.mothershipY = 0;
    state.mothership = 0;
}

uint32_t TeamComponent::Mothership()
{
    return netProperties.mothership;
}
float TeamComponent::MothershipX()
{
    return netProperties.mothershipX;
}
float TeamComponent::MothershipY()
{
    return netProperties.mothershipY;
}
ColorId TeamComponent::TeamColor()
{
    return netProperties.teamColor;
}
