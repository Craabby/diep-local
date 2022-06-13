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
#include <Native/Entity.h>

Entity *CreateObject(diep::server::GameServer *gameServer)
{
    Entity *entity = new Entity(gameServer);
    entity->gameServer->AppendComponentToEntity<RelationsComponent>(entity);
    entity->gameServer->AppendComponentToEntity<PhysicsComponent>(entity);
    entity->gameServer->AppendComponentToEntity<PositionComponent>(entity);
    entity->gameServer->AppendComponentToEntity<StyleComponent>(entity);
    return entity;
}
Entity *CreateLivingObject(diep::server::GameServer *gameServer)
{
    Entity *entity = CreateObject(gameServer);
    entity->gameServer->AppendComponentToEntity<HealthComponent>(entity);
    return entity;
}
Entity *CreateTankBody(diep::server::GameServer *gameServer)
{
    Entity *entity = CreateLivingObject(gameServer);
    entity->gameServer->AppendComponentToEntity<NameComponent>(entity);
    entity->gameServer->AppendComponentToEntity<ScoreComponent>(entity);
    return entity;
}
Entity *CreateBarrel(diep::server::GameServer *gameServer)
{
    return CreateObject(gameServer);
}

Entity *CreateArena(diep::server::GameServer *gameServer)
{
    Entity *entity = new Entity(gameServer);
    entity->gameServer->AppendComponentToEntity<ArenaComponent>(entity);
    return entity;
}
CameraEntity *CreateCameraEntity(diep::server::GameServer *gameServer)
{
    CameraEntity *entity = new CameraEntity(gameServer);
    entity->gameServer->AppendComponentToEntity<CameraComponent>(entity);
    return entity;
}
Camera *CreateCamera(diep::server::client::Client *client)
{
    Camera *entity = new Camera(client);
    entity->gameServer->AppendComponentToEntity<CameraComponent>(entity);
    return entity;
}