#pragma once

#include <Native/Component/types.h>

class ExampleComponent
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

    ExampleComponent(entityId entity);

    void wipe();

    uint8_t unknown();

    void unknown(uint8_t unknown);
};