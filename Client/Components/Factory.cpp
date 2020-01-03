/*
** EPITECH PROJECT, 2019
** OOP_rtype_2019
** File description:
** Factory | Create and Destroy entities
*/

#include "Factory.hpp"
#include "ComponentTypeList.hpp"
#include <bits/stdc++.h>
#include <algorithm>
#include <utility>

Factory::Factory() : IDcount_(0)
{
}

ComponentTypeList<std::pair<float, float>> &Factory::getPositionComponentsList()
{
    return this->compPosition_;
}

ComponentTypeList<short int> &Factory::getHorizontalMoveComponentsList()
{
    return this->compHorizontalMove_;
}

ComponentTypeList<std::pair<short int, short int>> &Factory::getBounceMoveComponentsList()
{
    return this->compBounceMove_;
}

ComponentTypeList<short int> &Factory::getTeamComponentsList()
{
    return this->compTeam_;
}

ComponentTypeList<unsigned int> &Factory::getScoreComponentsList()
{
    return this->compScore_;
}

ComponentTypeList<std::string> &Factory::getAudioComponentsList()
{
    return this->compAudio_;
}

ComponentTypeList<short int> &Factory::getRandomGunComponentsList()
{
    return this->compRandomGun_;
}

ComponentTypeList<std::string> &Factory::getDrawableComponentsList()
{
    return this->compDrawable_;
}

ComponentTypeList<std::pair<unsigned int, unsigned int>> &Factory::getHitboxComponentsList()
{
    return this->compHitbox_;
}

ComponentTypeList<unsigned int>& Factory::getInputMoveComponentList()
{
    return this->compInputMove_;
}

std::vector<std::string> Factory::tokenizeConfig(const std::string config, const char split)
{
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream configStream(config);
    while (getline(configStream, token, split)) // Splitting config string into tokens
    {
        tokens.push_back(token); // Add token into the tokens vector
    }
    return(tokens);
}

bool Factory::createEntity(const unsigned int id, const std::string config)
{
    std::vector<std::string> tokens = this->tokenizeConfig(config, ' ');

    if (tokens.empty()) // if no token (no config)
        return false;
    toCreate_.push_back(config);
    for (unsigned int it = 0; it < tokens.size(); it++)
    {
        if (tokens[it] == COMPONENT_POSITION)
        {
            compPosition_.addComponent(id, std::make_pair(std::stof(tokens[it + 1]), std::stof(tokens[it + 2])));
            it += 2;
            continue;
        }
        else if (tokens[it] == COMPONENT_HORIZONTAL_MOVE)
        {
            compHorizontalMove_.addComponent(id, std::stoi(tokens[it + 1]));
            ++it;
            continue;
        }
        else if (tokens[it] == COMPONENT_BOUNCE_MOVE)
        {
            compBounceMove_.addComponent(id, std::make_pair(std::stoi(tokens[it + 1]), std::stoi(tokens[it + 2])));
            it += 2;
            continue;
        }
        else if (tokens[it] == COMPONENT_TEAM)
        {
            compTeam_.addComponent(id, std::stoi(tokens[it + 1]));
            ++it;
            continue;
        }
        else if (tokens[it] == COMPONENT_SCORE)
        {
            compScore_.addComponent(id, std::stoi(tokens[it + 1]));
            ++it;
            continue;
        }
        else if (tokens[it] == COMPONENT_AUDIO)
        {
            compAudio_.addComponent(id, tokens[it + 1]);
            ++it;
            continue;
        }
        else if (tokens[it] == COMPONENT_RANDOM_GUN)
        {
            compRandomGun_.addComponent(id, std::stoi(tokens[it + 1]));
            ++it;
            continue;
        }
        else if (tokens[it] == COMPONENT_DRAWABLE)
        {
            compDrawable_.addComponent(id, tokens[it + 1]);
            ++it;
            continue;
        }
        else if (tokens[it] == COMPONENT_HITBOX)
        {
            compHitbox_.addComponent(id, std::make_pair(std::stoi(tokens[it + 1]), std::stoi(tokens[it + 2])));
            it += 2;
            continue;
        }
    }
    this->entityIDs.push_back(id);
    return true;
}

