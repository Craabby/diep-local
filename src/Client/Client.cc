#include <Client/Client.h>

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

#include <websocketpp/frame.hpp>

#include <Coder/Writer.h>
#include <Entity/Tank/TankBody.h>
#include <EventEmitter.h>
#include <Game.h>
#include <Native/Entity.h>
#include <Native/EntityFactory.h>
#include <Native/Manager.h>

diep::server::client::Client::Client(websocketpp::connection_hdl connection, GameServer *gameServer)
    : socket(diep::server::socket::Socket(gameServer->server, connection)),
      gameServer(gameServer)
{
    socket.server->get_con_from_hdl(socket.connection)->set_message_handler([this, connection](websocketpp::connection_hdl, Server::message_ptr _message)
                                                                            {
        diep::server::socket::Message packet((uint8_t *)_message->get_raw_payload().c_str(), _message->get_raw_payload().size(), connection);
        socket.events.Emit<EventId::packet>(static_cast<void *>(&packet)); });

    socket.events.On<EventId::packet>([this](void *_packet)
                                      {
        diep::server::socket::Message *packet = static_cast<diep::server::socket::Message *>(_packet);

        if (packet->reader.size < 1) return;

        uint8_t header = packet->reader.U8();

        if (header == 0)
        {
            std::cout << "recieved init packet" << std::endl;
            if (camera)
                return;
            if (packet->reader.StringNT() != "6f59094d60f98fafc14371671d3ff31ef4d75d9e")
                return;


            Send(*coder::writer::Writer().U8(7));
            Send(*coder::writer::Writer().U8(4)->StringNT(this->gameServer->gamemode)->StringNT(this->gameServer->endpoint));
            Send(*coder::writer::Writer().U8(10)->Vu(static_cast<uint32_t>(this->gameServer->clients.size())));

            camera = CreateCamera(this);

            camera->Insert();

            return;
        }

        if (!camera)
            return;

        if (header == 2)
        {
            CameraComponent &camera = this->gameServer->entities.registry.get<CameraComponent>(this->camera->entity);
            RelationsComponent &relations = this->gameServer->entities.registry.get<RelationsComponent>(this->camera->entity);
            if (this->gameServer->entities.Exists(camera.Player())) return;
            if (this->gameServer->entities.registry.get<ArenaComponent>(this->gameServer->arena->entity).arenaState != 0) return;
        
            camera.StatsAvailable(0);
            camera.Level(1);

            for (uint8_t i = 0; i < 8; i++)
                camera.StatLevels()->Set(i, 0);
            
            TankBody *tank = new TankBody(this->gameServer);
            camera.Player(tank);
            relations.Owner(tank);
            relations.Parent(tank);

            tank->SetTank(TankId::Basic);
            this->camera->spectatee = nullptr;
        }
        else if (header == 5)
        {
            Send(*coder::writer::Writer().U8(5));

            return;
        } });
}

void diep::server::client::Client::Terminate()
{
    std::cout << "removed client" << std::endl;
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

void diep::server::client::Client::Send(coder::writer::Writer const &writer)
{
    gameServer->server->get_con_from_hdl(socket.connection)->send((void *)writer.Write().output, writer.Write().size, websocketpp::frame::opcode::value::binary);
}

void diep::server::client::Client::Tick(uint32_t tick)
{
}