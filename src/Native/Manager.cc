#include <Native/Manager.h>

EntityManager::EntityManager()
{
}

void EntityManager::Tick(uint32_t tick)
{
    collisionManager.Reset();
}
