/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** pre game wait room
*/

#pragma once

#include "SoundLib.hpp"
#include "GraphicalLib.hpp"
#include "systemDraw.hpp"
#include "systemSound.hpp"
#include "systemEvent.hpp"

enum GAMEMODE
{
    SURVIVAL = 42,
    CAMPAIGN = 84
};

#define NB_MAX_PLAYER 4

int connectServer(int &nb_player, const std::string &nickname, GraphicalLib &GLib, SoundLib &SLib, std::string ip_addr);