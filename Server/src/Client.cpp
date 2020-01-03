/*
** EPITECH PROJECT, 2019
** RType
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(int socket_client, std::string &nickname) : socket_client_(socket_client), nickname_(nickname)
{
}

std::string Client::getNickaname()
{
    return nickname_;
}

void Client::setNickname(std::string &nickame)
{
    this->nickname_ = nickame;
}

Client::~Client()
{
}
