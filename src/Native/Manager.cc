#include <Native/Manager.h>

#include <iostream>

#include <Native/Component/Camera.h>

EntityManager::EntityManager()
{
}

void EntityManager::Tick(uint32_t tick)
{
    collisionManager.Reset();
}

entityId EntityManager::Add(Entity *entity)
{
    entityId lastId = this->lastId + 1;

    for (entityId id = 0; id < 16384; id++)
    {
        if (Exists(id))
            continue;

        std::cout << "allocated new entity id " << id << std::endl;
        entity->id = id;
        hashTable[id] += 1;
        entity->preservedHash = hashTable[id];
        entity->hash = hashTable[id];
        inner[id] = entity;

        if (registry.any_of<CameraComponent>(entity->entity))
            cameras.push_back(entity->id);
        else 
            otherEntities.push_back(entity->id);
        return id;
    }
    throw std::runtime_error("no more ids >:(");
}

void EntityManager::Remove(Entity *entity)
{
    inner[entity->id] = nullptr;
}

bool EntityManager::Exists(entityId id)
{
    std::cout << "step one" << std::endl;
    if (id < 0 || id >= 16384)
        return false;

    std::cout << "step two " << inner[id] << std::endl;
    return inner[id] != 0;
}
