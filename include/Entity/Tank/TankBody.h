#pragma once

#include <Const/Enums.h>
#include <Native/Entity.h>

class CameraEntity;

class TankBody : public Entity
{
    CameraEntity *camera;
public:
    TankBody(CameraEntity *camera);

    void SetTank(TankId tank);
};
