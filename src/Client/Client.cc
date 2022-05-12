#include <Client/Client.h>

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

#include <Coder/Writer.h>
#include <EventEmitter.h>

diep::server::client::Client::Client(Server *server, websocketpp::connection_hdl connection, std::vector<Client *> clients)
    : socket(diep::server::socket::Socket(server, connection)),
      terminated(false),
      connectTick(0),
      clients(clients)
{
    socket.server->get_con_from_hdl(socket.connection)->set_message_handler([this](websocketpp::connection_hdl connection, Server::message_ptr _message)
                                                                            {
        diep::server::socket::Message packet((uint8_t *)_message->get_raw_payload().c_str(), _message->get_raw_payload().size(), connection);
        socket.events.Emit<EventId::packet>((void *)&packet); });

    socket.events.On<EventId::packet>([this](void *_packet)
                                      {
        diep::server::socket::Message *packet = (diep::server::socket::Message *)_packet;

        if (packet->reader.size < 1) return;

        PacketId header = (PacketId)packet->reader.U8();

        if (header == PacketId::build)
        {

        }
        else if (header == PacketId::ping)
        {
            coder::writer::Writer writer;
            writer.U8(5);
            Send(writer);
        } });

    socket.events.On<EventId::close>([this](void *)
                                     {
        Terminate(); });
}

void diep::server::client::Client::Terminate()
{
    terminated = true;
}

size_t diep::server::client::Client::GetId() const
{
    return 0;
}

void diep::server::client::Client::Send(coder::writer::Writer const &writer)
{

}
