#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <Client/Socket.h>
#include <Native/EntityFactory.h>

typedef websocketpp::server<websocketpp::config::asio> Server;

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

    enum class PacketId
    {
        build = 0,
        input = 1,
        ping = 5,
    };

    class Client
    {
    private:
        std::vector<Client *> clients;
        uint32_t connectTick;

    public:
        bool terminated;
        socket::Socket socket;
        Client(Server *server, websocketpp::connection_hdl connection, std::vector<Client *> clients);
        void Terminate();
        size_t GetId() const;
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
