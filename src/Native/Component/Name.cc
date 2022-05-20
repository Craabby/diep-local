#include <Native/Component/Name.h>

#include <Native/Entity.h>

NameComponent::NameComponent(Entity *entity)
    : entity(entity)
{
}

void NameComponent::Wipe()
{
    state.name = 0;
    state.nametag = 0;
}
