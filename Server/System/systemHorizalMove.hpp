/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** creation of the shoot entity
*/

#pragma once

#include <vector>
#include "ComponentTypeList.hpp"

class systemHorizalMove
{
    public:
        systemHorizalMove(ComponentTypeList<short int> &, ComponentTypeList<std::pair<float, float>> &);
        ~systemHorizalMove() = default;

        void update();

    private:
        ComponentTypeList<short int> &_cpHorizontalTraj;
        ComponentTypeList<std::pair<float, float>> &_cpPosition;
};