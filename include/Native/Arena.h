#pragma once

#include <entt/entity/registry.hpp>

#include <Native/EntityFactory.h>

class ArenaEntity : public Entity
{
public:
    ArenaEntity(entt::registry *registry);
};
