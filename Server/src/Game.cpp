/*
** EPITECH PROJECT, 2019
** RType
** File description:
** Game
*/

#include "Game.hpp"
#include <iostream>

Game::Game(const std::string &currentdir, boost::asio::io_service &io_service, std::vector<std::shared_ptr<Client>> Clients, short port)
    : current_dir(currentdir)
    , socket_(io_service, udp::v4())
    , Client_(Clients)
    // , sSpawn_(current_dir)
    // , sHitbox_(factory_.getPositionComponentsList(), factory_.getHitboxComponentsList(), QUADTREE_MAX_DEPTH, QUADTREE_MAX_ENTITY)
    // , sApplyDmg_(factory_.getTeamComponentsList())
    // , sHorizalMove_(factory_.getHorizontalMoveComponentsList(), factory_.getPositionComponentsList())
{
    boost::asio::socket_base::reuse_address option(true);
    socket_.set_option(option);
    socket_.bind(udp::endpoint(udp::v4(), port));
    data_struct = new network_buffer;
    start_game(io_service);
    io_service.run();
}

void Game::start_game(boost::asio::io_service& io_service)
{
    std::cout << "• Welcome to Rtype Game •" << std::endl;
    udp::resolver resolver(io_service);

    socket_.async_receive_from(boost::asio::buffer(data_, MAX_SIZE), sender_endpoint_,
        boost::bind(&Game::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

bool Game::check_unique(udp::endpoint& sender)
{
    for (auto i : this->clients_endpoints_) {
        if (i == sender)
            return true;
    }
    return false;
}

void Game::add_player()
{
    // std::cout << sender_endpoint_ << std::endl;
    if (clients_endpoints_.empty() || !check_unique(sender_endpoint_)) {
        std::cout << "Client adresse: " << sender_endpoint_.address().to_string() << std::endl;
        clients_endpoints_.push_back(sender_endpoint_);
    }
}

std::vector<std::shared_ptr<Client>> Game::get_all_clients()
{
    return Client_;
}

void Game::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
{
    add_player();
    data_struct = (network_buffer*)data_;
    for (auto i : clients_endpoints_) {
        // this->runGameLoop();
        if (!error && bytes_recvd > 0) {
            socket_.async_send_to(
                boost::asio::buffer(data_, bytes_recvd), i,
                boost::bind(&Game::handle_send_to, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        } else {
            socket_.async_receive_from(
                boost::asio::buffer(data_, MAX_SIZE), i,
                boost::bind(&Game::handle_receive_from, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        }
    }
}

void Game::handle_send_to(const boost::system::error_code&, size_t bytes_recv)
{
    if (bytes_recv < 0)
        std::cout << "Client disconnected" << std::endl;
    socket_.async_receive_from(
        boost::asio::buffer(data_, MAX_SIZE), sender_endpoint_,
        boost::bind(&Game::handle_receive_from, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

// void Game::runGameLoop()
// {
//     static std::time_t start = 0;
//     std::time_t nowtime = std::time(nullptr);

//     if (nowtime - start > 5) {
//         start = nowtime;
//         factory_.createEntity(factory_.generateNewUniqueID(), sSpawn_.update());
//     }        
//     factory_.updateComponents(*data_struct);
//     sHorizalMove_.update();
//     factory_.destroyEntity(sApplyDmg_.update(sHitbox_.update(WINDOW_X, WINDOW_Y)));
//     *data_struct = factory_.prepareServerNetworkBuffer();
// }
