#include <Entity/Tank/TankBody.h>

#include <Game.h>
#include <Native/Camera.h>

TankBody::TankBody(CameraEntity *camera)
    : Entity(camera->gameServer),
      camera(camera)
{
    gameServer->AppendComponentToEntity<RelationsComponent>(this);
    gameServer->AppendComponentToEntity<PositionComponent>(this);
    gameServer->AppendComponentToEntity<PhysicsComponent>(this);
    gameServer->AppendComponentToEntity<StyleComponent>(this);

    CameraComponent &cameraComponent = gameServer->entities.registry.get<CameraComponent>(camera->entity);
    RelationsComponent &cameraRelations = gameServer->entities.registry.get<RelationsComponent>(camera->entity);
    RelationsComponent &relationsComponent = gameServer->entities.registry.get<RelationsComponent>(entity);
    PhysicsComponent &physicsComponent = gameServer->entities.registry.get<PhysicsComponent>(entity);
    StyleComponent &styleComponent = gameServer->entities.registry.get<StyleComponent>(entity);
    cameraComponent.Player(this);
    cameraComponent.SpawnTick(gameServer->tickCount);
    cameraRelations.Owner(this);
    cameraRelations.Parent(this);
    relationsComponent.Team(camera);
    relationsComponent.Owner(camera);
    physicsComponent.Size(100);
    physicsComponent.Sides(1);
}
