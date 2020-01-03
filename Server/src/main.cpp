/*
** EPITECH PROJECT, 2019
** RType
** File description:
** main
*/

#include <cstdlib>
#include <iostream>
#include "Server.hpp"
#include "Game.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "need port" << std::endl;
        return (84);
    }
    try
    {
        std::string current_dir(argv[0]);
        int port = atoi(argv[1]);
        std::shared_ptr<Server> server(new Server(port));
        
        current_dir = current_dir.substr(0, current_dir.find_last_of("/"));
        server->run(current_dir);
        //**** Game loop when a game start *****//
        // while (1)
        // {
        //     //sMovePlayers.update(NetworkReceive());
        //     sHorizalMove.update();
        //     factory.createEntity(factory.generateNewUniqueID(), sSpawn.update());
        //     factory.destroyEntity(sApplyDmg.update(sHitbox.update(WINDOW_X, WINDOW_Y)));
        //     //Network.send(factory.prepareServerNetworkBuffer())
        // }
        //**************************************//
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        exit(84);
    }
    return 0;
}
