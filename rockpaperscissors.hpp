#ifndef ROCKPAPERSCISSORSROCKPAPERSCISSORS_HPP
#define ROCKPAPERSCISSORSROCKPAPERSCISSORS_HPP

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

void rps_play_game();

#endif
