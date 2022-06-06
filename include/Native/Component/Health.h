#pragma once

#include <Native/Component/types.h>
#include <Const/Fields.h>

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
    static inline std::array<FieldId, 3> fields = {FieldId::Healthbar, FieldId::Health, FieldId::MaxHealth};

    HealthComponent(Entity *entity);

    void Wipe();
    std::vector<FieldId> FindUpdates();

    uint32_t Healthbar();
    float Health();
    float MaxHealth();

    void Healthbar(uint32_t healthbar);
    void Health(float health);
    void MaxHealth(float maxHealth);
};
