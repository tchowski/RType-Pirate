/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** wait room for all players to connect to each other in a game
*/

#include "Levels.hpp"
#include "ClientGameNetwork.hpp"
#include "Factory.hpp"

int GameOverScreen(GraphicalLib& GLib, SoundLib& SLib, Factory& factory)
{
    ComponentTypeList<std::string> cpMusics;
    systemDraw sysDraw(GLib, factory.getPositionComponentsList(), factory.getDrawableComponentsList());
    systemEvent sysEvent(GLib);
    systemSound sysSound(SLib, cpMusics, factory.getAudioComponentsList());
    std::pair<std::string, std::pair<float, float>> pathsTextures = { "GameOver", std::pair<float, float>(0, 0) };

    factory.getDrawableComponentsList().addComponent(0, pathsTextures.first);
    factory.getPositionComponentsList().addComponent(0, pathsTextures.second);
    cpMusics.addComponent(0, "GameOver");
    while (GLib.isWindowOpen()) {
        if (sysEvent.update(CLOSE) == TRUE)
            GLib.destroyWindow();
        if (sysEvent.update(SPACE) == PRESSED)
            return PLAY;
        sysDraw.update(true);
        sysSound.update({ "GameOver" }, false);
    }
    return EXIT_FAILURE;
}

int VictoryScreen(GraphicalLib& GLib, SoundLib& SLib, Factory& factory)
{
    ComponentTypeList<std::string> cpMusics;
    systemDraw sysDraw(GLib, factory.getPositionComponentsList(), factory.getDrawableComponentsList());
    systemEvent sysEvent(GLib);
    systemSound sysSound(SLib, cpMusics, factory.getAudioComponentsList());
    std::pair<std::string, std::pair<float, float>> pathsTextures = { "Credits", std::pair<float, float>(0, 0) };

    factory.getDrawableComponentsList().addComponent(0, pathsTextures.first);
    factory.getPositionComponentsList().addComponent(0, pathsTextures.second);
    cpMusics.addComponent(0, "Credits");
    while (GLib.isWindowOpen()) {
        if (sysEvent.update(CLOSE) == TRUE)
            GLib.destroyWindow();
        if (sysEvent.update(SPACE) == PRESSED)
            return PLAY;
        sysDraw.update(true);
        sysSound.update({ "Credits" }, false);
    }
    return EXIT_FAILURE;
}

int StageClearScreen1(GraphicalLib& GLib, SoundLib& SLib, Factory& factory)
{
    ComponentTypeList<std::string> cpMusics;
    systemDraw sysDraw(GLib, factory.getPositionComponentsList(), factory.getDrawableComponentsList());
    systemEvent sysEvent(GLib);
    systemSound sysSound(SLib, cpMusics, factory.getAudioComponentsList());
    std::pair<std::string, std::pair<float, float>> pathsTextures = { "LevelPassed1", std::pair<float, float>(0, 0) };

    factory.getDrawableComponentsList().addComponent(0, pathsTextures.first);
    factory.getPositionComponentsList().addComponent(0, pathsTextures.second);
    cpMusics.addComponent(0, "Victory1");
    while (GLib.isWindowOpen()) {
        if (sysEvent.update(CLOSE) == TRUE)
            GLib.destroyWindow();
        if (sysEvent.update(SPACE) == PRESSED)
            return PLAY;
        sysDraw.update(true);
        sysSound.update({ "Victory1" }, false);
    }
    return EXIT_FAILURE;
}

int StageClearScreen2(GraphicalLib& GLib, SoundLib& SLib, Factory& factory)
{
    ComponentTypeList<std::string> cpMusics;
    systemDraw sysDraw(GLib, factory.getPositionComponentsList(), factory.getDrawableComponentsList());
    systemEvent sysEvent(GLib);
    systemSound sysSound(SLib, cpMusics, factory.getAudioComponentsList());
    std::pair<std::string, std::pair<float, float>> pathsTextures = { "LevelPassed2", std::pair<float, float>(0, 0) };

    factory.getDrawableComponentsList().addComponent(0, pathsTextures.first);
    factory.getPositionComponentsList().addComponent(0, pathsTextures.second);
    cpMusics.addComponent(0, "Victory2");
    while (GLib.isWindowOpen()) {
        if (sysEvent.update(CLOSE) == TRUE)
            GLib.destroyWindow();
        if (sysEvent.update(SPACE) == PRESSED)
            return PLAY;
        sysDraw.update(true);
        sysSound.update({ "Victory2" }, false);
    }
    return EXIT_FAILURE;
}

