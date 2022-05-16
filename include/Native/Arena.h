#pragma once

#include <entt/entity/registry.hpp>

#include <Native/EntityFactory.h>

namespace diep::server
{
    class GameServer;
}

class ArenaEntity
{
public:
    ArenaEntity(diep::server::GameServer *gameServer);
};
