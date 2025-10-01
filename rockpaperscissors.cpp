#include "util.hpp"

enum Winner
{
    CPU = 0,
    DRAW,
    PLAYER
};

enum Moves
{
    NONE = 10,
    ROCK,
    PAPER,
    SCISSORS,
    DONE
};

static void print_count_down(uint8_t n)
{
    display.clearDisplay();
    display.setTextSize(3);
    char str[16];
    sprintf(str, "%hu", n);
    centerText(str, 28);
    display.display();
    delay(850);
}

static char get_move_char(Moves whos_move)
{
    switch (whos_move)
    {
        case ROCK:     return 'S';
        case PAPER:    return 'C';
        case SCISSORS: return 'F';
    }
    return ' ';
}

static Moves get_cpu_move()
{
    int random = rand() % 3;  // 0, 1, or 2
    switch (random)
    {
        case 0:  return ROCK;
        case 1:  return PAPER;
        case 2:  return SCISSORS;
        default: return ROCK;  // fallback
    }
}

static void print_winner(Winner winner)
{
    display.clearDisplay();
    display.setTextSize(2);
    switch (winner)
    {
        case CPU:    centerText("CPU Wins", 28); break;
        case DRAW:   centerText("Draw!", 28); break;
        case PLAYER: centerText("You Win!", 28); break;
    }
    display.display();
    delay(1500);
}

static Winner calculate_winner(Moves computer_move, Moves player_move)
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

static void print_player_moves(Moves player_move)
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

static void print_moves(Moves computer_move, Moves player_move)
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
    centerText("VS", 28);

    display.setCursor(110, 28);
    display.setTextSize(2);
    display.print(get_move_char(computer_move));

    display.display();
    delay(1500);
}

static int currentButton = NONE;
static int lastButton    = NONE;

void play_singlep_rps()
{
    Moves player_move = NONE;

    while (true)
    {
        currentButton = get_current_button();
        if (currentButton != RBLUE_BUTTON_PIN)
        {
            switch (currentButton)
            {
                case LWHITE_BUTTON_PIN: player_move = ROCK; break;
                case LRED_BUTTON_PIN:   player_move = PAPER; break;
                case RRED_BUTTON_PIN:   player_move = SCISSORS; break;
            }
        }
        else if (currentButton == RBLUE_BUTTON_PIN && player_move != NONE)
        {
            break;
        }
        print_player_moves(player_move);
        lastButton = currentButton;
    }

    Moves computer_move = get_cpu_move();
    print_count_down(3);
    print_count_down(2);
    print_count_down(1);
    Winner winner = calculate_winner(computer_move, player_move);
    print_moves(computer_move, player_move);
    print_winner(winner);
    lastButton = currentButton = NONE;
    play_singlep_rps();
}
