/*
** EPITECH PROJECT, 2019
** OOP_rtype_2019
** File description:
** Factory | Class Header
*/

#pragma once

#ifndef FACTORY_HPP_
    #define FACTORY_HPP_

#include "ComponentTypeList.hpp"
#include "Component.hpp"
#include "NetworkStruct.hpp"
#include <vector>

class Factory {
    public:
        Factory();
        ~Factory() = default;

        // Getters
        ComponentTypeList<std::pair<float, float>> &getPositionComponentsList();
        ComponentTypeList<short int> &getHorizontalMoveComponentsList();
        ComponentTypeList<std::pair<short int, short int>> &getBounceMoveComponentsList();
        ComponentTypeList<short int> &getTeamComponentsList();
        ComponentTypeList<unsigned int> &getScoreComponentsList();
        ComponentTypeList<std::string> &getAudioComponentsList();
        ComponentTypeList<short int> &getRandomGunComponentsList();
        ComponentTypeList<std::string> &getDrawableComponentsList();
        ComponentTypeList<std::pair<unsigned int, unsigned int>> &getHitboxComponentsList();
        ComponentTypeList<unsigned int> &getInputMoveComponentList();
        std::vector<unsigned int> &getEntityIDs();
        
        // Other methods
        bool entityExists(const unsigned int);
        bool createEntity(const unsigned int, const std::string);
        bool addComponent(const unsigned int, const std::string);
        bool destroyEntity(const unsigned int);
        void destroyEntity(const std::vector<unsigned int>);
        bool removeComponent(unsigned int, std::string);
        unsigned int generateNewUniqueID();
        void updateComponents(network_buffer);
        network_buffer prepareClientNetworkBuffer(bool);
        network_buffer prepareServerNetworkBuffer();


    private:
        unsigned long long int IDcount_;
        ComponentTypeList<std::pair<float, float>> compPosition_;
        ComponentTypeList<std::pair<short int, short int>> compBounceMove_;
        ComponentTypeList<std::pair<unsigned int, unsigned int>> compHitbox_;
        ComponentTypeList<short int> compHorizontalMove_;
        ComponentTypeList<short int> compTeam_;
        ComponentTypeList<short int> compRandomGun_;
        ComponentTypeList<std::string> compAudio_;
        ComponentTypeList<std::string> compDrawable_;
        ComponentTypeList<unsigned int> compScore_;
        ComponentTypeList<unsigned int> compInputMove_;
        std::vector<unsigned int> entityIDs;
        std::vector<unsigned int> toDestroy_;
        std::vector<std::string> toCreate_;

        // Private methods
        std::vector<std::string> tokenizeConfig(const std::string, const char);
        std::vector<unsigned int> networkStrToVector(std::string &str);
        void updateComponentsWithVector(std::vector<std::string> &);
};

#endif /* !FACTORY_HPP_ */
