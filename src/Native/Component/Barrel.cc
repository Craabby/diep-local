#include <Native/Component/Barrel.h>

BarrelComponent::BarrelComponent(entityId entity)
    : entity(entity)
{
}

void BarrelComponent::Wipe()
{
    state.shooting = 0;
    state.reloadTime = 0;
    state.trapezoidalDir = 0;
}