bool Factory::destroyEntity(const unsigned int entityID)
{
    if (this->entityExists(entityID) == false)
        return false;
    this->compPosition_.deleteComponent(entityID);
    this->compHorizontalMove_.deleteComponent(entityID);
    this->compBounceMove_.deleteComponent(entityID);
    this->compTeam_.deleteComponent(entityID);
    this->compScore_.deleteComponent(entityID);
    this->compAudio_.deleteComponent(entityID);
    this->compRandomGun_.deleteComponent(entityID);
    this->compDrawable_.deleteComponent(entityID);
    this->compHitbox_.deleteComponent(entityID);
    this->compInputMove_.deleteComponent(entityID);
    this->entityIDs.erase(std::remove(entityIDs.begin(), entityIDs.end(), entityID), entityIDs.end());
    toDestroy_.push_back(entityID);
    return true;
}

void Factory::destroyEntity(const std::vector<unsigned int> entityIDs)
{
    for (auto entityID : entityIDs)
    {
        this->destroyEntity(entityID);
    }
}

bool Factory::addComponent(const unsigned int id, const std::string config)
{
    std::vector<std::string> tokens = this->tokenizeConfig(config, ' ');

    if (tokens.empty()) // if no token (no config)
        return false;
    if (tokens.size() == 3 and tokens[0] == COMPONENT_POSITION)
    {
        compPosition_.addComponent(id, std::make_pair(std::stof(tokens[1]), std::stof(tokens[2])));
        return true;
    }
    else if (tokens.size() == 2 and tokens[0] == COMPONENT_HORIZONTAL_MOVE)
    {
        compHorizontalMove_.addComponent(id, std::stoi(tokens[1]));
        return true;
    }
    else if (tokens.size() == 3 and tokens[0] == COMPONENT_BOUNCE_MOVE)
    {
        compBounceMove_.addComponent(id, std::make_pair(std::stoi(tokens[1]), std::stoi(tokens[2])));
        return true;
    }
    else if (tokens.size() == 2 and tokens[0] == COMPONENT_TEAM)
    {
        compTeam_.addComponent(id, std::stoi(tokens[1]));
        return true;
    }
    else if (tokens.size() == 2 and tokens[0] == COMPONENT_SCORE)
    {
        compScore_.addComponent(id, std::stoi(tokens[1]));
        return true;
    }
    else if (tokens.size() == 2 and tokens[0] == COMPONENT_AUDIO)
    {
        compAudio_.addComponent(id, tokens[1]);
        return true;
    }
    else if (tokens.size() == 2 and tokens[0] == COMPONENT_RANDOM_GUN)
    {
        compRandomGun_.addComponent(id, std::stoi(tokens[1]));
        return true;
    }
    else if (tokens.size() == 2 and tokens[0] == COMPONENT_DRAWABLE)
    {
        compDrawable_.addComponent(id, tokens[1]);
        return true;
    }
    else if (tokens.size() == 3 and tokens[0] == COMPONENT_HITBOX)
    {
        compHitbox_.addComponent(id, std::make_pair(std::stoi(tokens[1]), std::stoi(tokens[2])));
        return true;
    } else if (tokens.size() == 2 and tokens[0] == COMPONENT_INPUTMOVE) {
        compInputMove_.addComponent(id, id);
    }
    return false;
}

