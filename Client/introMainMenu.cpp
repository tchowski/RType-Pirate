/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** Intro of the main menu
*/


#include "IntroMainMenu.hpp"

void setScale(sf::Sprite &sprite, int width, int height)
{
    sf::FloatRect size = sprite.getGlobalBounds();
    sprite.setScale(width / size.width, height / size.height);
}

int playIntro(GraphicalLib &GLib, SoundLib &SLib)
{
    ComponentTypeList<std::string> cpListSounds;
    ComponentTypeList<std::string> cpListMusics;
    ComponentTypeList<std::string> cpDrawable;
    ComponentTypeList<std::pair<float, float>> cpPosition;
    systemEvent sysEvent(GLib);
    systemDraw sysDraw(GLib, cpPosition, cpDrawable);
    systemSound sysSound(SLib, cpListMusics, cpListSounds);
    std::vector<std::pair<std::string, std::pair<float, float>>> pathsTextures =
    {
    {"BackgroundMenu", std::pair<int, int>(0, 0)},
    {"MonsterLeft", std::pair<int, int>(0, 200)},
    {"MonsterRight", std::pair<int, int>(1500, 200)},
    {"Underline", std::pair<int, int>(450, 300)},
    {"Title3", std::pair<int, int>(350, 50)},
    {"CatchPhrase", std::pair<int, int>(1350, 10)},
    {"Play", std::pair<int, int>(350, 950)}
    };
    std::vector<std::string> pathsMusics =
    {
    "MenuIntro",
    "MenuLoop"
    };
    int id = 0;

    for (std::vector<std::pair<std::string, std::pair<float, float>>>::iterator path = pathsTextures.begin();
    path != pathsTextures.end(); path++) {
        cpDrawable.addComponent(id, path->first);
        cpPosition.addComponent(id, path->second);
        id++;
    }
    id = 0;
    for (std::vector<std::string>::iterator path = pathsMusics.begin();
    path != pathsMusics.end(); path++) {
        cpListMusics.addComponent(id, *path);
        id++;
    }
    // sysSound.update({"MenuIntro"}, false);
    while (GLib.isWindowOpen())
    {
        // sysSound.update({"MenuLoop"}, true);
        if (sysEvent.update(CLOSE) == TRUE)
            GLib.destroyWindow();
        if (sysEvent.update(SPACE) == PRESSED) {
            return EXIT_SUCCESS;
        }
        sysDraw.update(true);
    }
    return EXIT_SUCCESS;
}
