/*
** EPITECH PROJECT, 2019
** RType
** File description:
** Thread
*/

#include "Thread.hpp"


void Thread::startGameC(const std::string &current_dir, const std::string& tname, std::vector<std::shared_ptr<Client>> Clients)
{
    boost::asio::io_service io_service;
    Game game(current_dir, io_service, Clients, 8081);
    io_service.run();
}

void Thread::start_thread(const std::string &current_dir, const std::string& tname, std::vector<std::shared_ptr<Client>> Clients)
{
    std::thread thrd = std::thread(&Thread::startGameC, this, current_dir, tname, Clients);
    tm_[tname] = thrd.native_handle();
    thrd.detach();
    std::cout << "Thread " << tname << " created:" << std::endl;
}

void Thread::stop_thread(const std::string& tname)
{
    ThreadMap::const_iterator it = tm_.find(tname);
    if (it != tm_.end()) {
        pthread_cancel(it->second);
        tm_.erase(tname);
        std::cout << "Thread " << tname << " killed:" << std::endl;
    }
}