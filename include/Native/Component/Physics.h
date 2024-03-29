#pragma once

#include <Native/Component/types.h>
#include <Const/Fields.h>

class Entity;

class PhysicsComponent
{
    struct
    {
        uint8_t objectFlags = 0;
        uint8_t sides = 0;
        uint8_t size = 0;
        uint8_t width = 0;
        uint8_t absorbtionFactor = 0;
        uint8_t pushFactor = 0;
    } state;
    struct
    {
        uint32_t objectFlags = 0;
        uint32_t sides = 0;
        float size = 0;
        float width = 0;
        float absorbtionFactor = 1;
        float pushFactor = 8;
    } netProperties;

    float m_Mass;

public:
    Entity *entity;

    static constexpr FieldGroupId id = FieldGroupId::physics;
    static inline std::array<FieldId, 6> fields = {FieldId::ObjectFlags, FieldId::Sides, FieldId::Size, FieldId::Width, FieldId::AbsorbtionFactor, FieldId::PushFactor};

    PhysicsComponent(Entity *entity);

    void Tick(uint32_t tick);

    void OnCollision(PhysicsComponent &other);

    void Wipe();
    std::vector<FieldId> FindUpdates();

    uint32_t ObjectFlags();
    uint32_t Sides();
    float Size();
    float Mass();
    float Width();
    float AbsorbtionFactor();
    float PushFactor();

    void ObjectFlags(uint32_t objectFlags);
    void Sides(uint32_t sides);
    void Size(float size);
    void Width(float width);
    void AbsorbtionFactor(float absorbtionFactor);
    void PushFactor(float pushFactor);
};
