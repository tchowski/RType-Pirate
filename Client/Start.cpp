/*
** EPITECH PROJECT, 2019
** RType
** File description:
** Start
*/

#include "../include/Start.hpp"

Start::Start()
{
}

int Start::ConnectToRoom()
{
    int sockfd;
    char buffer[1024];
    std::string hello = "start\n";
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT_GAME);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        throw "\nConnection Failed \n";
        return 84;
    }
    int n, len;
    socklen_t sock_;
    sendto(sockfd, (const char*)hello.c_str(), hello.length(), 0, (const struct sockaddr*)&servaddr, sizeof(servaddr));
    printf("Start message sent.\n");
    close(sockfd);
    return 0;
}

Start::~Start()
{
}
