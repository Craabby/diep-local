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

std::vector<FieldId> NameComponent::FindUpdates()
{
    std::vector<FieldId> found;
    return found;
}

uint8_t NameComponent::Nametag()
{
    return netProperties.nametag;
}

std::string NameComponent::Name()
{
    return netProperties.name;
}
