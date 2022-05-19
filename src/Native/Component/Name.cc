#include <Native/Component/Name.h>

NameComponent::NameComponent(entityId entity)
    : entity(entity)
{
}

void NameComponent::Wipe()
{
    state.name = 0;
    state.nametag = 0;
}
