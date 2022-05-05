#include <Client/Client.h>

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

#include <EventEmitter.h>

enum class PacketId
{
    build = 0,
    input = 1,
};

Client::Client(Server *server, websocketpp::connection_hdl connection, std::vector<Client *> clients)
    : socket(Socket(server, connection)),
      terminated(false),
      connectTick(0),
      clients(clients)
{

    socket.server->get_con_from_hdl(socket.connection)->set_message_handler([this](websocketpp::connection_hdl connection, Server::message_ptr _message)
                                                                            {
        Message packet{(uint8_t *)_message->get_raw_payload().c_str(), _message->get_raw_payload().size(), connection};
        socket.events.emit<EventId::packet>((void *)&packet); });

    socket.events.on<EventId::packet>([](void *_packet)
                                      {
        Message *packet = (Message *)_packet;

        if (packet->length < 1) return;

        PacketId header = *(PacketId *)packet->message;

        if (header == PacketId::build)
        {
            
        } });

    socket.events.on<EventId::close>([](void *_client)
                                     {
        Client *client = (Client *)_client;
        client->terminate(); });
}

void Client::terminate()
{
    terminated = true;
}

size_t Client::getId() const
{
    return 0;
}
