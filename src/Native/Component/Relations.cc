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

std::vector<FieldId> RelationsComponent::FindUpdates()
{
    std::vector<FieldId> found;
    if (state.parent != 0)
        found.push_back(FieldId::Parent);
    if (state.owner != 0)
        found.push_back(FieldId::Owner);
    if (state.team != 0)
        found.push_back(FieldId::Team);

    return found;
}

void RelationsComponent::Owner(Entity *x)
{
    if (Owner() == x)
        return;
    
    state.owner |= 1;
    entity->state |= 1;
    netProperties.owner = x;
}

void RelationsComponent::Parent(Entity *x)
{
    if (Parent() == x)
        return;
    
    state.parent |= 1;
    entity->state |= 1;
    netProperties.parent = x;
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
