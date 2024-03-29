#include <Game.h>

#include <iostream>
#include <string>
#include <unordered_set>
#include <thread>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <Client/Client.h>
#include <Gamemodes/SandboxArena.h>
#include <Native/EntityFactory.h>

typedef websocketpp::server<websocketpp::config::asio> Server;

diep::server::GameServer::GameServer(Server *server, std::string gamemode, std::string endpoint)
    : server(server),
      gamemode(gamemode),
      endpoint(endpoint),
      arena(new SandboxArena(this)),
      entities(EntityManager(this))
{
    std::cout << "inserting arena" << std::endl;
    arena->Insert();

    Listen();
    RunGameLoop();
}

diep::server::GameServer::~GameServer()
{
    delete arena;
}

void diep::server::GameServer::RunGameLoop()
{
    while (true)
    {
        using namespace std::chrono;
        time_point start = system_clock::now();
        Tick(tickCount);
        time_point end = system_clock::now();
        duration<double> difference = end - start;
        int64_t deltaTime = (int64_t)duration_cast<microseconds>(difference).count();
        usleep(40'000 - (deltaTime < 40'000 ? deltaTime : 39'999));

        // time_point otherEnd = system_clock::now();
        // std::cout << std::endl
        //           << std::endl
        //           << "tick " << tickCount << " time:" << std::endl
        //           << "tick took: " << (double)duration_cast<nanoseconds>(difference).count() / 1'000'000 << " ms" << std::endl
        //           << "time elapsed: " << (double)duration_cast<nanoseconds>(duration<double>(otherEnd - start)).count() / 1'000'000 << " ms" << std::endl;
    }
}

void diep::server::GameServer::Tick(uint32_t tick)
{
    tickCount++;

    entities.Tick(tick);
    for (client::Client *client : clients)
        client->Tick(tick);
}

void diep::server::GameServer::Listen()
{
    namespace placeholders = websocketpp::lib::placeholders;
    server->set_open_handler([this](websocketpp::connection_hdl connection)
                             {
        std::cout << "client connected" << std::endl;
        client::Client *client = new client::Client(connection, this);
        clients.push_back(client); 
        
        server->get_con_from_hdl(client->socket.connection)->set_close_handler([this, client](websocketpp::connection_hdl)
                              {
            clients.erase(std::find(clients.begin(), clients.end(), client));
            client->Terminate();
            delete client;
        }); });
}