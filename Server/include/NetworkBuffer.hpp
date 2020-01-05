/*
** EPITECH PROJECT, 2019
** RType
** File description:
** NetworkBuffer
*/

#ifndef NETWORKBUFFER_HPP_
#define NETWORKBUFFER_HPP_

#include <iostream>
#include <string>

typedef struct network_buffer {
        std::string construct;
        std::string update;
        std::string destruct;
        bool isMobSpawned;
        bool fired;
        std::pair<float, float> pos;
    } data_t;

#endif /* !NETWORKBUFFER_HPP_ */
