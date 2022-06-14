#pragma once

#include <unordered_map>
#include <vector>

#include <entt/entity/registry.hpp>

#include <Native/Camera.h>
#include <Native/Component/Arena.h>
#include <Native/Component/Barrel.h>
#include <Native/Component/Camera.h>
#include <Native/Component/Example.h>
#include <Native/Component/Health.h>
#include <Native/Component/Name.h>
#include <Native/Component/Physics.h>
#include <Native/Component/Position.h>
#include <Native/Component/Relations.h>
#include <Native/Component/Score.h>
#include <Native/Component/Style.h>
#include <Native/Component/Team.h>
#include <Native/Entity.h>

namespace diep::server
{
    class GameServer;

    namespace client
    {
        class Client;
    }
}

Entity *CreateLivingObject(diep::server::GameServer *gameServer);
Entity *CreateObject(diep::server::GameServer *gameServer);
Entity *CreateTankBody(diep::server::GameServer *gameServer);
Entity *CreateBarrel(diep::server::GameServer *gameServer);

CameraEntity *CreateCameraEntity(diep::server::GameServer *gameServer);
Camera *CreateCamera(diep::server::client::Client *client);
