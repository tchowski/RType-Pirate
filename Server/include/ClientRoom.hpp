/*
** EPITECH PROJECT, 2019
** RType
** File description:
** ClientRoom
*/

#ifndef ClientGame_H_
#define ClientGame_H_

#include "ClientGame.hpp"
#include "NetworkStruct.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

class ClientRoom {
public:
    ClientRoom();
    ~ClientRoom();

protected:
private:
    void set_struct_serv();
    int sock_room;
    network_buffer *data;
    struct sockaddr_in serv_addr;
    int func(int sockfd);
};

#endif /* !ClientRoom */
