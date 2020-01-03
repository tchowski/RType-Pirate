/*
** EPITECH PROJECT, 2019
** ISoundLib.hpp
** File description:
** ISoundLib
*/

#ifndef ISoundLib_HPP_
#define ISoundLib_HPP_

#include <SFML/Audio.hpp>
#include <utility>
#include <unordered_map>

class ISoundLib {
	public:
		virtual ~ISoundLib() = default;
        virtual const std::string &getCurrentMusic(void) = 0;
        virtual bool loadMusic(const std::string &name) = 0;
        virtual bool unloadThisMusic(const std::string &name) = 0;
        virtual bool stopCurrentMusic() = 0;
        virtual bool startThisMusic(const std::string &name, const bool &loop) = 0;
        virtual bool isThisMusicPlaying(const std::string &name) = 0;
        virtual bool playSound(const std::string &name) = 0;
        virtual bool stopSound(const std::string &name) = 0;
        virtual void setPWD(const std::string &) = 0;

    protected:
    private:
        std::string currentMusic;
        std::unordered_map<std::string, std::string> _alias;
        std::unordered_map<std::string, sf::Music> musicList;
};

#endif /* !ISoundLib_HPP_ */
