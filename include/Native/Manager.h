#pragma once

#include <vector>

#include <Physics/CollisionManager.h>
#include <Native/Entity.h>

class EntityManager
{
public:
    using entityId = int16_t;

    EntityManager();

    DiepSpatialHashing collisionManager;
    uint32_t zIndex = 0;
    std::vector<entityId> cameras;
    std::vector<entityId> otherEntities;
    entityId *inner[16384];
    uint8_t hashTable[16384];
    entityId lastId = -1;

    void tick(uint32_t tick);
};
