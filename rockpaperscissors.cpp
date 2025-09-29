#include "rockpaperscissors.hpp"
#include "esp32-hal.h"

static void print_count_down(uint8_t n)
{
    display.clearDisplay();
    display.setTextSize(3);
    display.setCursor(55, 28);
    display.print(n);
    display.display();
    delay(850);
}

static char get_move_char(Moves whos_move)
{
    switch (whos_move)
    {
        case ROCK: return 'R';
        case PAPER: return 'P';
        case SCISSORS: return 'S';
    }
    return ' ';
}

static Moves get_cpu_move()
{
    int random = rand() % 3; // 0, 1, or 2
    switch(random)
    {
        case 0: return ROCK;
        case 1: return PAPER;
        case 2: return SCISSORS;
        default: return ROCK; // fallback
    }
}

void print_winner(Winner winner)
{
    display.clearDisplay();
    display.setCursor(18, 28);
    display.setTextSize(2);
    switch (winner)
    {
        case CPU: display.println("CPU Wins"); break;
        case DRAW: display.setCursor(55, 28); display.println("Draw!"); break;
        case PLAYER: display.println("You Win!"); break;
    }
    display.display();
    delay(1500);
}

Winner calculate_winner(Moves computer_move, Moves player_move)
{
    if (computer_move == player_move)
        return DRAW;

    else if ((computer_move == ROCK && player_move == SCISSORS) ||
             (computer_move == SCISSORS && player_move == PAPER) ||
             (computer_move == PAPER && player_move == ROCK))
        return CPU;

    else 
        return PLAYER;
}

void print_player_moves(Moves player_move)
{
    display.clearDisplay();
    display.setCursor(0, 28);
    display.setTextSize(1);
    display.print("Your move: ");
    display.setCursor(70, 25);
    display.setTextSize(2);
    display.print(get_move_char(player_move));

    display.display();
}

void print_moves(Moves computer_move, Moves player_move)
{
    display.clearDisplay();
    display.setCursor(6, 12);
    display.setTextSize(1);
    display.print("You");
    display.setCursor(110, 12);
    display.print("CPU");

    display.setCursor(6, 28);
    display.setTextSize(2);
    display.print(get_move_char(player_move));

    display.setTextSize(1);
    display.setCursor(55, 28);
    display.print("VS");

    display.setCursor(110, 28);
    display.setTextSize(2);
    display.print(get_move_char(computer_move));

    display.display();
    delay(1500);
}

Winner play(Moves player_move)
{
    Moves computer_move = get_cpu_move();
    print_count_down(3);
    print_count_down(2);
    print_count_down(1);
    Winner winner = calculate_winner(computer_move, player_move);
    print_moves(computer_move, player_move);
    print_winner(winner);
    delay(2000);
    return winner;
}
