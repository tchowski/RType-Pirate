/*
** EPITECH PROJECT, 2019
** RTYPE
** File description:
** ClientGameNetwork
*/

#ifndef ClientGameNetwork_H_
#define ClientGameNetwork_H_

#define PORT_GAME_THREAD 8081
#include "NetworkStruct.hpp"
#include "Factory.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

typedef struct
{
    int x;
    int y;
} playerData;

typedef struct
{
    playerData player[];
} DataStruct;


class ClientGameNetwork {
public:
    struct sockaddr_in servaddr;
    int sockfd_;
    char* data_buffer_;
    network_buffer *data_;
    socklen_t sock_;
    ClientGameNetwork(std::string ip_addr);
    ~ClientGameNetwork() = default;
    void setDataStruct(std::string construct, std::string destruct, bool fired, int nb_player, std::pair<float, float> pos);
    void setServAddr();
    network_buffer *getDataStruct();
    void start_server();
    void disconnect(int nb_player);
    void send(Factory &factory, int nb_player, bool fired);
    void receive(Factory &factory, int nb_player);
    std::string ip_addr_;
};

#endif /* !ClientGameNetwork */
