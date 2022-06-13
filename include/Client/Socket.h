#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <Coder/Reader.h>
#include <EventEmitter.h>

typedef websocketpp::server<websocketpp::config::asio> Server;
using Connection = std::shared_ptr<websocketpp::connection<websocketpp::config::asio>>;

namespace diep::server::socket
{
    class Message
    {
    public:
        Message(uint8_t *message, size_t length, Connection connection);

        diep::coder::reader::Reader reader;
        Connection connection;
    };

    class Socket
    {
    public:
        Server *server;
        Connection connection;
        EventEmitter events;

        Socket(Server *server, Connection connection);
    };
}
