#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include "rockpaperscissors.hpp"
#include "util.hpp"
#include "scenes.hpp"
#include "game_scenes.hpp"
#include "rockpaperscissors_multi.hpp"
#include <time.h>

// Declaration for SSD1306 display connected using I2C
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

static int currentButton = 0;
static int lastButton = 0;

int get_current_button()
{
  if (digitalRead(LWHITE_BUTTON_PIN) == LOW)
    return LWHITE_BUTTON_PIN;

  if (digitalRead(LRED_BUTTON_PIN) == LOW)
    return LRED_BUTTON_PIN;

  if (digitalRead(RRED_BUTTON_PIN) == LOW)
    return RRED_BUTTON_PIN;

  if (digitalRead(RBLUE_BUTTON_PIN) == LOW)
    return RBLUE_BUTTON_PIN;

  return -1;
}

void setup() {
  //Serial.begin(115200);
  srand(time(NULL));

  // initialize the OLED object
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  pinMode(LRED_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LWHITE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RRED_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RBLUE_BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  display.clearDisplay();
  currentButton = get_current_button();
  switch (currentButton)
  {
    case LRED_BUTTON_PIN: if (selectedGame > GAME_NONE) --selectedGame; break; 
    case RRED_BUTTON_PIN: if (selectedGame <= GAME_CREDITS) ++selectedGame; break;
  }

  load_scene(currentScene);
  if (currentButton == RBLUE_BUTTON_PIN)
  {
    delay(200);
    switch (selectedGame)
    {
      case GAME_RPS:
        currentScene = SCENE_NONE;
        rps_play_game();
        break;
      case GAME_MULTI_RPS:
        currentScene = SCENE_NONE;
        rps_multi_play_game();
        break;
      default:;
    }
  }

  lastButton = currentButton;
  delay(50);
}

// vim:shiftwidth=2