bool Factory::removeComponent(const unsigned int id, const std::string component)
{
    if (component.empty()) // if no @param component given
        return false;
    if (component == COMPONENT_POSITION)
    {
        compPosition_.deleteComponent(id);
        return true;
    }
    else if (component == COMPONENT_HORIZONTAL_MOVE)
    {
        compHorizontalMove_.deleteComponent(id);
        return true;
    }
    else if (component == COMPONENT_BOUNCE_MOVE)
    {
        compBounceMove_.deleteComponent(id);
        return true;
    }
    else if (component == COMPONENT_TEAM)
    {
        compTeam_.deleteComponent(id);
        return true;
    }
    else if (component == COMPONENT_SCORE)
    {
        compScore_.deleteComponent(id);
        return true;
    }
    else if (component == COMPONENT_AUDIO)
    {
        compAudio_.deleteComponent(id);
        return true;
    }
    else if (component == COMPONENT_RANDOM_GUN)
    {
        compRandomGun_.deleteComponent(id);
        return true;
    }
    else if (component == COMPONENT_DRAWABLE)
    {
        compDrawable_.deleteComponent(id);
        return true;
    }
    else if (component == COMPONENT_HITBOX)
    {
        compHitbox_.deleteComponent(id);
        return true;
    }
    else if (component == COMPONENT_INPUTMOVE)
    {
        compInputMove_.deleteComponent(id);
        return true;
    }
    return false;
}

bool Factory::entityExists(const unsigned int id)
{
    for (auto entityID : this->entityIDs)
    {
        if (entityID == id)
            return true;
    }
    return false;
}

unsigned int Factory::generateNewUniqueID()
{
    return (++IDcount_);
}

std::vector<unsigned int> Factory::networkStrToVector(std::string &str)
{
    std::vector<unsigned int> vec;
    int size = str.size();
    int j = 0;
    // assigner = travail pas ses projets, pas cool pour les mates #LORE
    unsigned int astekpascool = 0;

    for (int i = 0; i < size && j < size; i++) {
        while (j < size && str[j] != ' ')
            j++;
        while (i != j) {
            astekpascool *= 10;
            astekpascool += str[i] - '0';
            i++;
        }
        vec.push_back(astekpascool);
        astekpascool = 0;
        j += 1;
    }
    /*/ for debug, uncomment :
    for (auto &it: vec) {
        std::cout << it << std::endl;
    }
    /////////*/
    return vec;
}

void Factory::updateComponentsWithVector(std::vector<std::string> &tokens)
{
    unsigned int id = 0;

    for (unsigned int it = 0; it < tokens.size(); it++)
    {
        if (tokens[it] == "ID") {
            id = std::stoi(tokens[it + 1]);
            it += 1;
            continue;
        }
        if (this->entityExists(id)) {
            if (tokens[it] == COMPONENT_POSITION)
            {
                compPosition_.setComponent(id, std::make_pair(std::stoi(tokens[it + 1]), std::stoi(tokens[it + 2])));
                it += 2;
                continue;
            }
            else if (tokens[it] == COMPONENT_HORIZONTAL_MOVE)
            {
                compHorizontalMove_.setComponent(id, std::stoi(tokens[it + 1]));
                ++it;
                continue;
            }
            else if (tokens[it] == COMPONENT_BOUNCE_MOVE)
            {
                compBounceMove_.setComponent(id, std::make_pair(std::stoi(tokens[it + 1]), std::stoi(tokens[it + 2])));
                it += 2;
                continue;
            }
            else if (tokens[it] == COMPONENT_TEAM)
            {
                compTeam_.setComponent(id, std::stoi(tokens[it + 1]));
                ++it;
                continue;
            }
            else if (tokens[it] == COMPONENT_SCORE)
            {
                compScore_.setComponent(id, std::stoi(tokens[it + 1]));
                ++it;
                continue;
            }
            else if (tokens[it] == COMPONENT_AUDIO)
            {
                compAudio_.setComponent(id, tokens[it + 1]);
                ++it;
                continue;
            }
            else if (tokens[it] == COMPONENT_RANDOM_GUN)
            {
                compRandomGun_.setComponent(id, std::stoi(tokens[it + 1]));
                ++it;
                continue;
            }
            else if (tokens[it] == COMPONENT_DRAWABLE)
            {
                compDrawable_.setComponent(id, tokens[it + 1]);
                ++it;
                continue;
            }
            else if (tokens[it] == COMPONENT_HITBOX)
            {
                compHitbox_.setComponent(id, std::make_pair(std::stoi(tokens[it + 1]), std::stoi(tokens[it + 2])));
                it += 2;
                continue;
            }
        }
    }
}

