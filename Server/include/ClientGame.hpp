/*
** EPITECH PROJECT, 2019
** RType
** File description:
** ClientGame
*/

#ifndef Clientgame_H_
#define Clientgame_H_
#include "NetworkStruct.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#define PORT_GAME 8081

class ClientGame {
public:
    ClientGame();
    ~ClientGame();
    void setDataStruct(std::string construct, std::string destruct, bool fired, std::pair<float, float> pos);
	void setServAddr();
	network_buffer getDataStruct();

protected:
private:
    struct sockaddr_in servaddr;
    int sockfd_;
	char* data_buffer_;
    network_buffer data_;
    socklen_t sock_;

};

#endif /* !ClientGame */
