/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** creation of the shoot entity
*/

#pragma once

#include <vector>
#include "ComponentTypeList.hpp"
#include <ctime>
#include <chrono>

using namespace std::chrono;

class systemRandomShoot
{
    public:
        systemRandomShoot(ComponentTypeList<short int> &);
        ~systemRandomShoot();

        void update();

    private:
        ComponentTypeList<short int> _time;
        ComponentTypeList<short int> &_interval;
};