/*
** EPITECH PROJECT, 2019
** OOP_rtype_2019
** File description:
** Mob Interface | General structure of a Mob object
*/

#pragma once

#ifndef IMOB_HPP_
	#define IMOB_HPP_

#include <string>

class IMob {
	public:
		// IMob();
		virtual ~IMob() = default;
};

// @brief		Typedef used to generate mobs for child classes
typedef std::string create_t();

#endif /* !IMOB_HPP_ */