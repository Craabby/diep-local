#pragma once

#include <Native/Component/types.h>
#include <Const/Fields.h>

class Entity;

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
        float angle;
        uint32_t motion;
    } netProperties;

public:
    Entity *entity;

    static constexpr FieldGroupId id = FieldGroupId::position;
    static inline std::array<FieldId, 4> fields = {FieldId::X, FieldId::Y, FieldId::Angle, FieldId::Motion};

    PositionComponent(Entity *entity);

    void Wipe();

    int32_t X();
    int32_t Y();
    float Angle();
    uint32_t Motion();

    void X(int32_t x);
    void Y(int32_t y);
    void Angle(float angle);
    void Motion(uint32_t motion);
};
