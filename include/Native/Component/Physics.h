#pragma once

#include <Native/Component/types.h>

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
    } values;

public:
    entityId entity;

    static constexpr FieldGroupId id = FieldGroupId::physics;
    std::vector<std::string> fields{"objectFlags", "sides", "size", "width", "absorbtionFactor", "pushFactor"};

    PhysicsComponent(entityId entity);

    void wipe();

    uint32_t objectFlags();
    uint32_t sides();
    float size();
    float width();
    float absorbtionFactor();
    float pushFactor();

    void objectFlags(uint32_t objectFlags);
    void sides(uint32_t sides);
    void size(float size);
    void width(float width);
    void absorbtionFactor(float absorbtionFactor);
    void pushFactor(float pushFactor);
};
