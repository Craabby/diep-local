#pragma once

#include <Native/Component/types.h>

class PositionComponent
{
    struct
    {
        uint8_t x;
        uint8_t y;
        uint8_t angle;
        uint8_t motion;
    } state;
    struct
    {
        int32_t x;
        int32_t y;
        uint32_t angle;
        uint32_t motion;
    } values;

public:
    entityId entity;

    static constexpr FieldGroupId id = FieldGroupId::position;
    std::vector<std::string> fields{"x", "y", "angle", "motion"};

    PositionComponent(entityId entity);

    void wipe();

    int32_t x();
    int32_t y();
    uint32_t angle();
    uint32_t motion();

    void x(int32_t x);
    void y(int32_t y);
    void angle(uint32_t angle);
    void motion(uint32_t motion);
};
