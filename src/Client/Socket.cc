#include <Client/Socket.h>

Socket::Socket(Server *server, websocketpp::connection_hdl connection)
    : server(server),
      connection(connection)
{
}
