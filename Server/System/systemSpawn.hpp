/*
** EPITECH PROJECT, 2019
** rtype projct
** File description:
** spawn an enemy, box or wall
*/

#pragma once

#include <ctime>
#include <string>
#include <vector>

#define MOB_NUMBER 1
#define MOB_BYDOS "bydos"

enum MobHandler
{
    BYDOS = 0
};

class systemSpawn
{
    public:
        systemSpawn(std::string &currentdir);
        ~systemSpawn();

        std::string update();
        void *openMobLibrary(const std::string &);
        void closeMobLibrary(void *);
        void closeMobLibrary(std::vector<void *>);
        std::string createNewMob(const int);
    private:
        std::string current_dir;
        std::vector<void *> _handler;
        std::string _str;
        std::clock_t _start;
        double _since;
        unsigned short int _spawntype;
        const int getRandMob() const;
        std::string mobCompletePath(const std::string);
};