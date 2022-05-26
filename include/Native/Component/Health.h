#pragma once

#include <Native/Component/types.h>

class Entity;

class HealthComponent
{
    struct
    {
        uint8_t healthbar = 0;
        uint8_t health = 0;
        uint8_t maxHealth = 0;
    } state;
    struct
    {
        uint32_t healthbar = 0;
        float health = 1;
        float maxHealth = 1;
    } netProperties;

public:
    Entity *entity;

    static constexpr FieldGroupId id = FieldGroupId::health;
    std::{"healthbar", "health", "maxHealth"};

    HealthComponent(Entity *entity);

    void Wipe();

    uint32_t Healthbar();
    float Health();
    float MaxHealth();

    void Healthbar(uint32_t healthbar);
    void Health(float health);
    void MaxHealth(float maxHealth);
};
