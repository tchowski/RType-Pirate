/*
** EPITECH PROJECT, 2019
** RType
** File description:
** Client
*/

#ifndef client_H_
#define client_H_

#include <set>
#include <iostream>
#include <string>

class Client
{
public:
	Client(int socket_client, std::string &nickame);
	std::string getNickaname();
	void setNickname(std::string &nickame);
	~Client();
	int socket_client_;

protected:
private:
	std::string nickname_;
};

#endif /* !client */
