#pragma once

#include <entt/entity/registry.hpp>

#include <Native/Arena.h>

class SandboxArena : public ArenaEntity
{
public:
    SandboxArena(entt::registry *registry);
};
