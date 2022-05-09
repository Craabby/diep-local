#pragma once

#include <unordered_map>
#include <vector>

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
#include <Native/Entity.h>

Entity CreateArena(entt::registry *registry);
Entity CreateCamera(entt::registry *registry);
Entity CreateLivingObject(entt::registry *registry);
Entity CreateObject(entt::registry *registry);
Entity CreateTankBody(entt::registry *registry);
Entity CreateBarrel(entt::registry *registry);
