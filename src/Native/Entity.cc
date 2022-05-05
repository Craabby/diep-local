#include <Native/Entity.h>

Entity::Entity()
{
}

void Entity::wipeState()
{
    if (relations)
        relations->wipe();
    if (barrel)
        barrel->wipe();
    if (physics)
        physics->wipe();
    if (health)
        health->wipe();
    if (unused)
        unused->wipe();
    if (arena)
        arena->wipe();
    if (name)
        name->wipe();
    if (camera)
        camera->wipe();
    if (position)
        position->wipe();
    if (style)
        style->wipe();
    if (score)
        score->wipe();
    if (team)
        team->wipe();
}
