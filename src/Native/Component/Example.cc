#include <Native/Component/Example.h>

#include <Native/Entity.h>

ExampleComponent::ExampleComponent(Entity *entity)
    : entity(entity)
{
}

void ExampleComponent::Wipe()
{
    state.unknown = 0;
}

std::vector<FieldId> ExampleComponent::FindUpdates()
{
    std::vector<FieldId> found;
    return found;
}

uint8_t ExampleComponent::Unknown()
{
    return netProperties.unknown;
}
