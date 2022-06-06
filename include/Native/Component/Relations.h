#pragma once

#include <Const/Fields.h>
#include <Native/Component/types.h>

class Entity;

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
        Entity *parent = nullptr;
        Entity *owner = nullptr;
        Entity *team = nullptr;
    } netProperties;

public:
    Entity *entity;
    bool isChild = false;

    Entity *rootParent = entity;
    std::vector<Entity *> children;

    static constexpr FieldGroupId id = FieldGroupId::relations;
    static inline std::array<FieldId, 3> fields = {FieldId::Parent, FieldId::Owner, FieldId::Team};

    RelationsComponent(Entity *entity);

    void Wipe();
    std::vector<FieldId> FindUpdates();

    Entity *Parent();
    Entity *Owner();
    Entity *Team();

    void Parent(Entity *parent);
    void Owner(Entity *parent);
    void Team(Entity *parent);
};
