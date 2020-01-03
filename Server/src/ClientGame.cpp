/*
** EPITECH PROJECT, 2019
** RType
** File description:
** ClientGame
*/

#include "../include/ClientGame.hpp"

void ClientGame::setServAddr()
{
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT_GAME);
    servaddr.sin_addr.s_addr = INADDR_ANY;
}

void ClientGame::setDataStruct(std::string construct, std::string destruct, bool fired, std::pair<float, float> pos)
{
    data_.construct = "Construct";
    data_.destruct = "Destruct";
    data_.update = "Update";
    data_.fired = false;
    data_.pos = std::pair(2, 2);
    data_buffer_ = reinterpret_cast<char*>(&data_);
}

network_buffer ClientGame::getDataStruct()
{
    std::cout << "Message receive from server: " << std::endl;
    network_buffer *buffer = new network_buffer;
    buffer = reinterpret_cast<network_buffer *>(data_buffer_);
    memcpy(&data_, buffer, sizeof(network_buffer));
    return data_;
}

ClientGame::ClientGame()
{
    memset(&data_, 0, sizeof(network_buffer));
    if ((sockfd_ = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        throw "socket creation failed";
    }
    setServAddr();
    while (1) {
        setDataStruct("Construct", "Destruct", true, std::pair<float, float>(2,2));
        sleep(2);
        sendto(sockfd_, (const char*)data_buffer_, strlen(data_buffer_), 0, (const struct sockaddr*)&servaddr, sizeof(servaddr));
        recvfrom(sockfd_, (char*)data_buffer_, 1024, MSG_WAITALL, (struct sockaddr*)&servaddr, &sock_);
        getDataStruct();
    }
    close(sockfd_);
}

ClientGame::~ClientGame()
{
}
