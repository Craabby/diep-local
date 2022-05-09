#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <Client/Socket.h>
#include <Native/EntityFactory.h>

typedef websocketpp::server<websocketpp::config::asio> Server;

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
private:
    std::vector<Client *> clients;
    uint32_t connectTick;

public:
    bool terminated;
    Socket socket;
    Client(Server *server, websocketpp::connection_hdl connection, std::vector<Client *> clients);
    void terminate();
    size_t getId() const;
};

namespace std
{
    template <>
    struct hash<Client>
    {
        size_t operator()(const Client &p) const
        {
            return std::hash<uint32_t>()(p.getId());
        }
    };
}
