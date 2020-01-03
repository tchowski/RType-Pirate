/*
** EPITECH PROJECT, 2019
** SoundLib.hpp
** File description:
** SoundLib
*/

#ifndef SoundLib_CPP_
#define SoundLib_CPP_

#include "SoundLib.hpp"

SoundLib::SoundLib()
{
    std::unordered_map<std::string, std::string> sounds =
    {
    {"MenuIntro", "Audio/menu_intro.wav"},
    {"MenuLoop", "Audio/menu_loop.wav"},
    {"Server", "Audio/server.wav"},
    {"Stage1", "Audio/stage1.wav"},
    {"Boss1", "Audio/boss1.wav"},
    {"Victory1", "Audio/victory1.wav"},
    {"Stage2", "Audio/stage2.wav"},
    {"Boss2", "Audio/boss2.wav"},
    {"Victory2", "Audio/victory2.wav"},
    {"FinalBoss", "Audio/final_boss.wav"},
    {"Credits", "Audio/credits.wav"},
    {"GameOver", "Audio/GameOver.wav"},
    {"PAttack", "Sfx/player_attack.wav"},
    {"PDeath", "Sfx/player_death.wav"},
    {"PLaser", "Sfx/player_laser.wav"},
    {"PRifle", "Sfx/player_rifle.wav"},
    {"PUp1", "Sfx/power_up.wav"},
    {"PUp2", "Sfx/power_up2.wav"},
    {"Uncharge", "Sfx/spring_uncharge.wav"},
    {"BigUncharge", "Sfx/big_spring_uncharge.wav"},
    {"Charge1", "Sfx/charge.wav"},
    {"Charge2", "Sfx/charge_attack.wav"},
    {"BigCharge", "Sfx/big_charged_attack.wav"},
    {"MCharge", "Sfx/monster_charge.wav"},
    {"MDeath1", "Sfx/monster_death1.wav"},
    {"MDeath2", "Sfx/monster_death2.wav"},
    {"MDeath3", "Sfx/monster_death3.wav"},
    {"MDeath4", "Sfx/monster_death4.wav"},
    {"MDeath5", "Sfx/monster_death5.wav"},
    {"MMove", "Sfx/monster_movement.wav"},
    {"MAttack1", "Sfx/monster_attack.wav"},
    {"MAttack2", "Sfx/enemy_attack.wav"},
    {"MLaser1", "Sfx/monster_laser.wav"},
    {"MLaser2", "Sfx/monster_moving_laser.wav"},
    {"MLaser3", "Sfx/monster_big_moving_laser.wav"},
    {"MMissile", "Sfx/monster_missile.wav"},
    {"Electricity", "Sfx/electricity.wav"},
    {"SmallExplosion", "Sfx/small_explosion.wav"},
    {"Explosion", "Sfx/explosion1.wav"},
    {"ExplosionDeath", "Sfx/missile_explosion_death.wav"},
    {"MissileLaunch1", "Sfx/missile_launch1.wav"},
    {"MissileLaunch2", "Sfx/missile_launch2.wav"},
    {"MissileLaunch3", "Sfx/missile_launch3.wav"},
    {"Piston", "Sfx/piston.wav"},
    {"HighNoise", "Sfx/super_high_noise.wav"},
    {"BadNoise", "Sfx/irritating_noise.wav"}
    };
    _alias = sounds;
    current_dir = ".";
}

SoundLib::~SoundLib()
{
}

void SoundLib::setPWD(const std::string &pwd)
{
    current_dir = pwd;
}


bool SoundLib::loadMusic(const std::string &name)
{
    std::vector<std::string> path_dependencies = {"/../../Client/Assets/", "/../Client/Assets/", "/Client/Assets/"};

    if (_alias.find(name) == _alias.end())
        return false;
    for (auto path : path_dependencies)
        if (musicList[name].openFromFile(current_dir + path + _alias[name]))
            return true;
    return false;
}

bool SoundLib::unloadThisMusic(const std::string &name)
{
    musicList.erase(name);
    return true;
}

bool SoundLib::stopCurrentMusic()
{
    if (currentMusic == "")
        return false;
    musicList[currentMusic].stop();
    currentMusic = "";
    return true;
}

const std::string &SoundLib::getCurrentMusic(void)
{
    return currentMusic;
}

bool SoundLib::playSound(const std::string &name)
{
    if (musicList.find(name) == musicList.end())
        return false;
    musicList[name].stop();
    musicList[name].play();
    musicList[name].setLoop(false);
    return true;
}

bool SoundLib::stopSound(const std::string &name)
{
    if (musicList.find(name) == musicList.end())
        return false;
    musicList[name].stop();
    return true;
}

bool SoundLib::startThisMusic(const std::string &name, const bool &loop)
{
    if (musicList.find(name) == musicList.end())
        return false;
    currentMusic = name;
    musicList[name].play();
    musicList[name].setLoop(loop);
    return true;
}

bool SoundLib::isThisMusicPlaying(const std::string &name)
{
    if (musicList.find(name) == musicList.end())
            return false;
    if (musicList[name].getStatus() == sf::SoundSource::Playing)
        return true;
    return false;   
}


#endif /* !ISoundLib_CPP_ */