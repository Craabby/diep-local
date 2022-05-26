#pragma once

#include <Native/Component/types.h>

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

public:
    Entity *entity;

    static constexpr FieldGroupId id = FieldGroupId::physics;

    PhysicsComponent(Entity *entity);

    void ApplyPhysics();

    void Wipe();

    uint32_t ObjectFlags();
    uint32_t Sides();
    float Size();
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
