/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** systemPlayerActions
*/

#pragma once

#include "systemEvent.hpp"
#include "systemSound.hpp"
#include "ClientGameNetwork.hpp"
#include "Factory.hpp"

class systemPlayerActions
{
    public:
        systemPlayerActions(std::shared_ptr<ClientGameNetwork> &network, std::vector<std::pair<std::string, std::pair<float, float>>> &pthsTxtrs, systemEvent &systemEvt, systemSound &systemSnd, Factory &fctry);
        ~systemPlayerActions() = default;

        void update(const int &nb_player);

    private:
        std::shared_ptr<ClientGameNetwork> &game;
        std::vector<std::pair<std::string, std::pair<float, float>>> &pathsTextures;
        systemEvent &sysEvent;
        systemSound &sysSound;
        Factory &factory;
};