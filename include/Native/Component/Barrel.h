#pragma once

#include <Native/Component/types.h>
#include <Const/Fields.h>

class Entity;

class BarrelComponent
{
private:
    struct
    {
        uint8_t shooting = 0;
        uint8_t reloadTime = 0;
        uint8_t trapezoidalDir = 0;
    } state;

    struct
    {
        uint32_t shooting = 0;
        float reloadTime = 15;
        float trapezoidalDir = 0;
    } netProperties;

public:
    Entity *entity;

    static constexpr FieldGroupId id = FieldGroupId::barrel;
    static inline std::array<FieldId, 3> fields = {FieldId::Shooting, FieldId::ReloadTime, FieldId::TrapezoidalDir};

    BarrelComponent(Entity *entity);

    void Wipe();
    std::vector<FieldId> FindUpdates();

    uint32_t Shooting();
    float ReloadTime();
    float TrapezoidalDir();

    void Shooting(uint32_t shooting);
    void ReloadTime(float reloadTime);
    void TrapezoidalDir(float trapezoidalDir);
};
