#pragma once

#include <entt/entity/registry.hpp>

#include <Native/Arena.h>

namespace diep::server
{
    class GameServer;
}

class SandboxArena : public ArenaEntity
{
public:
    SandboxArena(diep::server::GameServer *gameServer);
};
