#include "game_scenes.hpp"
#include "util.hpp"

void load_rps_scene_game()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    display.setCursor(6, 4);
    display.print("Rock Paper Scissors");

    display.setCursor(20, 16);
    display.print("(Single-player)");

    display.setCursor(0, 34);
    display.print('<');

    display.setCursor((SCREEN_WIDTH-15)/2, 34);
    display.print("RPS");

    display.setCursor(SCREEN_WIDTH-10, 34);
    display.print('>');

    display.display();
}

void load_credits_scene_game()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    display.setCursor((SCREEN_WIDTH-55)/2, 15);
    display.println("Created on");

    display.setCursor(4, 50);
    display.print("Toni500github/espboy");

    display.setCursor(0, 34);
    display.print('<');

    display.setCursor(SCREEN_WIDTH-10, 34);
    display.print('>');

    display.display();
}

void load_scene_game(int game)
{
    switch (game)
    {
        case GAME_NONE:
        case GAME_RPS: load_rps_scene_game(); break;
        case GAME_CREDITS: load_credits_scene_game(); break;
    }
}

void load_scene(int scene)
{
    switch (scene)
    {
        case SCENE_MAINMENU: load_scene_game(selectedGame); break;
        default:;
    }
}
