/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** create  and move them
*/

#include "systemRandomShoot.hpp"

systemRandomShoot::systemRandomShoot(ComponentTypeList<short int> &interval)
 : _interval(interval)
{
}

systemRandomShoot::~systemRandomShoot()
{
}

void systemRandomShoot::update()
{
    int total = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    short int now = total;

    for (auto interval : _interval.getComponentsMap()) {
        if (!_time.hasThisComponent(interval.first))
            _time.addComponent(interval.first, now);
        if (now - _time.getComponent(interval.first) >= interval.second) {
            _time.setComponent(interval.first, now);
            //SEND SHOT SIGNAL
        }
    }
}