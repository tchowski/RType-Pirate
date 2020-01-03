/*
** EPITECH PROJECT, 2019
** RType
** File description:
** Server
*/

#ifndef server_H_
#define server_H_

#include "Client.hpp"
#include <arpa/inet.h>
#include <chrono>
#include <errno.h>
#include <iostream>
#include <memory>
#include <mutex>
#include <netinet/in.h>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <vector>

class Server {
public:
    Server(int port);
    ~Server();
    void run(std::string &);
    void loopCommunication(std::string &);
    void cleanBuffer(char** buffer);
    std::vector<std::shared_ptr<Client>> Clients_;
    bool StartNewRoom();
    void client_connected();
    struct preGameWaitRoom {
        std::string name;
    };
    std::vector<std::string> nicknames_;
    preGameWaitRoom buffWait;

private:
    int master_socket_;
    int port_;
    int addrlen_;
    int max_sd_;
    int new_socket_;
    int activity_;
    int valread;
    int sd;
    char message[1024];
    struct sockaddr_in address;
    fd_set readfds;
};

#endif /* !server */
