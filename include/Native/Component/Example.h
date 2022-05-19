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
    } netProperties;

public:
    entityId entity;

    static constexpr FieldGroupId id = FieldGroupId::unused0;
    std::vector<std::string> fields{"unknown"};

    ExampleComponent(entityId entity);

    void Wipe();

    uint8_t Unknown();

    void Unknown(uint8_t unknown);
};
