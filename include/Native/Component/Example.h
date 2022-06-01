#pragma once

#include <Native/Component/types.h>
#include <Const/Fields.h>

class Entity;

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
    Entity *entity;

    static constexpr FieldGroupId id = FieldGroupId::unused0;
    static inline std::array<FieldId, 1> fields = {FieldId::Unknown};

    ExampleComponent(Entity *entity);

    void Wipe();

    uint8_t Unknown();

    void Unknown(uint8_t unknown);
};
