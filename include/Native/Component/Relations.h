#pragma once

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

    RelationsComponent(Entity *entity);

    void Wipe();

    Entity *Parent();
    Entity *Owner();
    Entity *Team();

    void Parent(Entity *parent);
    void Owner(Entity *parent);
    void Team(Entity *parent);
};
