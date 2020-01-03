/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** systemSound
*/

#pragma once

#include "SoundLib.hpp"
#include "ComponentTypeList.hpp"
#include <vector>
#include <algorithm>

class systemSound
{
    public:
        systemSound(SoundLib &sound, ComponentTypeList<std::string> &musics, ComponentTypeList<std::string> &sounds);
        ~systemSound() = default;

        void update(const std::vector<std::string> &names, const bool &wait_for_prev_to_finish = false);

    private:
        ComponentTypeList<std::string> &mySounds;
        ComponentTypeList<std::string> &myMusics;
        SoundLib &SLib;
};