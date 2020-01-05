/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** template of the structure used to communicate client/server
*/

#include <string>

typedef struct network_buffer {
    std::string construct;
    std::string destruct;
    std::string update;
    bool fired;
    bool isMobSpawned;
    std::pair<unsigned int, std::pair<float, float>> pos;
}network_buffer;
