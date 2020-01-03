/*
** EPITECH PROJECT, 2019
** RType
** File description:
** Thread
*/

#ifndef Thread_H_
#define Thread_H_

#include "Game.hpp"
#include <chrono>
#include <cstring>
#include <iostream>
#include <mutex>
#include <pthread.h>
#include <thread>
#include <unordered_map>

class Thread {
public:
    void start_thread(const std::string &current_dir, const std::string& tname, std::vector<std::shared_ptr<Client>> Clients);
    void startGameC(const std::string &current_dir, const std::string& tname, std::vector<std::shared_ptr<Client>> Clients);
    void stop_thread(const std::string& tname);

protected:
private:
    typedef std::unordered_map<std::string, pthread_t> ThreadMap;
    ThreadMap tm_;
};

#endif /* !Thread */
