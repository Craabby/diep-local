#pragma once

#include <Const/Enums.h>
#include <Native/Entity.h>

namespace diep::server
{
    class GameServer;
}

class TankBody : public Entity
{
public:
    TankBody(diep::server::GameServer *gameServer);

    void SetTank(TankId tank);
};
