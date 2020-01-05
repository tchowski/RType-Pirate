/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** wait room for all players to connect to each other in a game
*/

#include "preGameWaitRoom.hpp"
#include <algorithm>
#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
#define d(x) printf("%s\n", x)

void setBackground(const std::vector<bool>& client_states,
    const std::vector<std::pair<std::string, std::pair<float, float>>>& pathsTextures,
    ComponentTypeList<std::string>& cpDrawable,
    ComponentTypeList<std::pair<float, float>>& cpPositions,
    systemSound& sysSound)
{
    static std::vector<bool> save_states = { true, false, false, false };
    std::string path = "";
    std::vector<std::string> names = {
        "Player1_static",
        "Player2_static",
        "Player3_static",
        "Player4_static"
    };

    for (int i = 0; i < NB_MAX_PLAYER; i++)
        if (save_states[i] != client_states[i])
            if (client_states[i])
                sysSound.update({ "HighNoise" });
            else
                sysSound.update({ "BadNoise" });
    for (int i = 0; i < NB_MAX_PLAYER; i++) {
        if (client_states[i]) {
            path += "P" + std::to_string(i + 1);
            if (!cpDrawable.hasThisComponent(i + 1)) {
                cpDrawable.addComponent(i + 1, names[i]);
                for (auto path : pathsTextures)
                    if (path.first == names[i])
                        cpPositions.addComponent(i + 1, path.second);
            }
        } else {
            if (cpDrawable.hasThisComponent(i + 1)) {
                cpDrawable.deleteComponent(i + 1);
                cpPositions.deleteComponent(i + 1);
            }
        }
    }
    save_states = client_states;
    if (cpDrawable.getComponentsMap()[0] != path) {
        cpDrawable.deleteComponent(0);
        cpDrawable.addComponent(0, path);
    }
}

void chooseGameMode(const int& mode,
    const std::vector<std::pair<std::string, std::pair<float, float>>>& pathsTextures,
    ComponentTypeList<std::string>& cpDrawable,
    ComponentTypeList<std::pair<float, float>>& cpPositions)
{
    int id = 0;
    if (mode == SURVIVAL) {
        for (auto spr : cpDrawable.getComponentsMap()) {
            if (spr.second == "Campaign") {
                id = spr.first;
                cpDrawable.deleteComponent(id);
                if (cpPositions.hasThisComponent(id))
                    cpPositions.deleteComponent(id);
                cpDrawable.addComponent(id, "Survival");
                for (auto texture : pathsTextures)
                    if (texture.first == "Survival")
                        cpPositions.addComponent(id, texture.second);
            }
        }
    } else if (mode == CAMPAIGN) {
        for (auto spr : cpDrawable.getComponentsMap()) {
            if (spr.second == "Survival") {
                id = spr.first;
                cpDrawable.deleteComponent(id);
                if (cpPositions.hasThisComponent(id))
                    cpPositions.deleteComponent(id);
                cpDrawable.addComponent(id, "Campaign");
                for (auto texture : pathsTextures)
                    if (texture.first == "Campaign")
                        cpPositions.addComponent(id, texture.second);
            }
        }
    }
}

void displayNicknames(GraphicalLib& GLib, const std::vector<std::string>& nicknames)
{
    std::pair<float, float> pos(420, 530);
    int i = 0;
    for (auto names = nicknames.begin(); i < NB_MAX_PLAYER && names != nicknames.end(); names++) {
        if (names->length() > 0) {
            GLib.addText(*names, pos, "federalescort");
        }
        pos.first += 100;
        pos.second -= 80;
        i++;
    }
}

void print_vector(std::vector<std::string> vector)
{
    for (auto i = vector.begin(); i != vector.end(); ++i)
        std::cout << *i << ' ';
    std::cout << '\n';
}

void resize_vectors(std::vector<std::string>& nicknames, std::vector<bool>& client_states, int i)
{
    nicknames.resize(i);
    // client_states.resize(i);
}

