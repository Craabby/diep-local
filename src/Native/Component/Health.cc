#include <Native/Component/Health.h>

#include <Native/Entity.h>

HealthComponent::HealthComponent(Entity *entity)
    : entity(entity)
{
}

void HealthComponent::Wipe()
{
    state.healthbar = 0;
    state.health = 0;
    state.maxHealth = 0;
}
