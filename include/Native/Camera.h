#pragma once

#include <Native/Entity.h>
#include <Native/FieldGroups.h>

class CameraEntity : public Entity
{
public:
    float sizeFactor = 1;

    CameraEntity(entityId arena);
};
