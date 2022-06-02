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

uint8_t ExampleComponent::Unknown()
{
    return netProperties.unknown;
}
