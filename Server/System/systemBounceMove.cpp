/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** create  and move them
*/

#include "systemBounceMove.hpp"

systemBounceMove::systemBounceMove(ComponentTypeList<std::pair<float, float>> &cpTraj, ComponentTypeList<std::pair<float, float>> &cpPosition)
 : _cpTraj(cpTraj), _cpPosition(cpPosition)
{
}

systemBounceMove::~systemBounceMove()
{

}

void systemBounceMove::update()
{
    auto cpTraj = _cpTraj.getComponentsMap();
    auto cpPos = _cpPosition.getComponentsMap();

    for (auto &it : cpTraj) {
        if (!_cpVerticalUp.hasThisComponent(it.first))
            _cpVerticalUp.addComponent(it.first, true);
        if (_cpVerticalUp.getComponent(it.first) == true)
            if (cpPos[it.first].second + it.second.second > 1080)
                _cpVerticalUp.setComponent(it.first, false);
        else
            if (cpPos[it.first].second - it.second.second < 0)
                _cpVerticalUp.setComponent(it.first, true); 
        if (_cpVerticalUp.getComponent(it.first) == true)
            _cpPosition.setComponent(it.first, std::make_pair(cpPos[it.first].first + it.second.first, cpPos[it.first].second + it.second.second));
        if (_cpVerticalUp.getComponent(it.first) == false)
            _cpPosition.setComponent(it.first, std::make_pair(cpPos[it.first].first + it.second.first, cpPos[it.first].second - it.second.second));
    }
}