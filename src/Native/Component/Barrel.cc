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

std::vector<FieldId> BarrelComponent::FindUpdates()
{
    std::vector<FieldId> found;
    return found;
}

uint32_t BarrelComponent::Shooting()
{
    return netProperties.shooting;
}

float BarrelComponent::ReloadTime()
{
    return netProperties.reloadTime;
}

float BarrelComponent::TrapezoidalDir()
{
    return netProperties.trapezoidalDir;
}
