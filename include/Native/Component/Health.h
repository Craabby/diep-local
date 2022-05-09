#pragma once

#include <Native/Component/types.h>

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
    } values;

public:
    entityId entity;

    static constexpr FieldGroupId id = FieldGroupId::health;
    std::vector<std::string> fields{"healthbar", "health", "maxHealth"};

    HealthComponent(entityId entity);

    void wipe();

    uint32_t healthbar();
    float health();
    float maxHealth();

    void healthbar(uint32_t healthbar);
    void health(float health);
    void maxHealth(float maxHealth);
};