void moveAndDestroyMobs(Factory &factory)
{
    for (int id = 10; id < 100; id++) {
        if (factory.getPositionComponentsList().hasThisComponent(id)) {
            if (factory.getPositionComponentsList().getComponent(id).first < 0) {
                factory.getPositionComponentsList().deleteComponent(id);
                factory.getDrawableComponentsList().deleteComponent(id);
            } else {
                std::pair<float, float> pos = factory.getPositionComponentsList().getComponent(id);
                pos.first -= 0.5f;
                factory.getPositionComponentsList().setComponent(id, pos);
            }
        }
    }
}

int LaunchStage(const int &nb_player, const int& difficulty_max, const std::string& music_name, GraphicalLib& GLib, SoundLib& SLib, Factory& factory)
{
    ComponentTypeList<std::string> cpMusics;
    std::shared_ptr<ClientGameNetwork> game(new ClientGameNetwork);
    systemDraw sysDraw(GLib, factory.getPositionComponentsList(), factory.getDrawableComponentsList());
    systemEvent sysEvent(GLib);
    systemSound sysSound(SLib, cpMusics, factory.getAudioComponentsList());
    std::vector<std::string> pathsSounds = { "PAttack",
        "PDeath",
        "PLaser",
        "PRifle",
        "PUp1",
        "PUp2",
        "Uncharge",
        "BigUncharge",
        "Charge1",
        "Charge2",
        "BigCharge",
        "MCharge",
        "MDeath1",
        "MDeath2",
        "MDeath3",
        "MDeath4",
        "MDeath5",
        "MMove",
        "MAttack1",
        "MAttack2",
        "MLaser1",
        "MLaser2",
        "MLaser3",
        "MMissile",
        "Electricity",
        "SmallExplosion",
        "Explosion",
        "ExplosionDeath",
        "MissileLaunch1",
        "MissileLaunch2",
        "MissileLaunch3",
        "Piston",
        "HighNoise",
        "BadNoise" };
    std::vector<std::pair<std::string, std::pair<float, float>>> pathsTextures = {
        { "Bck_scroll", std::pair<float, float>(0, 0) },
        { "Player1_static", std::pair<int, int>(50, 570) },
        { "Player2_static", std::pair<int, int>(50, 490) },
        { "Player3_static", std::pair<int, int>(50, 410) },
        { "Player4_static", std::pair<int, int>(50, 330) },
        { "Player1_up", std::pair<int, int>(50, 570) },
        { "Player2_up", std::pair<int, int>(50, 490) },
        { "Player3_up", std::pair<int, int>(50, 410) },
        { "Player4_up", std::pair<int, int>(50, 330) },
        { "Player1_down", std::pair<int, int>(50, 570) },
        { "Player2_down", std::pair<int, int>(50, 490) },
        { "Player3_down", std::pair<int, int>(50, 410) },
        { "Player4_down", std::pair<int, int>(50, 330) },
        { "Charge_attack", std::pair<int, int>(50, 50) }
    };
    systemPlayerActions sysPActions(game, pathsTextures, sysEvent, sysSound, factory);
    int id = 0;
    int state_attack = 0;
    bool fired = false;

    for (int i = 0; i < 5; i++) {
        factory.getDrawableComponentsList().addComponent(i, pathsTextures[i].first);
        factory.getPositionComponentsList().addComponent(i, pathsTextures[i].second);
    }
    for (auto sounds : pathsSounds) {
        factory.getAudioComponentsList().addComponent(id, sounds);
        id++;
    }
    cpMusics.addComponent(0, music_name);
    while (GLib.isWindowOpen()) {
        fired = false;
        sysSound.update({ music_name }, false);
        sysPActions.update(nb_player);
        game->receive(factory, nb_player);
        if (sysEvent.update(CLOSE) == TRUE) {
            game->disconnect(nb_player);
            GLib.destroyWindow();
        }
        moveAndDestroyMobs(factory);
        sysDraw.update(true);
    }
    return PLAY;
}
