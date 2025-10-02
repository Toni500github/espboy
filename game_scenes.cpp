#include "scenes.hpp"
#include "util.hpp"

const unsigned char rock_icon_Bitmap[] PROGMEM = {
    // 'pixil-frame-0', 16x16px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x0f, 0xe0, 0x3f, 0xf0, 0x3f, 0xf0,
    0x3f, 0xf0, 0x3f, 0xf0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char paper_icon_Bitmap[] PROGMEM = {
    // 'pixil-frame-0 (2)', 16x16px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x04, 0x08, 0x08, 0x08, 0x13, 0xe8, 0x10, 0x08,
    0x17, 0xe8, 0x10, 0x08, 0x17, 0xe8, 0x10, 0x08, 0x10, 0x08, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00
};

const unsigned char scissors_icon_Bitmap[] PROGMEM = {
    // 'pixil-frame-0 (1)', 16x16px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x80, 0x03, 0x00, 0x3a, 0x30, 0x2a, 0x60, 0x3f, 0xc0,
    0x02, 0x00, 0x03, 0x80, 0x02, 0x80, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char ping_pong_Bitmap [] PROGMEM = {
    // 'pixil-frame-0 (3)', 16x16px
    0x00, 0x00, 0x00, 0x00, 0x1b, 0xc0, 0x3b, 0xe0, 0x33, 0xf0, 0x07, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 
    0x00, 0x00, 0x03, 0xc0, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static void load_scene_game(const int& game)
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    display.setCursor(0, 35);
    display.print('<');

    switch (game)
    {
        case GAME_MULTIP_RPS:
        case GAME_SINGLEP_RPS:
            centerText("Rock Paper Scissors", 10);
            display.drawBitmap(35, 35, rock_icon_Bitmap, 16, 16, SSD1306_WHITE);
            display.drawBitmap(55, 32, paper_icon_Bitmap, 16, 16, SSD1306_WHITE);
            display.drawBitmap(75, 35, scissors_icon_Bitmap, 16, 16, SSD1306_WHITE);
            break;
        case GAME_MULTIP_PING_PONG:
            centerText("Ping Pong", 10);
            display.drawBitmap(55, 32, ping_pong_Bitmap, 16, 16, SSD1306_WHITE);
            break;
        default:;
    }

    display.setCursor(SCREEN_WIDTH - 7, 35);
    display.print('>');

    display.display();
}

void load_scene_game_credits()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    centerText("Created on", 10);
    centerText("Toni500github/espboy", 40);

    display.display();
}

void load_scene_main_menu(const int& choice)
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    centerText("EspBoy v0.0.1", 8);

    centerText(choice == SCENE_MAIN_MENU_SINGLEP ? "> Single-Player" : "Single-Player", 35);
    centerText(choice == SCENE_MAIN_MENU_MULTIP ? "> Multi-Player" : "Multi-Player", 45);
    centerText(choice == SCENE_MAIN_MENU_CREDITS ? "> Credits" : "Credits", 55);

    display.display();
}

void load_scene(const int& scene, const int& game)
{
    switch (scene)
    {
        case SCENE_MAIN_MENU:     load_scene_main_menu(game); break;
        case SCENE_SINGLEP_GAMES: load_scene_game(game); break;
        case SCENE_MULTIP_GAMES:  load_scene_game(game); break;
        case SCENE_CREDITS:       load_scene_game_credits();
        default:                  ;
    }
}