int ConnectToRoom(std::string ip_addr)
{
    int sockfd;
    char buffer[1024];
    std::string hello = "start\n";
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);
    // servaddr.sin_addr.s_addr = INADDR_ANY;
    if (inet_pton(AF_INET, ip_addr.c_str(), &servaddr.sin_addr) <= 0) {
        throw "\nInvalid address/ Address not supported \n";
    }

    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        throw "\nConnection Failed \n";
        return 84;
    }
    int n, len;
    socklen_t sock_;
    sendto(sockfd, (const char*)hello.c_str(), hello.length(), 0, (const struct sockaddr*)&servaddr, sizeof(servaddr));
    printf("Start message sent.\n");
    close(sockfd);
    return 0;
}

int check_start(int sock_room)
{
    char buff[80];
    bzero(buff, sizeof(buff));
    int recv_int = recv(sock_room, buff, sizeof(buff), MSG_DONTWAIT);
    if (recv_int < 0) {

    } else {
        printf("From Server : %s", buff);
        if ((strncmp(buff, "Start Game!\n", 11)) == 0) {
            printf("Client TCP Exit...\n");
            return 1;
        }
    }
    return 0;
}

int getClientsStatesandNames(std::vector<bool>& client_states, std::vector<std::string>& nicknames, int sock_room, int &nbplayer)
{
    long size = 0;
    int ret = recv(sock_room, &size, sizeof(size), MSG_DONTWAIT);
    if (ret < 0) {
        // handle error
    } else {
        size = ntohl(size);
        if (size > 4)
            return 1;
        client_states = { true, false, false, false };
        d("Loop User.");
        nbplayer = size;
        std::cout << size << std::endl;
        for (int i = 0; i < size; ++i) {
            std::string stringRead;
            long length = 0;
            recv(sock_room, &length, sizeof(length), MSG_DONTWAIT);
            length = ntohl(length);
            int cread = 1;
            while (0 < length && cread > 0) {
                char buffer[1024];
                memset(buffer, 0, 1024);
#if __APPLE__
                cread = recv(sock_room, buffer, fmin(sizeof(buffer), length), MSG_DONTWAIT);
#else
                cread = recv(sock_room, buffer, std::min((int)sizeof(buffer), (int)length), MSG_DONTWAIT);
#endif
                std::cout << "String Buffer: " << buffer << std::endl;
                if (cread > 0)
                    stringRead.append(buffer, cread);
                length -= cread;
            }
            if (stringRead.size() >= 1 && stringRead.size() < 10) {
                resize_vectors(nicknames, client_states, i);
                if (nicknames.size() > i)
                    nicknames[i] = stringRead;
                else
                    nicknames.push_back(stringRead);
                if (client_states.size() > i)
                    client_states[i] = true;
                else
                    client_states.push_back(true);
            }
        }
    }
    return 0;
}

void set_struct_serv(struct sockaddr_in* serv_addr, std::string ip_addr)
{
    serv_addr->sin_family = AF_INET;
    serv_addr->sin_port = htons(PORT);
    if (inet_pton(AF_INET, ip_addr.c_str(), &serv_addr->sin_addr) <= 0) {
        throw "\nInvalid address/ Address not supported \n";
    }
}

