#include <Native/Component/Example.h>

ExampleComponent::ExampleComponent(entityId entity)
    : entity(entity)
{
}

void ExampleComponent::Wipe()
{
    state.unknown = 0;
}
