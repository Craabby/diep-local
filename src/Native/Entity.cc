#include <Native/Entity.h>

#include <entt/entity/registry.hpp>

#include <Game.h>

Entity::Entity(diep::server::GameServer *gameServer)
    : gameServer(gameServer),
      entity(gameServer->entities.registry.create())
{
    gameServer->entities.Add(this);
}
