/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** client main
*/

#include "Factory.hpp"
#include "GraphicalLib.hpp"
#include "IntroMainMenu.hpp"
#include "Levels.hpp"
#include "SoundLib.hpp"
#include "preGameWaitRoom.hpp"

int main(int argc, char* argv[])
{
    Factory factory;
    GraphicalLib GLib;
    SoundLib SLib;
    int game_mode = SURVIVAL;
    int return_value = GAMEOVER;
    int nb_player = 1;
    std::string path(argv[0]);
    std::string name = (argc > 1 ? argv[1] : "You");

    GLib.createWindow();
    path = path.substr(0, path.find_last_of("/"));
    GLib.setPWD(path);
    SLib.setPWD(path);
    if (playIntro(GLib, SLib) == EXIT_FAILURE)
        return EXIT_FAILURE;
    while (GLib.isWindowOpen()) {
        game_mode = connectServer(nb_player, name, GLib, SLib);
        if (game_mode == EXIT_FAILURE)
            return EXIT_FAILURE;
        if (game_mode == SURVIVAL) {
            LaunchStage(nb_player, -1, "Stage1", GLib, SLib, factory);
        } else if (game_mode == CAMPAIGN) {
            while (return_value == GAMEOVER) {
                return_value = LaunchStage(nb_player, 25, "Stage1", GLib, SLib, factory);
                if (return_value == GAMEOVER)
                    GameOverScreen(GLib, SLib, factory);
            }
            StageClearScreen1(GLib, SLib, factory);
            return_value = GAMEOVER;
            while (return_value == GAMEOVER) {
                return_value = LaunchStage(nb_player, 50, "Stage2", GLib, SLib, factory);
                if (return_value == GAMEOVER)
                    GameOverScreen(GLib, SLib, factory);
            }
            StageClearScreen2(GLib, SLib, factory);
            return_value = GAMEOVER;
            while (return_value == GAMEOVER) {
                return_value = LaunchStage(nb_player, 75, "FinalBoss", GLib, SLib, factory);
                if (return_value == GAMEOVER)
                    GameOverScreen(GLib, SLib, factory);
            }
            VictoryScreen(GLib, SLib, factory);
        }
    }
    return EXIT_SUCCESS;
}