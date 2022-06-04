#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <Client/Socket.h>
#include <Coder/Writer.h>
#include <Native/Entity.h>
#include <Native/EntityFactory.h>
#include <Native/Manager.h>

typedef websocketpp::server<websocketpp::config::asio> Server;

namespace diep::server
{
    class GameServer;
}

namespace diep::server::client
{
    enum class AccessLevel
    {
        NoAccess = -1,
        PublicAcess,
        Reserved,
        BetaAccess,
        FullAccess
    };

    class Client
    {
        uint32_t connectTick = 0;
        GameServer *gameServer;

    public:
        Entity *camera = nullptr;
        socket::Socket socket;
        bool terminated = false;

        Client(Server *server, websocketpp::connection_hdl connection, GameServer *gameServer);

        void Terminate();
        void Send(coder::writer::Writer const &&writer);
        size_t GetId() const;
        void Tick(uint32_t tick);
    };
}

namespace std
{
    template <>
    struct hash<diep::server::client::Client>
    {
        size_t operator()(const diep::server::client::Client &p) const
        {
            return std::hash<uint32_t>()(p.GetId());
        }
    };
}
