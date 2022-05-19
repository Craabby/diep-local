#pragma once

#include <entt/entity/registry.hpp>

#include <Native/Entity.h>

namespace diep::server
{
    class GameServer;
}

class SandboxArena : public Entity
{
public:
    SandboxArena(diep::server::GameServer *gameServer);
};
