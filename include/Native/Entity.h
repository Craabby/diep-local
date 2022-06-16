#pragma once

#include <entt/entity/registry.hpp>

#include <Native/Component/types.h>
#include <Native/Entity.h>

namespace diep::server
{
    class GameServer;
}

using entityId = int16_t;

class Entity
{
public:
    uint8_t state = 1;
    std::vector<FieldGroupId> fieldGroups{};
    diep::server::GameServer *gameServer;
    entt::entity entity;
    entityId id = -1;
    entityId hash = 0;
    entityId preservedHash = 0;
    bool isViewed = false;

    Entity(diep::server::GameServer *gameServer);
    ~Entity();

    void Insert();
    void WipeState();
    void Tick(uint32_t tick);
};