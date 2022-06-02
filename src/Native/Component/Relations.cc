#include <Native/Component/Relations.h>

#include <Native/Entity.h>

RelationsComponent::RelationsComponent(Entity *entity)
    : entity(entity)
{
}

void RelationsComponent::Wipe()
{
    state.parent = 0;
    state.owner = 0;
    state.team = 0;
}

Entity *RelationsComponent::Parent()
{
    return netProperties.parent;
}

Entity *RelationsComponent::Owner()
{
    return netProperties.owner;
}

Entity *RelationsComponent::Team()
{
    return netProperties.team;
}
