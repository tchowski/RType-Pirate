/*
** EPITECH PROJECT, 2019
** RType
** File description:
** session
*/

#ifndef Session
#define Session

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <thread>
#include <cstring>

using boost::asio::ip::tcp;

class session
{
public:
    session(boost::asio::io_service &io_service);
    tcp::socket &socket();
    void start();
private:
    void handle_read(const boost::system::error_code &error, size_t bytes_transferred);
    void handle_write(const boost::system::error_code &error);
    tcp::socket socket_;
    enum
    {
        max_length = 1024
    };
    char data_[max_length];
};


#endif /* !session */
