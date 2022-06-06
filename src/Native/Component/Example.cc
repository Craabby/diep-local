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

    if (state.unknown != 0)
        found.push_back(FieldId::Unknown);

    return found;
}

uint8_t ExampleComponent::Unknown()
{
    return netProperties.unknown;
}
