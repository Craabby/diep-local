#include <Native/Manager.h>

#include <iostream>

#include <Game.h>
#include <Native/Component/Camera.h>
#include <Native/Component/Arena.h>

EntityManager::EntityManager(diep::server::GameServer *gameServer)
    : gameServer(gameServer)
{
}

void EntityManager::Tick(uint32_t tick)
{
    auto view = registry.view<ArenaComponent>();

    ArenaComponent &arenaComponent = view.get<ArenaComponent>(gameServer->arena->entity);

    while (!inner[lastId] && lastId >= 0)
    {
        lastId--;
    }
}

entityId EntityManager::Add(Entity *entity)
{
    entityId oldLastId = this->lastId + 1;

    for (entityId id = 0; id <= oldLastId; id++)
    {
        if (Exists(id))
            continue;

        entity->id = id;
        hashTable[id]++;
        entity->preservedHash = hashTable[id];
        entity->hash = hashTable[id];
        inner[id] = entity;

        if (registry.any_of<CameraComponent>(entity->entity))
        {
            cameras.push_back(entity->id);
        }
        else
            otherEntities.push_back(entity->id);

        if (lastId < id)
            lastId = entity->id;

        std::cout << "allocated new id " << id << std::endl;

        return id;
    }
    throw std::runtime_error("no more ids >:(");
}

void EntityManager::Remove(Entity *entity)
{
    if (registry.any_of<CameraComponent>(entity->entity))
    {
        auto index = std::find(cameras.begin(), cameras.end(), entity->id);
        if (index != cameras.end())
            cameras.erase(index);
        else
            std::cout << "cannot remove camera " << entity->id << std::endl;
    }
    else
        otherEntities.erase(std::find(otherEntities.begin(), otherEntities.end(), entity->id));

    inner[entity->id] = nullptr;
}

void EntityManager::Clear()
{
    lastId = -1;
    collisionManager.Reset();
    otherEntities.clear();
    cameras.clear();

    for (entityId i = 0; i < 16384; i++)
        hashTable[i] = 0;
    for (entityId i = 0; i < 16384; i++)
    {
        if (inner[i] != nullptr)
        {
            inner[i]->hash = 0;
            inner[i] = nullptr;
        }
    };
}

bool EntityManager::Exists(entityId id)
{
    if (id < 0 || id >= 16384)
        return false;
    return inner[id] != nullptr;
}
