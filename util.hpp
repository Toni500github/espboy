#ifndef UTIL_HPP
#define UTIL_HPP

#include <Adafruit_SSD1306.h>

#include "scenes.hpp"

extern Adafruit_SSD1306 display;

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

enum
{
    LRED_BUTTON_PIN   = 19,
    LWHITE_BUTTON_PIN = 18,
    RRED_BUTTON_PIN   = 26,
    RBLUE_BUTTON_PIN  = 25,
};

int  get_current_button();
void centerText(const char* text, int y);

#endif
