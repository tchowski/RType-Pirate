/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** systemEvent
*/

#pragma once

#include "GraphicalLib.hpp"

class systemEvent
{
    public:
        systemEvent(GraphicalLib &graph);
        ~systemEvent() = default;

        const State update(const UserAction &action);

    private:
        GraphicalLib &GLib;
};