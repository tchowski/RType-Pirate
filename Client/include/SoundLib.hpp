/*
** EPITECH PROJECT, 2019
** SoundLib.hpp
** File description:
** SoundLib
*/

#ifndef SoundLib_HPP_
#define SoundLib_HPP_

#include "ISoundLib.hpp"

class SoundLib : public ISoundLib {
	public:
        SoundLib();
	    ~SoundLib();

        const std::string &getCurrentMusic(void);
        bool loadMusic(const std::string &name);
        bool unloadThisMusic(const std::string &name);
        bool stopCurrentMusic();
        bool startThisMusic(const std::string &name, const bool &loop);
        bool isThisMusicPlaying(const std::string &name);
        bool playSound(const std::string &name);
        bool stopSound(const std::string &name);
        void setPWD(const std::string &);

    protected:
    private:
        std::string current_dir;
        std::string currentMusic;
        std::unordered_map<std::string, std::string> _alias;
        std::unordered_map<std::string, sf::Music> musicList;
};

#endif /* !SoundLib_HPP_ */
