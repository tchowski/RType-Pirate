/*
** EPITECH PROJECT, 2019
** RType
** File description:
** Server
*/

#include "Server.hpp"
#include "Room.hpp"
#include <boost/range/adaptor/indexed.hpp>

Server::Server(int port)
    : port_(port)
{
    int opt;
    if ((master_socket_ = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(master_socket_, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0)
        throw "Setsockopt error";
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_);
    if (bind(master_socket_, (struct sockaddr*)&address, sizeof(address)) < 0)
        throw "Bind error";
    std::cout << "Listening on port " << port_ << std::endl;
    if (listen(master_socket_, 4) < 0)
        throw "Listen error";
    addrlen_ = sizeof(address);
    std::cout << "Waiting for connection..." << std::endl;
}

void print_vector(std::vector<std::string> vector)
{
    for (auto i = vector.begin(); i != vector.end(); ++i)
        std::cout << *i << ' ';
    std::cout << '\n';
}

void Server::loopCommunication(std::string &current_dir)
{
    for (auto& client : Clients_) {
        auto pos = &client - &Clients_[0];
        sd = client->socket_client_;
        if (FD_ISSET(sd, &readfds)) {
            if ((valread = read(sd, message, 1024)) == 0) {
                getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen_);
                printf("Host %s disconnected, ip %s, port %d \n", client->getNickaname().c_str(), inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                char* disconnected = new char[client->getNickaname().length() + 1];
                for (int q = 0; q < nicknames_.size();) {
                    std::string theCurrentWord = nicknames_[q];
                    if (theCurrentWord == client->getNickaname()) {
                        nicknames_.erase(nicknames_.begin() + q);
                    } else {
                        q++;
                    }
                }
                std::cout << "Disconnected vector: ";
                print_vector(nicknames_);
                for (auto& client : Clients_) {
                    long length = htonl(nicknames_.size());
                    write(client->socket_client_, &length, sizeof(length));
                    if (client->socket_client_ != 0) {
                        for (int i = 0; i < nicknames_.size(); ++i) {
                            length = htonl(nicknames_[i].length());
                            write(client->socket_client_, &length, sizeof(length));
                            write(client->socket_client_, nicknames_[i].data(), nicknames_[i].length());
                        }
                    }
                }
                Clients_.erase(Clients_.begin() + pos);
            } else {
                fprintf(stderr, "string %s", message);
                std::string buff = message;
                if (buff.compare("start\n") == 0) {
                    for (auto& client_dc : Clients_) {
                        send(client_dc->socket_client_, "Start Game!\n", strlen("Start Game!\n"), 0);
                    }
                    std::shared_ptr<Room> room(new Room(current_dir, buff, Clients_));
                }
            }
        }
    }
}

void Server::cleanBuffer(char** buffer)
{
    for (int i = 0; (*buffer)[i] != '\0'; i++) {
        if ((*buffer)[i] == '\n') {
            (*buffer)[i] = '\0';
            break;
        }
    }
}

void Server::run(std::string &current_dir)
{
    while (true) {
        FD_ZERO(&readfds);
        FD_SET(master_socket_, &readfds);
        max_sd_ = master_socket_;
        for (auto& client : Clients_) {
            sd = client->socket_client_;
            if (sd > 0)
                FD_SET(sd, &readfds);
            if (sd > max_sd_)
                max_sd_ = sd;
        }
        activity_ = select(max_sd_ + 1, &readfds, NULL, NULL, NULL);
        if ((activity_ < 0) && (errno != EINTR))
            throw "select error";
        if (FD_ISSET(master_socket_, &readfds)) {
            if ((new_socket_ = accept(master_socket_, (struct sockaddr*)&address,
                     (socklen_t*)&addrlen_))
                < 0)
                throw "Accept error";
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n",
                new_socket_, inet_ntoa(address.sin_addr), ntohs(address.sin_port));
            recv(new_socket_, message, 1024, 0);
            fprintf(stderr, "string %s", message);
            if (strncmp(message, "start\n", 5) == 0) {
                for (auto& client_dc : Clients_) {
                    write(client_dc->socket_client_, "Start Game!\n", strlen("Start Game!\n"));
                }
                std::string name_room = Clients_[0]->getNickaname();
                std::shared_ptr<Room> room(new Room(current_dir, name_room, Clients_));
                Clients_.clear();
                nicknames_.clear();
                continue;
            }
            if (send(new_socket_, "Put your nickname: ", 19, 0) < 0) {
                throw "Send error";
            }
            char* buffer = new char[1024];
            recv(new_socket_, buffer, 1024, 0);
            cleanBuffer(&buffer);
            std::string buff = buffer;
            nicknames_.push_back(buff);
            print_vector(nicknames_);
            if (!buff.empty()) {
                std::shared_ptr<Client> c(new Client(new_socket_, buff));
                Clients_.push_back(c);
            }
            // sleep(1);
            for (auto& client : Clients_) {
                long length = htonl(nicknames_.size());
                write(client->socket_client_, &length, sizeof(length));
                if (client->socket_client_ != 0) {
                    for (int i = 0; i < nicknames_.size(); ++i) {
                        length = htonl(nicknames_[i].length());
                        write(client->socket_client_, &length, sizeof(length));
                        write(client->socket_client_, nicknames_[i].data(), nicknames_[i].length());
                    }
                }
            }
        }
        loopCommunication(current_dir);
    }
}

Server::~Server()
{
    delete this;
}
