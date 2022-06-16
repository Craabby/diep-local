#include <Gamemodes/SandboxArena.h>

#include <entt/entity/registry.hpp>

#include <Game.h>

SandboxArena::SandboxArena(diep::server::GameServer *gameServer)
    : Entity(gameServer)
{
    std::cout << "constructor called" << std::endl;

    gameServer->AppendComponentToEntity<ArenaComponent>(this);
    gameServer->entities.registry.get<ArenaComponent>(entity).LeftX(-1250);
    gameServer->entities.registry.get<ArenaComponent>(entity).TopY(-1250);
    gameServer->entities.registry.get<ArenaComponent>(entity).RightX(1250);
    gameServer->entities.registry.get<ArenaComponent>(entity).BottomY(1250);
}
