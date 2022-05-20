#include <Native/Entity.h>

#include <entt/entity/registry.hpp>

#include <Game.h>

Entity::Entity(diep::server::GameServer *gameServer)
    : gameServer(gameServer),
      entity(gameServer->entities.registry.create())
{
    std::cout << "constructing Entity at " << this << std::endl;
}

void Entity::Insert()
{
    std::cout << "inserting Entity " << this << " with components ";
    for (size_t i = 0; i < fieldGroups.size(); i++)
    {
        std::cout << std::to_string((uint8_t)fieldGroups.at(i)) << " ";
    }
    std::cout << "to EntityManager" << std::endl;
    gameServer->entities.Add(this);
}

void Entity::WipeState()
{
    if (gameServer->entities.registry.all_of<ArenaComponent>(entity))
        gameServer->entities.registry.get<ArenaComponent>(entity).Wipe();
    if (gameServer->entities.registry.all_of<BarrelComponent>(entity))
        gameServer->entities.registry.get<BarrelComponent>(entity).Wipe();
    if (gameServer->entities.registry.all_of<CameraComponent>(entity))
        gameServer->entities.registry.get<CameraComponent>(entity).Wipe();
    if (gameServer->entities.registry.all_of<ExampleComponent>(entity))
        gameServer->entities.registry.get<ExampleComponent>(entity).Wipe();
    if (gameServer->entities.registry.all_of<HealthComponent>(entity))
        gameServer->entities.registry.get<HealthComponent>(entity).Wipe();
    if (gameServer->entities.registry.all_of<NameComponent>(entity))
        gameServer->entities.registry.get<NameComponent>(entity).Wipe();
    if (gameServer->entities.registry.all_of<PhysicsComponent>(entity))
        gameServer->entities.registry.get<PhysicsComponent>(entity).Wipe();
    if (gameServer->entities.registry.all_of<PositionComponent>(entity))
        gameServer->entities.registry.get<PositionComponent>(entity).Wipe();
    if (gameServer->entities.registry.all_of<RelationsComponent>(entity))
        gameServer->entities.registry.get<RelationsComponent>(entity).Wipe();
    if (gameServer->entities.registry.all_of<ScoreComponent>(entity))
        gameServer->entities.registry.get<ScoreComponent>(entity).Wipe();
    if (gameServer->entities.registry.all_of<StyleComponent>(entity))
        gameServer->entities.registry.get<StyleComponent>(entity).Wipe();
    if (gameServer->entities.registry.all_of<TeamComponent>(entity))
        gameServer->entities.registry.get<TeamComponent>(entity).Wipe();
}