int connectServer(int &nb_player, const std::string& my_nickname, GraphicalLib& GLib, SoundLib& SLib, std::string ip_addr)
{
    int sock_room;
    char buff[80];
    struct sockaddr_in serv_addr;
    int postest = SURVIVAL;
    if ((sock_room = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket error: %s\n", strerror(errno));
        return (84);
    }
    set_struct_serv(&serv_addr, ip_addr);
    if (connect(sock_room, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("connect error: %s\n", strerror(errno));
    }
    char handshake[7] = "Hello\n";
    if (send(sock_room, handshake, sizeof(buff), 0) < 0) {
        printf("send error: %s\n", strerror(errno));
        exit(84);
    }
    read(sock_room, buff, sizeof(buff));
    bzero(buff, sizeof(buff));
    send(sock_room, my_nickname.c_str(), sizeof(my_nickname.c_str()), 0);
    std::vector<std::string> nicknames;
    std::vector<bool> client_states = { true, false, false, false };
    nicknames.push_back(my_nickname);
    ComponentTypeList<std::pair<float, float>> cpPositions;
    ComponentTypeList<std::string> cpDrawable;
    ComponentTypeList<std::string> cpSounds;
    ComponentTypeList<std::string> cpMusics;
    systemDraw sysDraw(GLib, cpPositions, cpDrawable);
    systemSound sysSound(SLib, cpMusics, cpSounds);
    systemEvent sysEvent(GLib);
    std::vector<std::pair<std::string, std::pair<float, float>>> pathsTextures = {
        { "P1", std::pair<int, int>(0, 0) },
        { "P1P2", std::pair<int, int>(0, 0) },
        { "P1P2P3", std::pair<int, int>(0, 0) },
        { "P1P2P3P4", std::pair<int, int>(0, 0) },
        { "P1P3P4", std::pair<int, int>(0, 0) },
        { "P1P3", std::pair<int, int>(0, 0) },
        { "P1P4", std::pair<int, int>(0, 0) },
        { "Survival", std::pair<int, int>(0, 0) },
        { "Campaign", std::pair<int, int>(0, 0) },
        { "Player1_static", std::pair<int, int>(470, 570) },
        { "Player2_static", std::pair<int, int>(570, 490) },
        { "Player3_static", std::pair<int, int>(670, 410) },
        { "Player4_static", std::pair<int, int>(770, 330) }
    };
    std::vector<std::string> pathsSounds = {
        "PAttack",
        "Uncharge",
        "Charge2",
        "HighNoise",
        "BadNoise"
    };
    std::vector<std::string> pathsMusics = {
        "Server"
    };
    int id = 0;
    int tempsize = 1;
    bool check_nb_player_once = true;
    cpDrawable.addComponent(0, pathsTextures[0].first);
    cpPositions.addComponent(0, pathsTextures[0].second);
    cpDrawable.addComponent(7, pathsTextures[7].first);
    cpPositions.addComponent(7, pathsTextures[7].second);
    for (std::vector<std::string>::iterator path = pathsMusics.begin();
         path != pathsMusics.end(); path++) {
        cpMusics.addComponent(id, *path);
        id++;
    }
    id = 0;
    for (std::vector<std::string>::iterator path = pathsSounds.begin();
         path != pathsSounds.end(); path++) {
        cpSounds.addComponent(id, *path);
        id++;
    }
    //sysSound.update({ "Server" }, false);
    printf("Getting Loop isWindowOpen()\n");
    while (GLib.isWindowOpen()) {
         if (getClientsStatesandNames(client_states, nicknames, sock_room, tempsize) == 1) {
            close(sock_room);
            return postest;
        }
        if (nicknames.size() > 0) {
            if (check_nb_player_once || nicknames[nb_player - 1] != my_nickname) {
                nb_player = tempsize;
                check_nb_player_once = false;
            }
            if (nicknames[nb_player - 1] != my_nickname) {
                int i = nicknames.size() - 1;
                for (; i >= 0 && nicknames[i] != my_nickname; i--);
                nb_player = i + 1;
            }
        }
        if (sysEvent.update(CLOSE) == TRUE)
            GLib.destroyWindow();
        if (sysEvent.update(RETURN) == CLICKED) {
            ConnectToRoom(ip_addr);
            std::cout << " Connect To Room " << std::endl;
        }
        if (sysEvent.update(LEFT) == CLICKED && postest == CAMPAIGN)
            postest = SURVIVAL;
        if (sysEvent.update(RIGHT) == CLICKED && postest == SURVIVAL)
            postest = CAMPAIGN;
        displayNicknames(GLib, nicknames);
        chooseGameMode(postest, pathsTextures, cpDrawable, cpPositions);
        sysDraw.update(true);
        setBackground(client_states, pathsTextures, cpDrawable, cpPositions, sysSound);
    }
    printf("Getting Out\n");
    return EXIT_SUCCESS;
}