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
    ping = 5,
};

Client::Client(Server *server, websocketpp::connection_hdl connection, std::vector<Client *> clients)
    : socket(Socket(server, connection)),
      terminated(false),
      connectTick(0),
      clients(clients)
{
    socket.server->get_con_from_hdl(socket.connection)->set_message_handler([this](websocketpp::connection_hdl connection, Server::message_ptr _message)
                                                                            {
        Message packet((uint8_t *)_message->get_raw_payload().c_str(), _message->get_raw_payload().size(), connection);
        socket.events.Emit<EventId::packet>((void *)&packet); });

    socket.events.On<EventId::packet>([](void *_packet)
                                      {
        Message *packet = (Message *)_packet;

        if (packet->reader.size < 1) return;

        PacketId header = (PacketId)packet->reader.U8();

        if (header == PacketId::build)
        {

        }
        else if (header == PacketId::ping)
        {

        } });

    socket.events.On<EventId::close>([](void *_client)
                                     {
        Client *client = (Client *)_client;
        client->Terminate(); });
}

void Client::Terminate()
{
    terminated = true;
}

size_t Client::GetId() const
{
    return 0;
}
