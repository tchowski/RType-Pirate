/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** handling sound : music and destroy/spawn sounds
*/


#include "systemSound.hpp"

systemSound::systemSound(SoundLib &sound, ComponentTypeList<std::string> &musics, ComponentTypeList<std::string> &sounds)
:  SLib(sound), myMusics(musics), mySounds(sounds)
{
}

void play(SoundLib &SLib,const std::string &path, const bool &is_sound)
{
    if (!is_sound) {
        SLib.stopCurrentMusic();
        if (!SLib.startThisMusic(path, false)) {
            SLib.loadMusic(path);
            SLib.startThisMusic(path, false);
        }
    } else {
        if (!SLib.playSound(path)) {
            SLib.loadMusic(path);
            SLib.playSound(path);
        }  
    }
}

void systemSound::update(const std::vector<std::string> &names, const bool &wait_for_prev_to_finish)
{
    for (auto component : myMusics.getComponentsMap()) {
         if (std::find(names.begin(), names.end(), component.second) != names.end())
             if (wait_for_prev_to_finish) {
                 if (!SLib.isThisMusicPlaying(SLib.getCurrentMusic()))
                     if (!SLib.isThisMusicPlaying(component.second))
                         play(SLib, component.second, false);
             } else if (!SLib.isThisMusicPlaying(component.second))
                 play(SLib, component.second, false);
    }
    for (auto component : mySounds.getComponentsMap()) {
        if (std::find(names.begin(), names.end(), component.second) != names.end())
            play(SLib, component.second, true);
    }
}
