#include <Native/Manager.h>

EntityManager::EntityManager()
{
}

void EntityManager::tick(uint32_t tick)
{
    collisionManager.reset();
}
