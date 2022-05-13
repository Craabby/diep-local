#pragma once

#include <entt/entity/registry.hpp>

#include <Native/Component/types.h>
#include <Native/Entity.h>

namespace diep::server
{
    class GameServer;
}

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
    diep::server::GameServer *gameServer;
    entt::entity entity;
    entityId id = -1;
    uint8_t hash = 0;
    uint8_t preservedHash = 0;

    Entity(diep::server::GameServer *gameServer);
};
