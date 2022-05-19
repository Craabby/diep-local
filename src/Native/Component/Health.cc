#include <Native/Component/Health.h>

HealthComponent::HealthComponent(entityId entity)
    : entity(entity)
{
}

void HealthComponent::Wipe()
{
    state.healthbar = 0;
    state.health = 0;
    state.maxHealth = 0;
}
