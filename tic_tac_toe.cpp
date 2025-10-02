#include "util.hpp"

// I'm not singing for your XO... I'm singing cuz it's oveeeerrrrr
enum Player {
    NO_PLAYER = 0,
    X_PLAYER = 'X',
    X_PLAYER_INT = 1,
    O_PLAYER = 'O',
    O_PLAYER_INT = 2
};

static char board[3][3]   = { { ' ', ' ', ' ' }, { ' ', ' ', ' ' }, { ' ', ' ', ' ' } };
static bool game_over     = false;
static char currentPlayer = X_PLAYER;
static int  currentPos[256] = {0};

// Tic-Tac-Toe board lines
static const int BOARD_SIZE     = 64;
static const int CELL_SIZE      = 21;  // 64/3 ≈ 21 pixels per cell
static const int BOARD_OFFSET_X = 32;  // Center the board (128-64)/2
static const int BOARD_OFFSET_Y = 0;

static void draw_board()
{
    // Vertical lines
    display.drawLine(BOARD_OFFSET_X + CELL_SIZE, BOARD_OFFSET_Y, BOARD_OFFSET_X + CELL_SIZE,
                     BOARD_OFFSET_Y + BOARD_SIZE, WHITE);
    display.drawLine(BOARD_OFFSET_X + 2 * CELL_SIZE, BOARD_OFFSET_Y, BOARD_OFFSET_X + 2 * CELL_SIZE,
                     BOARD_OFFSET_Y + BOARD_SIZE, WHITE);

    // Horizontal lines
    display.drawLine(BOARD_OFFSET_X, BOARD_OFFSET_Y + CELL_SIZE, BOARD_OFFSET_X + BOARD_SIZE,
                     BOARD_OFFSET_Y + CELL_SIZE, WHITE);
    display.drawLine(BOARD_OFFSET_X, BOARD_OFFSET_Y + 2 * CELL_SIZE, BOARD_OFFSET_X + BOARD_SIZE,
                     BOARD_OFFSET_Y + 2 * CELL_SIZE, WHITE);
}

static bool is_board_full()
{
    for (uint8_t row = 0; row < 3; ++row)
        for (uint8_t col = 0; col < 3; ++col)
            if (board[row][col] == ' ')
                return false;
    return true;
}

void draw_piece(int row, int col, char piece)
{
    int x = BOARD_OFFSET_X + col * CELL_SIZE + (CELL_SIZE - 16) / 2;
    int y = BOARD_OFFSET_Y + row * CELL_SIZE + (CELL_SIZE - 16) / 2;

    if (piece == 'X')
    {
        display.drawLine(x, y, x + 15, y + 15, WHITE);
        display.drawLine(x + 15, y, x, y + 15, WHITE);
    }
    else if (piece == 'O')
    {
        display.drawCircle(x + 8, y + 8, 7, WHITE);
    }
}

void draw_game_screen()
{
    display.clearDisplay();
    draw_board();

    for (uint8_t row = 0; row < 3; ++row)
        for (uint8_t col = 0; col < 3; ++col)
            if (board[row][col] != ' ')
                draw_piece(row, col, board[row][col]);

    display.setCursor(5, 10);
    display.print("Player: ");
    display.print(currentPlayer);

    display.display();
}

Player check_winner()
{
    // check rows
    for (uint8_t row = 0; row < 3; ++row)
        if (board[row][0] != ' ' && board[row][0] == board[row][1] == board[row][2])
            return (Player)board[row][0];

    // check columns
    for (uint8_t col = 0; col < 3; ++col)
        if (board[0][col] != ' ' && board[0][col] == board[1][col] == board[2][col])
            return (Player)board[0][col];

    // check diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] == board[2][2])
        return (Player)board[0][0];
    if (board[0][2] != ' ' && board[0][2] == board[1][1] == board[2][0])
        return (Player)board[0][2];
    
    return NO_PLAYER;
}

void reset_game()
{
    for (uint8_t row = 0; row < 3; ++row)
        for (uint8_t col = 0; col < 3; ++col)
            board[row][col] == ' ';

    game_over = false;
    currentPlayer = X_PLAYER;
}

static int currentButton = 0;

void play_multip_ttt()
{
    while (true)
    {
        currentButton = get_current_button();
        switch (currentButton)
        {
            case LRED_BUTTON_PIN:
            if (currentPos[currentPlayer] >= 3);
        }
    }
}
