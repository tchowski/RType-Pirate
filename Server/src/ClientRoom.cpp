/*
** EPITECH PROJECT, 2019
** RType
** File description:
** ClientRoom
*/

#include "../include/ClientRoom.hpp"

#define PORT 8080

void ClientRoom::set_struct_serv()
{
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        throw "\nInvalid address/ Address not supported \n";
    }
}

int ClientRoom::func(int sockfd)
{
    char buff[80];
    char handshake[7] = "Hello\n";
    int n;

    send(sockfd, handshake, sizeof(buff), 0);
    read(sockfd, buff, sizeof(buff));
    printf("Buffer => %s", buff);
    bzero(buff, sizeof(buff));
    n = 0;
    while ((buff[n++] = getchar()) != '\n')
        ;
    printf("Send to Server: %s", buff);
    send(sockfd, buff, sizeof(buff), 0);
    for (;;) {
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        if ((strncmp(buff, "Start Game!\n", 11)) == 0) {
            printf("Client TCP Exit...\n");
            break;
        }
    }
    return 1;
}

ClientRoom::ClientRoom()
{
    if ((sock_room = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw "\n Socket creation error \n";
    }
    this->set_struct_serv();
    if (connect(sock_room, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        throw "\nConnection Failed \n";
    }
    func(sock_room);
    std::shared_ptr<ClientGame> game(new ClientGame());
}

ClientRoom::~ClientRoom()
{
}

int main(int argc, char const* argv[])
{
    ClientRoom client;

    return 0;
}
