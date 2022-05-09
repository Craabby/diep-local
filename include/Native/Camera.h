#pragma once

#include <Native/EntityFactory.h>
#include <Native/Component/Camera.h>

class CameraEntity : public Entity
{
public:
    float sizeFactor = 1;

    CameraEntity(entityId arena);
};
