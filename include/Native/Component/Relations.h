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
    } values;

public:
    entityId entity;

    static constexpr FieldGroupId id = FieldGroupId::relations;
    std::vector<std::string> fields{"parent", "owner", "team"};

    RelationsComponent(entityId entity);

    void wipe();

    entityId parent();
    entityId owner();
    entityId team();

    void parent(entityId parent);
    void owner(entityId parent);
    void team(entityId parent);
};