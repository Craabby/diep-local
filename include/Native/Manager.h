#pragma once

#include <vector>

#include <entt/entt.hpp>

#include <Physics/CollisionManager.h>
#include <Native/Entity.h>

namespace diep::server
{
    class GameServer;
};

class CameraEntity;

class EntityManager
{
public:
    using entityId = int16_t;

    DiepSpatialHashing collisionManager;
    diep::server::GameServer *gameServer;
    uint32_t zIndex = 0;
    std::vector<entityId> cameras;
    std::vector<entityId> otherEntities;
    Entity *inner[16384] = {};
    uint8_t hashTable[16384] = {};
    entityId lastId = -1;
    entt::registry registry;

    EntityManager(diep::server::GameServer *gameServer);

    void Tick(uint32_t tick);
    bool Exists(entityId id);
    bool Exists(Entity *entity);
    entityId Add(Entity *entity);
    void Remove(Entity *entity);
    void Clear();
};
