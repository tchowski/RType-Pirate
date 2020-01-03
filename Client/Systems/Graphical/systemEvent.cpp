/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** get the events
*/

#include "systemEvent.hpp"
#include <iostream>

systemEvent::systemEvent(GraphicalLib &graphicalLib)
: GLib(graphicalLib)
{
}

const State systemEvent::update(const UserAction &action)
{
    if (action == CLOSE) {
        if (GLib.getEvent() == CLOSE) {
            return TRUE;
        }
        return FALSE;
    }
    if (action == KEYPRESS) {
        if (GLib.isAKeyPressed())
            return TRUE;
        return FALSE;
    }
    GLib.getEvent();
    return GLib.isKeyPressed(action);
}