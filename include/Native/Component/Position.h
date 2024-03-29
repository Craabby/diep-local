#pragma once

#include <Const/Fields.h>
#include <Native/Component/types.h>
#include <Physics/Vector.h>

class Entity;

class PositionComponent
{
    struct
    {
        uint8_t x = 1;
        uint8_t y = 1;
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

    Vector<float> position;
    Vector<float> velocity;

    static constexpr FieldGroupId id = FieldGroupId::position;
    static inline std::array<FieldId, 4> fields = {FieldId::X, FieldId::Y, FieldId::Angle, FieldId::Motion};

    PositionComponent(Entity *entity);

    void Wipe();
    std::vector<FieldId> FindUpdates();

    int32_t X();
    int32_t Y();
    float Angle();
    uint32_t Motion();

    void Angle(float angle);
    void Motion(uint32_t motion);

    void SetPosition(const Vector<int32_t> &position);
    void Tick(uint32_t tick);
};
