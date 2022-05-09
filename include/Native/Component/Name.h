#pragma once

#include <Native/Component/types.h>

class NameComponent
{
    struct
    {
        uint8_t nametag = 0;
        uint8_t name = 0;
    } state;
    struct
    {
        uint32_t nametag = 0;
        std::string name;
    } values;

public:
    entityId entity;

    static constexpr FieldGroupId id = FieldGroupId::name;
    std::vector<std::string> fields{"nametag", "name"};

    NameComponent(entityId entity);

    void Wipe();

    uint8_t Nametag();
    std::string Name();

    void Nametag(uint8_t nametag);
    void Name(std::string name);
};
