#pragma once

#include <Native/Component/types.h>

class UnusedComponent
{
    struct
    {
        uint8_t unknown = 0;
    } state;
    struct
    {
        uint8_t unknown = 0;
    } values;

public:
    entityId entity;

    static constexpr FieldGroupId id = FieldGroupId::unused0;
    std::vector<std::string> fields{"unknown"};

    UnusedComponent(entityId entity);

    void wipe();

    uint8_t unknown();

    void unknown(uint8_t unknown);
};
