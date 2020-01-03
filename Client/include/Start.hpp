/*
** EPITECH PROJECT, 2019
** RType
** File description:
** Start
*/

#ifndef start_H_
#define start_H_

#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#define PORT_GAME 8080

class Start {
	public:
		Start();
		~Start();
		int ConnectToRoom();

	protected:
	private:
};

#endif /* !Start */
