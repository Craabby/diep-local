#include <Client/Socket.h>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <Coder/Reader.h>

typedef websocketpp::server<websocketpp::config::asio> Server;

Message::Message(uint8_t *message, size_t length, websocketpp::connection_hdl connection)
    : reader(Reader(message, length)),
      connection(connection)
{
}

Socket::Socket(Server *server, websocketpp::connection_hdl connection)
    : server(server),
      connection(connection)
{
}
