#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include "rockpaperscissors.hpp"
#include <time.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

enum {
 LRED_BUTTON_PIN = 19,
 LWHITE_BUTTON_PIN = 18,
 RRED_BUTTON_PIN = 26,
 RBLUE_BUTTON_PIN = 25,
};

Moves currentButton = NONE;
Moves lastButton = NONE;

void setup() {
  Serial.begin(9600);
  srand(time(NULL));

  // initialize the OLED object
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  pinMode(LRED_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LWHITE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RRED_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RBLUE_BUTTON_PIN, INPUT_PULLUP);
  print_player_moves(NONE);
}

void loop() {
  display.clearDisplay();
  if (digitalRead(LWHITE_BUTTON_PIN) == LOW)
    currentButton = ROCK;
  else if (digitalRead(LRED_BUTTON_PIN) == LOW)
    currentButton = PAPER;
  else if (digitalRead(RRED_BUTTON_PIN) == LOW)
    currentButton = SCISSORS;
  else if (digitalRead(RBLUE_BUTTON_PIN) == LOW)
    currentButton = DONE;
  
  if (currentButton != DONE)
    print_player_moves(currentButton);
  else if (currentButton == DONE && lastButton != NONE)
  {
    play(lastButton);
    lastButton = currentButton = NONE;
    return;
  }

  lastButton = currentButton;
  display.display();
  delay(100);
}

// vim:shiftwidth=2
