/*
** EPITECH PROJECT, 2019
** RType
** File description:
** Room
*/

#include "Room.hpp"

Room::Room(std::string &currentdir, std::string &name, std::vector<std::shared_ptr<Client>> Clients) : current_dir(currentdir), Clients_(Clients), name_(name)
{
    start_thread(current_dir, name_, Clients_);
}

Room::~Room()
{
}
