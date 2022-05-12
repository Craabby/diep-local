#pragma once

#include <vector>

#include <entt/entt.hpp>

#include <Physics/CollisionManager.h>
#include <Native/Entity.h>

class EntityManager
{
public:
    using entityId = int16_t;

    DiepSpatialHashing collisionManager;
    uint32_t zIndex = 0;
    std::vector<entityId> cameras;
    std::vector<entityId> otherEntities;
    Entity *inner[16384];
    uint8_t hashTable[16384];
    entityId lastId = -1;
    entt::registry registry;

    EntityManager();

    void Tick(uint32_t tick);
};
