/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** hitbox handle thanks to quad tree
*/

#pragma once

#include <vector>
#include "ComponentTypeList.hpp"

class systemHitbox
{
    public:
        systemHitbox(ComponentTypeList<std::pair<float, float>> &pos, ComponentTypeList<std::pair<unsigned int, unsigned int>> &hb, unsigned int maxDepth, unsigned int maxEntity);
        ~systemHitbox() = default;

        std::vector<std::pair<unsigned int, unsigned int>>& update(float width, float height);

    private:
        void checkTouching(std::vector<std::pair<unsigned int, std::pair<float, float>>>&);
        unsigned int divide();
        void startQuadtree(float width, float height, std::vector<std::pair<unsigned int, std::pair<float, float>>> _posList, unsigned int depth);

        ComponentTypeList<std::pair<float, float>> &_cpPosition;
        ComponentTypeList<std::pair<unsigned int, unsigned int>> &_cpHitbox;
        std::vector<std::pair<unsigned int, unsigned int>> _touching;
        unsigned int MAX_DEPTH;
        unsigned int MAX_ENTITY;
};