/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** systemDraw
*/

#pragma once

#include "ComponentTypeList.hpp"
#include "GraphicalLib.hpp"
#include <vector>
#include <algorithm>

class systemDraw
{
    public:
        systemDraw(GraphicalLib &graph, ComponentTypeList<std::pair<float, float>> &positions, ComponentTypeList<std::string> &sprites);
        ~systemDraw() = default;

        void update(const bool &all = false, const std::vector<unsigned int> &ids = std::vector<unsigned int>(), const std::vector<std::string> &names = std::vector<std::string>());

    private:
        ComponentTypeList<std::pair<float, float>> &myPositionComponents;
        ComponentTypeList<std::string> &mySpritesComponents;
        GraphicalLib &GLib;
};