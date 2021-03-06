/*
** EPITECH PROJECT, 2019
** RTYPE
** File description:
** ClientGameNetwork
*/

#include "ClientGameNetwork.hpp"

void ClientGameNetwork::setServAddr()
{
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT_GAME_THREAD);
    // servaddr.sin_addr.s_addr = INADDR_ANY;
    if (inet_pton(AF_INET, ip_addr_.c_str(), &servaddr.sin_addr) <= 0) {
        throw "\nInvalid address/ Address not supported \n";
    }
}

void ClientGameNetwork::setDataStruct(std::string construct, std::string destruct, bool fired, int nb_player, std::pair<float, float> pos)
{
    data_->construct = construct;
    data_->destruct = destruct;
    data_->update = "Update";
    data_->fired = fired;
    data_->pos = std::pair<unsigned int, std::pair<float, float>>(nb_player, pos);
    data_buffer_ = reinterpret_cast<char*>(data_);
}

void DEBUG(network_buffer* data)
{
    std::cout << "Data construct: " << data->construct << std::endl;
    std::cout << "Data destruct: " << data->destruct << std::endl;
    std::cout << "Data update: " << data->update << std::endl;
    std::cout << "Data fired: " << data->fired << std::endl;
    std::cout << "Data id: " << data->pos.first << std::endl;
    std::cout << "Data pos: " << data->pos.second.first << "," << data->pos.second.second << std::endl;
    std::cout << "Mob Spawn: " << data->isMobSpawned << std::endl;
}

network_buffer* ClientGameNetwork::getDataStruct()
{
    //std::cout << "Message receive from server: " << std::endl;
    network_buffer* buffer = new network_buffer;
    buffer = reinterpret_cast<network_buffer*>(data_buffer_);
    //DEBUG(buffer);
    memcpy(data_, buffer, sizeof(network_buffer));
    return data_;
}

void ClientGameNetwork::disconnect(int nb_player)
{
    setDataStruct(" ", "Destruct", false, nb_player, std::pair<float, float>(0, 0));
    sendto(sockfd_, data_buffer_, sizeof(network_buffer), 0, (const struct sockaddr*)&servaddr, sizeof(servaddr));
    close(sockfd_);
}

void ClientGameNetwork::receive(Factory& factory, int nb_player)
{
    int id = 10;

    int ret = recvfrom(sockfd_, data_buffer_, 1024, MSG_DONTWAIT, (struct sockaddr*)&servaddr, &sock_);
    if (ret < 0)
        return;
    else {
        getDataStruct();
        if (data_->isMobSpawned) {
            int sprite = 3;
            for (; factory.getDrawableComponentsList().hasThisComponent(id) && id < 100; id++)
                ;
            if (!factory.getDrawableComponentsList().hasThisComponent(id)) {
                factory.getDrawableComponentsList().addComponent(id, "Enemy" + std::to_string(sprite));
                factory.getPositionComponentsList().addComponent(id, std::pair<float, float>(1800, 540));
            }
        }
        if (data_->fired == true) {
            for (id = 10; !factory.getDrawableComponentsList().hasThisComponent(id) && id < 100; id++)
                ;
            if (factory.getDrawableComponentsList().hasThisComponent(id)) {
                factory.getDrawableComponentsList().deleteComponent(id);
                factory.getPositionComponentsList().deleteComponent(id);
            }
        }
        if (data_->pos.first >= 1 && data_->pos.first <= 4) {
            if (factory.getPositionComponentsList().hasThisComponent(data_->pos.first) && data_->pos.first != nb_player)
                factory.getPositionComponentsList().setComponent(data_->pos.first, data_->pos.second);
        }
    }
}

void ClientGameNetwork::send(Factory& factory, int nb_player, bool fired)
{
    if (factory.getPositionComponentsList().hasThisComponent(nb_player)) {
        setDataStruct(" ", " ", fired, nb_player, factory.getPositionComponentsList().getComponent(nb_player));
        sendto(sockfd_, data_buffer_, sizeof(network_buffer), 0, (const struct sockaddr*)&servaddr, sizeof(servaddr));
        //printf("Message sent to server! \n\n");
    }
}

ClientGameNetwork::ClientGameNetwork(std::string ip_addr)
{
    if ((sockfd_ = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        throw "socket creation failed";
    }
    ip_addr_ = ip_addr;
    data_ = new network_buffer;
    data_buffer_ = new char[1024];
    setServAddr();
}