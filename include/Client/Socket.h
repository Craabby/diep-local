#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <EventEmitter.h>

typedef websocketpp::server<websocketpp::config::asio> Server;

struct Message
{
    uint8_t *message;
    size_t length;
    websocketpp::connection_hdl connection;
};

class Socket
{
public:
    Server *server;
    websocketpp::connection_hdl connection;
    EventEmitter events;

    Socket(Server *server, websocketpp::connection_hdl connection);
};
