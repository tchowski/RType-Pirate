/*
** EPITECH PROJECT, 2019
** OOP_rtype_2019
** File description:
** Mob "Bydos" Header file
*/

#pragma once

#ifndef MOB_BYDOS_HPP_
    #define MOB_BYDOS_HPP_

#include "../IMob.hpp"
#include <cstddef>
#include <string>

#define CONFIG "POSITION 1900 400 DRAWABLE Enemy1 HITBOX 20 24 RANDOMGUN 100 HORIZAL 1 TEAM 1 AUDIO MDeath1"

class MobBydos : public IMob {
	public:
		MobBydos();
		~MobBydos() = default;
};

extern "C" {
	std::string create();
}

#endif /* !MOB_BYDOS_HPP */
