/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** connection
*/

#ifndef connection
#define connection

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "Client.hpp"
#include "NetworkStruct.hpp"
#include "Factory.hpp"
#include "systemApplyDmg.hpp"
#include "Server/System/systemHitbox.hpp" //allez savoir pourquoi, ne compile pas sans
#include "systemHorizalMove.hpp"
#include "Server/System/systemSpawn.hpp" //allez savoir pourquoi, ne compile pas sans

#define MAX_SIZE 2048
#define WINDOW_X 1920
#define WINDOW_Y 1080
#define QUADTREE_MAX_DEPTH 4
#define QUADTREE_MAX_ENTITY 5

using boost::asio::ip::udp;

class Game
{
public:
	Game();
	Game(const std::string &currentdir, boost::asio::io_service &io_service, std::vector<std::shared_ptr<Client>> Clients, short port = 8080);
	void handle_receive_from(const boost::system::error_code &error, size_t bytes_recvd);
	void handle_send_to(const boost::system::error_code &, size_t);
	bool check_unique(udp::endpoint &sender);
	void start_game(boost::asio::io_service& io_service);
	void add_player();
	std::vector<std::shared_ptr<Client>> get_all_clients();
	bool runGameLoop();
	~Game() = default;
protected:
private:
	std::string current_dir;
	boost::asio::io_service io_service_;
	udp::socket socket_;
	udp::endpoint sender_endpoint_;
	std::vector<udp::endpoint> clients_endpoints_;
	char data_[MAX_SIZE];
	std::vector<std::shared_ptr<Client>> Client_;
	int cpt = 0;
	network_buffer *data_struct;
	Factory factory_;
	systemSpawn sSpawn_;
	systemHitbox sHitbox_;
	systemApplyDmg sApplyDmg_;
	systemHorizalMove sHorizalMove_;
};

#endif /* !connection */