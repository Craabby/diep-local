#include <Native/EntityFactory.h>

#include <iostream>

#include <entt/entity/registry.hpp>

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

Entity CreateObject(entt::registry *registry)
{
    Entity entity = Entity(registry);
    entt::entity enttEntity = registry->create();
    entity.entity = enttEntity;

    registry->emplace<RelationsComponent>(enttEntity, entity.id);
    registry->emplace<PhysicsComponent>(enttEntity, entity.id);
    registry->emplace<PositionComponent>(enttEntity, entity.id);
    registry->emplace<StyleComponent>(enttEntity, entity.id);

    return entity;
}
Entity CreateCamera(entt::registry *registry)
{
    Entity entity = Entity(registry);
    entt::entity enttEntity = registry->create();
    entity.entity = enttEntity;

    registry->emplace<CameraComponent>(enttEntity, entity.id);

    return entity;
}
Entity CreateLivingObject(entt::registry *registry)
{
    Entity entity = CreateObject(registry);

    registry->emplace<HealthComponent>(entity.entity, entity.id);

    return entity;
}
Entity CreateTankBody(entt::registry *registry)
{
    Entity entity = CreateLivingObject(registry);

    registry->emplace<NameComponent>(entity.entity, entity.id);
    registry->emplace<ScoreComponent>(entity.entity, entity.id);

    return entity;
}
Entity CreateBarrel(entt::registry *registry)
{
    return CreateObject(registry);
}
