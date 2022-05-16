#include <Native/Entity.h>

#include <entt/entity/registry.hpp>

#include <Game.h>

Entity::Entity(diep::server::GameServer *gameServer)
    : gameServer(gameServer),
      entity(gameServer->entities.registry.create())
{
}

void Entity::Insert()
{
    if (gameServer->entities.registry.any_of<ArenaComponent>(entity))
        std::cout << " inserting arena" << std::endl;
    gameServer->entities.Add(this);
}
