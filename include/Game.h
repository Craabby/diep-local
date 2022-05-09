#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <Client/Client.h>
#include <Native/Arena.h>
#include <Native/Manager.h>

typedef websocketpp::server<websocketpp::config::asio> Server;

class GameServer
{
private:
    Server *server;
    uint32_t tickCount;

    void Listen();
    void RunGameLoop();
    void Tick(uint32_t tick);

public:
    static const uint32_t globalPlayerCount = 0;
    bool running = true;
    std::string gamemode;
    std::string endpoint;
    bool playersOnMap = false;
    std::vector<Client *> clients;
    ArenaEntity *arena;
    EntityManager entities;

    GameServer(Server *server, std::string gamemode, std::string endpoint);
    ~GameServer();
};
