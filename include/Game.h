#pragma once

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <Client/Client.h>
#include <Gamemodes/SandboxArena.h>
#include <Native/Entity.h>
#include <Native/Manager.h>

typedef websocketpp::server<websocketpp::config::asio> Server;

namespace diep::server
{
    class GameServer
    {
    private:

        void Listen();
        void RunGameLoop();
        void Tick(uint32_t tick);

    public:
        uint32_t tickCount;
        static const uint32_t globalPlayerCount = 0;
        Server *server;
        bool running = true;
        std::string gamemode;
        std::string endpoint;
        bool playersOnMap = false;
        std::vector<diep::server::client::Client *> clients;
        EntityManager entities;
        SandboxArena *arena;

        GameServer(Server *server, std::string gamemode, std::string endpoint);
        ~GameServer();

        template <class Component>
        void AppendComponentToEntity(Entity *entity)
        {
            std::cout << "emplacing component #" << std::to_string((uint8_t)Component::id) << " to Entity " << entity << std::endl;
            entities.registry.emplace<Component>(entity->entity, entity);
            entity->fieldGroups.push_back(Component::id);
            std::sort(entity->fieldGroups.begin(), entity->fieldGroups.end());
        }
    };
}
