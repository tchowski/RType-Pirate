/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** level
*/

#pragma once

#include "Factory.hpp"
#include "SoundLib.hpp"
#include "GraphicalLib.hpp"
#include "systemDraw.hpp"
#include "systemSound.hpp"
#include "systemEvent.hpp"
#include "systemPlayerActions.hpp"
#include "ClientGame.hpp"

enum RETURN_STATE {
    PLAY,
    GAMEOVER
};

int GameOverScreen(GraphicalLib &GLib, SoundLib &SLib, Factory &factory);
int VictoryScreen(GraphicalLib &GLib, SoundLib &SLib, Factory &factory);
int StageClearScreen1(GraphicalLib &GLib, SoundLib &SLib, Factory &factory);
int StageClearScreen2(GraphicalLib &GLib, SoundLib &SLib, Factory &factory);
int LaunchStage(const int &nb_player, const int &difficulty_max, const std::string &music_name, GraphicalLib &GLib, SoundLib &SLib, Factory &factory);