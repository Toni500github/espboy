#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

enum Winner {
    CPU = 0,
    DRAW,
    PLAYER
};

enum Moves {
    NONE = 10,
    ROCK,
    PAPER,
    SCISSORS,
    DONE
};

void print_winner(Winner winner);
void print_player_moves(Moves player_move);
Winner calculate_winner(Moves computer_move, Moves player_move);
Winner play(Moves player_move);
