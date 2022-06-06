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

std::vector<FieldId> StyleComponent::FindUpdates()
{
    std::vector<FieldId> found;
    return found;
}

float StyleComponent::StyleFlags()
{
    return netProperties.styleFlags;
}

ColorId StyleComponent::Color()
{
    return netProperties.color;
}

int32_t StyleComponent::BorderThickness()
{
    return netProperties.borderThickness;
}

float StyleComponent::Opacity()
{
    return netProperties.opacity;
}

uint32_t StyleComponent::Zindex()
{
    return netProperties.zIndex;
}
