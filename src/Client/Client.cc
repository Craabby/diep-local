#include <Client/Client.h>

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

#include <websocketpp/frame.hpp>

#include <Coder/Writer.h>
#include <EventEmitter.h>
#include <Game.h>
#include <Native/Entity.h>
#include <Native/EntityFactory.h>
#include <Native/Manager.h>

diep::server::client::Client::Client(Server *server, websocketpp::connection_hdl connection, GameServer *gameServer)
    : socket(diep::server::socket::Socket(server, connection)),
      gameServer(gameServer)
{
    socket.server->get_con_from_hdl(socket.connection)->set_message_handler([this](websocketpp::connection_hdl connection, Server::message_ptr _message)
                                                                            {
        diep::server::socket::Message packet((uint8_t *)_message->get_raw_payload().c_str(), _message->get_raw_payload().size(), connection);
        socket.events.Emit<EventId::packet>((void *)&packet); });

    socket.events.On<EventId::packet>([this](void *_packet)
                                      {
        diep::server::socket::Message *packet = (diep::server::socket::Message *)_packet;

        if (packet->reader.size < 1) return;

        uint8_t header = packet->reader.U8();

        if (header == 0)
        {
            std::cout << "recieved init packet" << std::endl;
            if (camera)
                return;
            if (packet->reader.StringNT() != "6f59094d60f98fafc14371671d3ff31ef4d75d9e")
                return;


            Send(std::move(*coder::writer::Writer().U8(7)));
            Send(std::move(*coder::writer::Writer().U8(4)->StringNT(this->gameServer->gamemode)->StringNT(this->gameServer->endpoint)));
            Send(std::move(*coder::writer::Writer().U8(10)->Vu((uint32_t)this->gameServer->clients.size())));

            camera = CreateCamera(this->gameServer);

            return;
        }

        if (!camera)
            return;

        if (header == 5)
        {
            Send(std::move(*coder::writer::Writer().U8(5)));

            return;
        } });

    socket.events.On<EventId::close>([this](void *)
                                     { Terminate(); });
}

void diep::server::client::Client::Terminate()
{
    terminated = true;
    if (camera != nullptr)
    {
        gameServer->entities.Remove(camera);
        delete camera;
    };
}

size_t diep::server::client::Client::GetId() const
{
    return camera->id;
}

void diep::server::client::Client::Send(coder::writer::Writer const &&writer)
{
    socket.server->send(socket.connection, std::string((const char *)writer.Write().output, writer.Write().size), websocketpp::frame::opcode::value::binary);
}
