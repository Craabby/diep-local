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

std::vector<FieldId> HealthComponent::FindUpdates()
{
    std::vector<FieldId> found;

    if (state.healthbar != 0)
        found.push_back(FieldId::Healthbar);
    if (state.health != 0)
        found.push_back(FieldId::Health);
    if (state.maxHealth != 0)
        found.push_back(FieldId::MaxHealth);

    return found;
}

uint32_t HealthComponent::Healthbar()
{
    return netProperties.healthbar;
}

float HealthComponent::Health()
{
    return netProperties.health;
}

float HealthComponent::MaxHealth()
{
    return netProperties.maxHealth;
}
