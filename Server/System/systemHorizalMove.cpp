/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** create  and move them
*/

#include "systemHorizalMove.hpp"

systemHorizalMove::systemHorizalMove(ComponentTypeList<short int> &cpHorizontalTraj, ComponentTypeList<std::pair<float, float>> &cpPosition)
 : _cpHorizontalTraj(cpHorizontalTraj), _cpPosition(cpPosition)
{

}

void systemHorizalMove::update()
{
    auto cpTraj = _cpHorizontalTraj.getComponentsMap();
    auto cpPos = _cpPosition.getComponentsMap();

    for (auto &it : cpTraj) {
        _cpPosition.setComponent(it.first, std::make_pair(cpPos[it.first].first + it.second, cpPos[it.first].second));
    }
}