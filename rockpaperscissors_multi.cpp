#include "util.hpp"

enum Winner
{
    PLAYER1 = 0,
    DRAW,
    PLAYER2,
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

static void print_winner(Winner winner)
{
    display.clearDisplay();
    display.setTextSize(1);
    switch (winner)
    {
        case PLAYER1: centerText("Player1 Wins!", 28); break;
        case DRAW:    centerText("Draw!", 28); break;
        case PLAYER2: centerText("Player2 Win!", 28); break;
    }
    display.display();
    delay(1500);
}

static Winner calculate_winner(Moves player1_move, Moves player2_move)
{
    if (player1_move == player2_move)
        return DRAW;

    else if ((player1_move == ROCK && player2_move == SCISSORS) ||
             (player1_move == SCISSORS && player2_move == PAPER) ||
             (player1_move == PAPER && player2_move == ROCK))
        return PLAYER1;

    else
        return PLAYER2;
}

static void print_player_moves(bool is_player1, Moves player_move)
{
    display.clearDisplay();
    display.setCursor(0, 28);
    display.setTextSize(1);
    if (is_player1)
        display.print("Player1 move: ");
    else
        display.print("Player2 move: ");
    display.setCursor(90, 25);
    display.setTextSize(2);
    display.print(get_move_char(player_move));

    display.display();
}

static void print_moves(Moves player1_move, Moves player2_move)
{
    display.clearDisplay();
    display.setCursor(6, 12);
    display.setTextSize(1);
    display.print("P1");
    display.setCursor(110, 12);
    display.print("P2");

    display.setCursor(6, 28);
    display.setTextSize(2);
    display.print(get_move_char(player1_move));

    display.setTextSize(1);
    centerText("VS", 28);

    display.setCursor(110, 28);
    display.setTextSize(2);
    display.print(get_move_char(player2_move));

    display.display();
    delay(1500);
}

static int currentButton = NONE;
static int lastButton    = NONE;

void play_multip_rps()
{
    while (true)
    {
        Moves player1_move = NONE, player2_move = NONE;

        while (true)
        {
            currentButton = get_current_button();
            if (currentButton != RBLUE_BUTTON_PIN)
            {
                switch (currentButton)
                {
                    case LWHITE_BUTTON_PIN: player1_move = ROCK; break;
                    case LRED_BUTTON_PIN:   player1_move = PAPER; break;
                    case RRED_BUTTON_PIN:   player1_move = SCISSORS; break;
                }
            }
            else if (currentButton == RBLUE_BUTTON_PIN && player1_move != NONE)
            {
                break;
            }
            print_player_moves(true, player1_move);
            lastButton = currentButton;
        }

        lastButton = currentButton = NONE;

        while (true)
        {
            currentButton = get_current_button();
            if (currentButton != RBLUE_BUTTON_PIN)
            {
                switch (currentButton)
                {
                    case LWHITE_BUTTON_PIN: player2_move = ROCK; break;
                    case LRED_BUTTON_PIN:   player2_move = PAPER; break;
                    case RRED_BUTTON_PIN:   player2_move = SCISSORS; break;
                }
            }
            else if (currentButton == RBLUE_BUTTON_PIN && player2_move != NONE)
            {
                break;
            }
            print_player_moves(false, player2_move);
            lastButton = currentButton;
        }

        print_count_down(3);
        print_count_down(2);
        print_count_down(1);
        Winner winner = calculate_winner(player1_move, player2_move);
        print_moves(player1_move, player2_move);
        print_winner(winner);
        lastButton = currentButton = NONE;
    }
}
