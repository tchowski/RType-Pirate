/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** hitbox handle thanks to quad tree
*/

#include "systemApplyDmg.hpp"

systemApplyDmg::systemApplyDmg(ComponentTypeList<short int> &cpTeam) : _cpTeam(cpTeam)
{
}

std::vector<unsigned int> &systemApplyDmg::update(std::vector<std::pair<unsigned int, unsigned int>> &hitboxVec)
{
    _destroy.clear();
    auto map = _cpTeam.getComponentsMap();
    for (long unsigned int it = 0; it != hitboxVec.size(); it++) {
        if (map[hitboxVec[it].first] && map[hitboxVec[it].second]) {
            if (map[hitboxVec[it].first] != map[hitboxVec[it].second]) {
                    _destroy.push_back(hitboxVec[it].second);
                    _destroy.push_back(hitboxVec[it].first);
            }
        }
    }
    return _destroy;
}
