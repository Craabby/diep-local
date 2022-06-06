#pragma once

#include <Native/Component/types.h>
#include <Const/Fields.h>

class Entity;

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
    } netProperties;

public:
    Entity *entity;

    static constexpr FieldGroupId id = FieldGroupId::name;
    static inline std::array<FieldId, 2> fields = {FieldId::Nametag, FieldId::Name};

    NameComponent(Entity *entity);

    void Wipe();
    std::vector<FieldId> FindUpdates();

    uint8_t Nametag();
    std::string Name();

    void Nametag(uint8_t nametag);
    void Name(std::string name);
};
