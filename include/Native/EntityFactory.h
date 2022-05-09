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

Entity creatArena(entt::registry *registry);
Entity createCamera(entt::registry *registry);
Entity createLivingObject(entt::registry *registry);
Entity createObject(entt::registry *registry);
Entity createTankBody(entt::registry *registry);
Entity createBarrel(entt::registry *registry);

// class Entity
// {
// public:
//     EntityStateFlags state = EntityStateFlags::needsCreate;
//     std::vector<FieldGroupId> fieldGroups;

//     RelationsGroup *relations = nullptr;    
//     BarrelGroup *barrel = nullptr;
//     PhysicsGroup *physics = nullptr;
//     HealthGroup *health = nullptr;
//     UnusedGroup *unused = nullptr;
//     ArenaGroup *arena = nullptr;
//     NameGroup *name = nullptr;
//     CameraGroup *camera = nullptr;
//     PositionGroup *position = nullptr;
//     StyleGroup *style = nullptr;
//     ScoreGroup *score = nullptr;
//     TeamGroup *team = nullptr;

//     Entity();

//     void wipeState();
// };
