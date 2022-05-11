#include <iostream>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <Game.h>

typedef websocketpp::server<websocketpp::config::asio> Server;

int main()
{
    // Create a server endpoint
    Server *server = new Server;
    std::thread thread([server]()
                       {
            server->set_access_channels(websocketpp::log::alevel::none);
            server->clear_access_channels(websocketpp::log::alevel::none);
            server->init_asio();
            server->listen(28623);
            server->start_accept();
            server->run(); });

    thread.detach();

    // std::thread([server]()
    //             { new GameServer(server, "teams", "teams"); })
    //     .detach();
    // std::thread([server]()
    //             { new GameServer(server, "4teams", "4teams"); })
    //     .detach();
    // std::thread([server]()
    //             { new GameServer(server, "dom", "dom"); })
    //     .detach();
    std::thread([server]()
                {
        diep::server::GameServer *gameServer = new diep::server::GameServer(server, "sandbox", "*");
        delete gameServer; })
        .detach();

    pause();

    delete server;
}
