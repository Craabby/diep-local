#include <iostream>

#include <entt/entity/registry.hpp>

#include <Native/EntityFactory.h>
#include <Native/FieldGroups.h>

Entity::Entity(entt::registry *registry)
    : registry(registry)
{
}

Entity *createObjectEntity(entt::registry *registry)
{
    Entity *entity = new Entity(registry);
    entt::entity enttEntity = registry->create();

    registry->emplace<RelationsComponent>(enttEntity, entity->id);
    registry->emplace<PhysicsComponent>(enttEntity, entity->id);
    registry->emplace<PositionComponent>(enttEntity, entity->id);
    registry->emplace<StyleComponent>(enttEntity, entity->id);

    return entity;
}
