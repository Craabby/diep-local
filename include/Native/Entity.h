#pragma once

#include <unordered_map>
#include <vector>

#include <Native/FieldGroups.h>

using entityId = int16_t;

enum class EntityStateFlags
{
    needsUpdate = 1 << 0,
    needsCreate = 1 << 1,
    needsDelete = 1 << 2,
};

class Entity
{
public:
    EntityStateFlags state = EntityStateFlags::needsCreate;
    std::vector<FieldGroupId> fieldGroups;

    RelationsGroup *relations = nullptr;    
    BarrelGroup *barrel = nullptr;
    PhysicsGroup *physics = nullptr;
    HealthGroup *health = nullptr;
    UnusedGroup *unused = nullptr;
    ArenaGroup *arena = nullptr;
    NameGroup *name = nullptr;
    CameraGroup *camera = nullptr;
    PositionGroup *position = nullptr;
    StyleGroup *style = nullptr;
    ScoreGroup *score = nullptr;
    TeamGroup *team = nullptr;

    Entity();

    void wipeState();
};
