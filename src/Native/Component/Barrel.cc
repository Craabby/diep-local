#include <Native/Component/Barrel.h>

#include <Native/Entity.h>

BarrelComponent::BarrelComponent(Entity *entity)
    : entity(entity)
{
}

void BarrelComponent::Wipe()
{
    state.shooting = 0;
    state.reloadTime = 0;
    state.trapezoidalDir = 0;
}

