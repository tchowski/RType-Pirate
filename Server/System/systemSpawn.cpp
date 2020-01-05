/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** spawn an enemy, box or wall
*/

#include "systemSpawn.hpp"
#include "IMob.hpp"
#include <dlfcn.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

systemSpawn::systemSpawn(std::string &currentdir)
    : current_dir(currentdir), _start(std::clock()), _spawntype(0)
{
    srand(time(0));
    _handler.push_back(this->openMobLibrary(this->mobCompletePath(MOB_BYDOS)));
}

systemSpawn::~systemSpawn()
{
    closeMobLibrary(_handler);
}

/**
 * @brief           Return a randomly generated number between 0 and MOB_NUMBER
 *                  (MOB_NUMBER value out)
 * @return          Random integer
 */
const int systemSpawn::getRandMob() const
{
    return (rand() % MOB_NUMBER);
}

/**
 * @brief           Returns complete path using the mob name
 * @param name      Name of the mob needed
 * @return          Mob dynamic library relative path
 * 
 * For example 'pikachu' gives '../../Mobs/lib_rtype_pikachu.so'
 */
std::string systemSpawn::mobCompletePath(const std::string name)
{
    std::vector<std::string> path_dependencies = {"/../../Server/Mobs/lib_rtype_", "/../Server/Mobs/lib_rtype_", "/Server/Mobs/lib_rtype_"};
    std::ifstream file;
  
    for (auto dep : path_dependencies) {
        file.open(std::string(current_dir + dep + name + ".so"), std::ifstream::in);
        if (file.good()) {
            return std::move(std::string(current_dir + dep + name + ".so"));
        }
    }
    return std::move(std::string(name));
}

/**
 * @brief           Open the @param path dynamic library and returns it
 * @param path      Mob Library name to open dynamicly
 * @return          Library handler
 * 
 * Exits in failure when error found (Cannot open lib, lib doesn't exist, ...)
 */
void *systemSpawn::openMobLibrary(const std::string &path)
{
    void *handler = dlopen(path.c_str(), RTLD_LAZY);
    if (!handler) // is null
    {
        fputs(dlerror(), stderr); // print error message
        exit(84);                 // error code
    }
    return handler;
}

/**
 * @brief           Closes the @param lib dynamic library
 * @param lib       Mob library to close
 * @return          None
 */
void systemSpawn::closeMobLibrary(void *lib)
{
    dlclose(lib);
}

/**
 * @brief           Closes the complete list of @param libs dynamic libraries
 * @param libs      Mob libraries to close
 * @return          None
 */
void systemSpawn::closeMobLibrary(std::vector<void *>libs)
{
    for (auto lib : libs)
        this->closeMobLibrary(lib);
}

/**
 * @brief           Generate the config line of the @param mob mob given using
 *                  the dynamic library's 'create' function
 * @param mob       MobHandler is an enum. Rank of the needed mob in the vector
 * @return          Configuration string needed by factory to build mob entity
 * 
 * Exits in error if failure (dlsym error, ...)
 */
std::string systemSpawn::createNewMob(const int mob)
{
    char *error;
    create_t *ftCreate = (create_t *)dlsym(this->_handler[mob], "create");

    error = dlerror(); // get dlsym error log if exist
    if (error)
    {
        fputs(error, stderr); // print error msg
        exit(84); // exit in error
    }
    return ftCreate();
}

std::string systemSpawn::update()
{
    _str.clear();
    //_since = (std::clock() - _start) / (double)CLOCKS_PER_SEC;
    //_str = this->createNewMob(this->getRandMob()); // generate new mob configuration line randomly
    //if (_since > 3) {
        //_start = std::clock();
        std::srand(std::time(nullptr));
        int random = std::rand() % 900;
        if (_spawntype == 1) {
            //CRÉATION D'UNE BOX
            _str = "POSITION 2000 " + std::to_string(random) + " HORIZAL 1 HEALTH 40 TEAM 3 DRAWABLE DestructibleWall HITBOX 20 20";
            _spawntype++;
        } else if (_spawntype == 2) {
            _str = "POSITION 2000 " + std::to_string(random) + " HORIZAL 1 HEALTH 40 TEAM 3 DRAWABLE Wall HITBOX 20 20";
            _spawntype = 0;
        }
        return _str;
    //}
    //return _str;
}
