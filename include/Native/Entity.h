#pragma once

#include <entt/entity/registry.hpp>

#include <Native/Component/types.h>

using entityId = int16_t;

enum class EntityStateFlags
{
    needsUpdate = 1 << 0,
    needsCreate = 1 << 1,
    needsDelete = 1 << 2,
};

class Entity
{
public:
    EntityStateFlags state = EntityStateFlags::needsCreate;
    std::vector<FieldGroupId> fieldGroups{};
    entt::registry *registry;
    entt::entity entity;
    entityId id = -1;

    Entity(entt::registry *registry);
};
