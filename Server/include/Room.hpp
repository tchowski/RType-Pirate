/*
** EPITECH PROJECT, 2019
** RType
** File description:
** Room
*/

#ifndef Room_H_
#define Room_H_

#include "Server.hpp"
#include "Thread.hpp"
#include "Client.hpp"

class Room : public Thread {
	public:
		Room(std::string &currentdir, std::string &name, std::vector<std::shared_ptr<Client>> Clients);
		~Room();

	protected:
	private:
		std::string current_dir;
		std::vector<std::shared_ptr<Client>> Clients_;
		std::string name_;
};

#endif /* !Room */
