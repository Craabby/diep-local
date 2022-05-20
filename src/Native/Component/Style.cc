#include <Native/Component/Style.h>

#include <Native/Entity.h>

StyleComponent::StyleComponent(Entity *entity)
    : entity(entity)
{
}

void StyleComponent::Wipe()
{
    state.styleFlags = 0;
    state.color = 0;
    state.borderThickness = 0;
    state.opacity = 0;
    state.zIndex = 0;
}
