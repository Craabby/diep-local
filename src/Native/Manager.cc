#include <Native/Manager.h>

#include <iostream>

#include <Game.h>
#include <Native/Camera.h>
#include <Native/Component/Arena.h>
#include <Native/Component/Camera.h>
#include <Native/Component/Relations.h>

EntityManager::EntityManager(diep::server::GameServer *gameServer)
    : gameServer(gameServer)
{
}

void EntityManager::Tick(uint32_t tick)
{
    ArenaComponent &arenaComponent = registry.get<ArenaComponent>(gameServer->arena->entity);

    while (!inner[lastId] && lastId >= 0)
    {
        lastId--;
    }

    for (entityId id = 0; id <= lastId; id++)
    {
        if (!Exists(id))
            continue;

        Entity *entity = inner[id];

        if (registry.all_of<PositionComponent, PhysicsComponent, RelationsComponent>(entity->entity) && (!registry.get<RelationsComponent>(entity->entity).isChild))
        {
            PositionComponent &positionComponent = registry.get<PositionComponent>(entity->entity);
            PhysicsComponent &physicsComponent = registry.get<PhysicsComponent>(entity->entity);

            [&]
            {
            for (size_t i = 0; i < cameras.size(); i++)
            {
                // Entity *camera = inner[cameras.at(i)];
                // CameraComponent &cameraComponent = registry.get<CameraComponent>(camera->entity);
                // float deltaX = (cameraComponent.CameraX() - positionComponent.X());
                // float deltaY = (cameraComponent.CameraY() - positionComponent.Y());
                // float entityFov = 4500 + physicsComponent.Size() + physicsComponent.Width();
                // if ((deltaX * deltaX + deltaY * deltaY) < entityFov)
                // {
                    collisionManager.InsertEntity(entity);
                    entity->isViewed = true;
                //     return;
                // }

                // entity->isViewed = false;
            } }();
        }

        for (entityId id = 0; id <= lastId; id++)
        {
            if (!Exists(id))
                continue;

            Entity *entity = inner[id];

            entity->WipeState();
        }
    }

    for (entityId id = 0; id <= lastId; id++)
    {
        if (!Exists(id))
            continue;

        Entity *entity = inner[id];

        if (!registry.all_of<PhysicsComponent>(entity->entity))
            continue;

        registry.get<PhysicsComponent>(entity->entity).ApplyPhysics();
    }

    for (size_t i = 0; i < cameras.size(); i++)
    {
        registry.get<CameraComponent>(inner[cameras.at(i)]->entity).Tick(tick);
    }

    for (entityId cameraId : cameras)
    {
        CameraEntity *cameraEntity = static_cast<CameraEntity *>(inner[cameraId]);
        if (cameraEntity->isClientCamera)
            static_cast<Camera *>(cameraEntity)->Tick(tick);
        else
            cameraEntity->Tick(tick);
    }

    for (entityId id = 0; id < lastId; id++)
    {
        if (!Exists(id))
            continue;

        inner[id]->WipeState();
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

        std::cout << "allocated new id " << id << " to Entity " << entity << std::endl;

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