#pragma once

#include <Native/Component/types.h>

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
    } values;

public:
    entityId entity;

    static constexpr FieldGroupId id = FieldGroupId::barrel;
    std::vector<std::string> fields{"shooting", "reloadTime", "trapezoidalDir"};

    BarrelComponent(entityId entity);

    void wipe();

    uint32_t Shooting();
    float ReloadTime();
    float TrapezoidalDir();

    void Shooting(uint32_t shooting);
    void ReloadTime(float reloadTime);
    void TrapezoidalDir(float trapezoidalDir);
};
