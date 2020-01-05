/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** template of the structure used to communicate client/server
*/

#pragma once

#ifndef NETWORK_STRUCT
#define NETWORK_STRUCT

#include <string>

struct network_buffer {
    std::string construct;
    std::string update;
    std::string destruct;
    bool fired;
    bool isMobSpawned;
    std::pair<unsigned int, std::pair<float, float>> pos;
};

#endif /* !NETWORK_STRUCT */