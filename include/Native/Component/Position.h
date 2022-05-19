#pragma once

#include <Native/Component/types.h>

class PositionComponent
{
    struct
    {
        uint8_t x = 0;
        uint8_t y = 0;
        uint8_t angle = 0;
        uint8_t motion = 0;
    } state;
    struct
    {
        int32_t x;
        int32_t y;
        uint32_t angle;
        uint32_t motion;
    } netProperties;

public:
    entityId entity;

    static constexpr FieldGroupId id = FieldGroupId::position;
    std::vector<std::string> fields{"x", "y", "angle", "motion"};

    PositionComponent(entityId entity);

    void Wipe();

    int32_t X();
    int32_t Y();
    uint32_t Angle();
    uint32_t Motion();

    void X(int32_t x);
    void Y(int32_t y);
    void Angle(uint32_t angle);
    void Motion(uint32_t motion);
};
