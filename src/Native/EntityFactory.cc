#include <Native/EntityFactory.h>

#include <iostream>

#include <entt/entity/registry.hpp>

#include <Game.h>
#include <Native/Component/Arena.h>
#include <Native/Component/Barrel.h>
#include <Native/Component/Camera.h>
#include <Native/Component/Example.h>
#include <Native/Component/Health.h>
#include <Native/Component/Name.h>
#include <Native/Component/Physics.h>
#include <Native/Component/Position.h>
#include <Native/Component/Relations.h>
#include <Native/Component/Score.h>
#include <Native/Component/Style.h>
#include <Native/Component/Team.h>

Entity *CreateObject(diep::server::GameServer *gameServer)
{
    Entity *entity = new Entity(gameServer);

    entity->gameServer->entities.registry.emplace<RelationsComponent>(entity->entity, entity->id);
    entity->gameServer->entities.registry.emplace<PhysicsComponent>(entity->entity, entity->id);
    entity->gameServer->entities.registry.emplace<PositionComponent>(entity->entity, entity->id);
    entity->gameServer->entities.registry.emplace<StyleComponent>(entity->entity, entity->id);

    return entity;
}
Entity *CreateCamera(diep::server::GameServer *gameServer)
{
    Entity *entity = new Entity(gameServer);

    entity->gameServer->entities.registry.emplace<CameraComponent>(entity->entity, entity->id);

    return entity;
}
Entity *CreateLivingObject(diep::server::GameServer *gameServer)
{
    Entity *entity = CreateObject(gameServer);

    entity->gameServer->entities.registry.emplace<HealthComponent>(entity->entity, entity->id);

    return entity;
}
Entity *CreateTankBody(diep::server::GameServer *gameServer)
{
    Entity *entity = CreateLivingObject(gameServer);

    entity->gameServer->entities.registry.emplace<NameComponent>(entity->entity, entity->id);
    entity->gameServer->entities.registry.emplace<ScoreComponent>(entity->entity, entity->id);

    return entity;
}
Entity *CreateBarrel(diep::server::GameServer *gameServer)
{
    return CreateObject(gameServer);
}
