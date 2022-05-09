#include <Native/Entity.h>

#include <entt/entity/registry.hpp>

Entity::Entity(entt::registry *registry)
    : registry(registry)
{
}
