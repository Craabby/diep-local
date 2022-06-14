#include <Gamemodes/SandboxArena.h>

#include <entt/entity/registry.hpp>

#include <Game.h>

SandboxArena::SandboxArena(diep::server::GameServer *gameServer)
    : Entity(gameServer)
{
    std::cout << "constructor called" << std::endl;

    gameServer->AppendComponentToEntity<ArenaComponent>(this);
    // gameServer->AppendComponentToEntity<TeamComponent>(this);
}