void Factory::updateComponents(network_buffer network)
{
    if (network.fired) { // info client : le client a tiré
        std::string str("POSITION " + std::to_string(network.pos.second.first) + " " + std::to_string(network.pos.second.first));
        this->createEntity(generateNewUniqueID(), str + " HEALTH 20 TEAM 2 AUDIO PRifle DRAWABLE PlayerShot HITBOX 12 4 HORIZAL 1");
    } else if (network.pos.second.first != 0 && network.pos.second.second != 0) { //info client : nouvelle pos client
        compPosition_.setComponent(network.pos.first, network.pos.second);
    } else { //info serveur : les modifs à faire
        if (!network.construct.empty()) {
            this->createEntity(generateNewUniqueID(), network.construct);
        }
        if (!network.update.empty()) {
            std::vector<std::string> tokens = this->tokenizeConfig(network.update, ' ');
            updateComponentsWithVector(tokens);
        }   
        if (!network.destruct.empty()) {
            this->destroyEntity(networkStrToVector(network.destruct));
        }
    }
}

network_buffer Factory::prepareClientNetworkBuffer(bool fired)
{
    network_buffer buff;
    if (fired)
        buff.fired = true;
    else
        buff.fired = false;
    auto map = compInputMove_.getComponentsMap();
    auto posmap = compPosition_.getComponentsMap();
    for (auto &it : map) {
        buff.pos.first = it.first;
        buff.pos.second.first = posmap[it.second].first;
        buff.pos.second.second = posmap[it.second].second;
        break;
    }
    return buff;
}

network_buffer Factory::prepareServerNetworkBuffer()
{
    unsigned int i = 0;
    network_buffer buff;

    buff.fired = false;
    if (!toDestroy_.empty()) { // vide la pile d'entity a destroy
        while (1) {
            buff.destruct += std::to_string(toDestroy_[i]);
            i++;
            if (i == toDestroy_.size())
                break;
            buff.destruct += ' ';
        }
        toDestroy_.clear();
    }
    if (!toCreate_.empty()) { // destack de 1 la pile d'entity a create
        buff.construct = toCreate_[toCreate_.size() - 1];
        toCreate_.pop_back();
    }
    auto posMap = compPosition_.getComponentsMap();
    for (auto &it : posMap) { //update tous les components ayant une position
        buff.update += "ID " + std::to_string(it.first);
        if (compPosition_.hasThisComponent(it.first))
            buff.update += " POSITION " + std::to_string(compPosition_.getComponent(it.first).first) + " " + std::to_string(compPosition_.getComponent(it.first).second);
        if (compHorizontalMove_.hasThisComponent(it.first))
            buff.update += " HORIZAL " + std::to_string(compHorizontalMove_.getComponent(it.first));
        if (compTeam_.hasThisComponent(it.first))
            buff.update += " TEAM " + std::to_string(compTeam_.getComponent(it.first));
        if (compRandomGun_.hasThisComponent(it.first))
            buff.update += " RANDOMGUN " + std::to_string(compRandomGun_.getComponent(it.first));
        if (compDrawable_.hasThisComponent(it.first))
            buff.update += " DRAWABLE " + compDrawable_.getComponent(it.first);
        if (compAudio_.hasThisComponent(it.first))
            buff.update += " AUDIO " + compAudio_.getComponent(it.first);
        if (compScore_.hasThisComponent(it.first))
            buff.update += " SCORE " + std::to_string(compScore_.getComponent(it.first));
        if (compInputMove_.hasThisComponent(it.first))
            buff.update += " INPUTMOVE " + std::to_string(compInputMove_.getComponent(it.first));
        if (compBounceMove_.hasThisComponent(it.first))
            buff.update += " BOUNCE " + std::to_string(compBounceMove_.getComponent(it.first).first) + " " + std::to_string(compBounceMove_.getComponent(it.first).second);
        if (compHitbox_.hasThisComponent(it.first))
            buff.update += " HITBOX " + std::to_string(compHitbox_.getComponent(it.first).first) + " " + std::to_string(compHitbox_.getComponent(it.first).second);
        buff.update += " ";
    }
    if (buff.update.back() == ' ')
        buff.update.pop_back();
    return buff;
}