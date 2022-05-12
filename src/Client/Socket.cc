#include <Client/Socket.h>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <Coder/Reader.h>

typedef websocketpp::server<websocketpp::config::asio> Server;

diep::server::socket::Message::Message(uint8_t *message, size_t length, websocketpp::connection_hdl connection)
    : reader(diep::coder::reader::Reader(message, length)),
      connection(connection)
{
}

diep::server::socket::Socket::Socket(Server *server, websocketpp::connection_hdl connection)
    : server(server),
      connection(connection)
{
}
