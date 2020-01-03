/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** creation of the shoot entity
*/

#pragma once

#include <vector>
#include "ComponentTypeList.hpp"

class systemBounceMove
{
    public:
        systemBounceMove(ComponentTypeList<std::pair<float, float>> &, ComponentTypeList<std::pair<float, float>> &);
        ~systemBounceMove() = default;

        void update();

    private:
        ComponentTypeList<std::pair<float, float>> &_cpTraj;
        ComponentTypeList<std::pair<float, float>> &_cpPosition;
        ComponentTypeList<bool> _cpVerticalUp;
};