#pragma once

#include <Native/Component/types.h>

class RelationsComponent
{
    struct
    {
        uint8_t parent = 0;
        uint8_t owner = 0;
        uint8_t team = 0;
    } state;

    struct
    {
        entityId parent = -1;
        entityId owner = -1;
        entityId team = -1;
    } netProperties;

public:
    entityId entity;
    bool isChild = false;

    static constexpr FieldGroupId id = FieldGroupId::relations;
    std::vector<std::string> fields{"parent", "owner", "team"};

    RelationsComponent(entityId entity);

    void Wipe();

    entityId Parent();
    entityId Owner();
    entityId Team();

    void Parent(entityId parent);
    void Owner(entityId parent);
    void Team(entityId parent);
};
