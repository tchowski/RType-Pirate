/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** hitbox handle thanks to quad tree
*/

#pragma once

#include <vector>
#include "ComponentTypeList.hpp"

class systemApplyDmg
{
    public:
        systemApplyDmg(ComponentTypeList<short int> &);
        ~systemApplyDmg() = default;

        std::vector<unsigned int> &update(std::vector<std::pair<unsigned int, unsigned int>> &);

    private:
        ComponentTypeList<short int> &_cpTeam;
        std::vector<unsigned int> _destroy;
};