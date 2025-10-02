#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <time.h>

#include "scenes.hpp"
#include "util.hpp"

// Declaration for SSD1306 display connected using I2C
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

static int currentButton = 0;
static int lastButton    = 0;

static int choice = SCENE_MAIN_MENU_SINGLEP;
static int min_choice = SCENE_MAIN_MENU_SINGLEP;
static int max_choice = SCENE_MAIN_MENU_CREDITS;

void play_singlep_rps();
void play_multip_rps();
void play_multip_ping_pong();

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

void centerText(const char* text, int y)
{
  int16_t x1, y1;
  uint16_t w, h;
  
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

  int x = (128 - w) / 2;
  
  display.setCursor(x, y);
  display.print(text);
}

void setup() {
  //Serial.begin(115200);
  srand(time(NULL));

  // initialize the OLED object
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
      Serial.println(F("SSD1306 allocation failed"));
      for (;;)
          ;  // Don't proceed, loop forever
  }

  pinMode(LRED_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LWHITE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RRED_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RBLUE_BUTTON_PIN, INPUT_PULLUP);
}

void loop()
{
  display.clearDisplay();
  currentButton = get_current_button();

  switch (currentButton)
  {
    case LRED_BUTTON_PIN: if (choice > min_choice) --choice; delay(130); break;
    case RRED_BUTTON_PIN: if (choice < max_choice) ++choice; delay(130); break;
  }

  load_scene(currentScene, choice);
  if (currentButton == RBLUE_BUTTON_PIN)
  {
    delay(50);
    switch (currentScene)
    {
      case SCENE_MAIN_MENU:
        switch (choice)
        {
          case SCENE_MAIN_MENU_SINGLEP:
            currentScene = SCENE_SINGLEP_GAMES;
            choice = GAME_SINGLEP_RPS;
            min_choice = GAME_SINGLEP_RPS;
            max_choice = GAME_SINGLEP_RPS;
            break;
          case SCENE_MAIN_MENU_MULTIP:
            currentScene = SCENE_MULTIP_GAMES;
            choice = GAME_MULTIP_RPS;
            min_choice = GAME_MULTIP_RPS;
            max_choice = GAME_MULTIP_PING_PONG;
            break;
          case SCENE_MAIN_MENU_CREDITS: currentScene = SCENE_CREDITS;
          default: choice = min_choice = max_choice = -67; // ahahahah...
        }
        break;
      case SCENE_SINGLEP_GAMES:
        switch (choice)
        {
          case GAME_SINGLEP_RPS:
            currentScene = SCENE_NONE;
            play_singlep_rps();
            break;
        }
        break;
      case SCENE_MULTIP_GAMES:
        switch (choice)
        {
          case GAME_MULTIP_RPS:
            currentScene = SCENE_NONE;
            play_multip_rps();
            break;
          case GAME_MULTIP_PING_PONG:
            currentScene = SCENE_NONE;
            play_multip_ping_pong();
            break;
        }
        break;
      default:;
    }
  }

    lastButton = currentButton;
    delay(150);
}

// vim:shiftwidth=2