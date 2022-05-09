#include <Game.h>

#include <iostream>
#include <string>
#include <unordered_set>
#include <thread>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <Client/Client.h>
#include <Gamemodes/SandboxArena.h>

typedef websocketpp::server<websocketpp::config::asio> Server;

GameServer::GameServer(Server *server, std::string gamemode, std::string endpoint)
    : server(server),
      gamemode(gamemode),
      endpoint(endpoint),
      arena(new SandboxArena(&entities.registry))
{
    listen();

    runGameLoop();
}

GameServer::~GameServer()
{
    delete arena;
}

void GameServer::runGameLoop()
{
    while (true)
    {
        using namespace std::chrono;
        time_point start = system_clock::now();
        tick(tickCount);
        time_point end = system_clock::now();
        duration<double> difference = end - start;
        usleep(40'000 - (uint32_t)duration_cast<microseconds>(difference).count() - 160);

        time_point otherEnd = system_clock::now();

        std::cout << std::endl
                  << std::endl
                  << "tick " << tickCount << " time:" << std::endl;
        std::cout << "tick took: " << (double)duration_cast<nanoseconds>(difference).count() / 1'000'000 << " ms" << std::endl;
        std::cout << "time elapsed: " << (double)duration_cast<nanoseconds>(duration<double>(otherEnd - start)).count() / 1'000'000 << " ms" << std::endl;
    }
}

void GameServer::tick(uint32_t tick)
{
    tickCount++;

    entities.tick(tick);
}

void GameServer::listen()
{
    namespace placeholders = websocketpp::lib::placeholders;
    server->set_max_message_size(1024);
    server->set_open_handler([this](websocketpp::connection_hdl connection)
                             {
        std::cout << "client connected" << std::endl;
        Client *client = new Client(server, connection, clients);
        clients.push_back(client); });

    server->set_close_handler([this](websocketpp::connection_hdl connection)
                              {
        for (size_t i = 0; i < clients.size(); i++)
        {
            Client *client = clients.at(i);
            server->get_con_from_hdl(client->socket.connection);
            if (server->get_con_from_hdl(client->socket.connection) == server->get_con_from_hdl(connection))
            {
                client->socket.events.emit<EventId::close>((void *)client);
                clients.erase(clients.begin() + i);
                delete client;
            }
        } });
}
