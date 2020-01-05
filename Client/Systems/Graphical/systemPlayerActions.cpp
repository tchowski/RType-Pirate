/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** do actions depending on the player inputs
*/

#include "systemPlayerActions.hpp"
#include <iostream>

systemPlayerActions::systemPlayerActions(std::shared_ptr<ClientGameNetwork> &network, std::vector<std::pair<std::string, std::pair<float, float>>> &pthsTxtrs, systemEvent &systemEvt, systemSound &systemSnd, Factory &fctry)
: game(network), pathsTextures(pthsTxtrs), sysEvent(systemEvt), sysSound(systemSnd), factory(fctry)
{
}

void systemPlayerActions::update(const int &nb_player)
{
    int state_attack = sysEvent.update(SPACE);
    bool moved = false;
    static bool firing = false;
    
    if (state_attack == CLICKED) {
        if (!factory.getDrawableComponentsList().hasThisComponent(nb_player + 4))
            factory.getDrawableComponentsList().addComponent(nb_player + 4, "Charge_attack");
        factory.getDrawableComponentsList().setComponent(nb_player + 4, "Charge_attack");
        sysSound.update({"Charge1"}, false);
    } else if (state_attack == UNCLICKED) {
        sysSound.update({"Uncharge"}, false);
        if (!factory.getDrawableComponentsList().hasThisComponent(nb_player + 4))
            factory.getDrawableComponentsList().addComponent(nb_player + 4, "Empty");
        factory.getDrawableComponentsList().setComponent(nb_player + 4, "Empty");
        firing = true;
    } else if (state_attack == UNPRESSED && firing == true) {
        firing = false;
        moved = true;
    }
    //Move the charge attack to the player 
    if (!factory.getPositionComponentsList().hasThisComponent(nb_player + 4))
        factory.getPositionComponentsList().addComponent(nb_player + 4, std::pair<float, float>(0, 0));
    if (factory.getPositionComponentsList().hasThisComponent(nb_player + 4) && factory.getPositionComponentsList().hasThisComponent(nb_player))
        factory.getPositionComponentsList().setComponent(nb_player + 4, factory.getPositionComponentsList().getComponent(nb_player));
    //reset to default ship sprite 
    if (factory.getDrawableComponentsList().hasThisComponent(nb_player) && (sysEvent.update(UP) == UNCLICKED))
        factory.getDrawableComponentsList().setComponent(nb_player, pathsTextures[nb_player].first);
    if (factory.getDrawableComponentsList().hasThisComponent(nb_player) && (sysEvent.update(DOWN) == UNCLICKED))
        factory.getDrawableComponentsList().setComponent(nb_player, pathsTextures[nb_player].first);
    //Move in a direction and adapt the sprite 
    if (factory.getPositionComponentsList().hasThisComponent(nb_player) && factory.getDrawableComponentsList().hasThisComponent(nb_player) && (sysEvent.update(RIGHT) == CLICKED || sysEvent.update(RIGHT) == PRESSED)) {
        std::pair<float, float> new_pos = factory.getPositionComponentsList().getComponent(nb_player);
        if (new_pos.first < 1800) {
            new_pos.first += 1;
            factory.getPositionComponentsList().setComponent(nb_player, new_pos);
            factory.getDrawableComponentsList().setComponent(nb_player, pathsTextures[nb_player].first);
            moved = true;
        }
    }
    if (factory.getPositionComponentsList().hasThisComponent(nb_player) && factory.getDrawableComponentsList().hasThisComponent(nb_player) && (sysEvent.update(LEFT) == CLICKED || sysEvent.update(LEFT) == PRESSED)) {
        std::pair<float, float> new_pos = factory.getPositionComponentsList().getComponent(nb_player);
        if (new_pos.first > 0) {
            new_pos.first -= 1;
            factory.getPositionComponentsList().setComponent(nb_player, new_pos);
            factory.getDrawableComponentsList().setComponent(nb_player, pathsTextures[nb_player].first);
            moved = true;
        }
    }
    if (factory.getPositionComponentsList().hasThisComponent(nb_player) && factory.getDrawableComponentsList().hasThisComponent(nb_player) && (sysEvent.update(UP) == CLICKED || sysEvent.update(UP) == PRESSED)) {
        std::pair<float, float> new_pos = factory.getPositionComponentsList().getComponent(nb_player);
        if (new_pos.second > 0) {
            new_pos.second -= 1;
            factory.getPositionComponentsList().setComponent(nb_player, new_pos);
            factory.getDrawableComponentsList().setComponent(nb_player, pathsTextures[nb_player + 4].first);
            moved = true;
        }
    }
    if (factory.getPositionComponentsList().hasThisComponent(nb_player) && factory.getDrawableComponentsList().hasThisComponent(nb_player) && (sysEvent.update(DOWN) == CLICKED || sysEvent.update(DOWN) == PRESSED)) {
        std::pair<float, float> new_pos = factory.getPositionComponentsList().getComponent(nb_player);
        if (new_pos.second < 1000) {
            new_pos.second += 1;
            factory.getPositionComponentsList().setComponent(nb_player, new_pos);
            factory.getDrawableComponentsList().setComponent(nb_player, pathsTextures[nb_player + 8].first);
            moved = true;
        }
    }
    if (moved || firing) {
        game->send(factory, nb_player, firing);
    }
}