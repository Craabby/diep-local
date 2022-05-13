#pragma once

#include <entt/entity/registry.hpp>

#include <Native/EntityFactory.h>

namespace diep::server
{
    class GameServer;
}

class ArenaEntity : public Entity
{
public:
    ArenaEntity(diep::server::GameServer *gameServer);
};
