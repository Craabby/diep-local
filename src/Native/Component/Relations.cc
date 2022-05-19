#include <Native/Component/Relations.h>

RelationsComponent::RelationsComponent(entityId id)
    : entity(id)
{
}

void RelationsComponent::Wipe()
{
    state.parent = 0;
    state.owner = 0;
    state.team = 0;
}
