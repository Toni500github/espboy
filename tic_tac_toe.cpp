#include "util.hpp"

// I'm not singing for your XO... I'm singing cuz it's oveeeerrrrr
enum Player
{
    NO_PLAYER = 0,
    X_PLAYER  = 'X',
    O_PLAYER  = 'O',
};

static char board[3][3]   = { { ' ', ' ', ' ' }, { ' ', ' ', ' ' }, { ' ', ' ', ' ' } };
static bool choose_pos    = false;
static char currentPlayer = X_PLAYER;
static int  currentPosX, oldPosX, cursorX = 0;
static int  currentPosY, oldPosY, cursorY = 0;
static int  moves = 0;

// Tic-Tac-Toe board lines
static const int BOARD_SIZE     = 64;
static const int CELL_SIZE      = 21;  // 64/3 ≈ 21 pixels per cell
static const int BOARD_OFFSET_X = 32;  // Center the board (128-64)/2
static const int BOARD_OFFSET_Y = 0;

static bool is_board_full()
{
    for (uint8_t row = 0; row < 3; ++row)
        for (uint8_t col = 0; col < 3; ++col)
            if (board[row][col] == ' ' || board[row][col] == '*')
                return false;
    return true;
}

void draw_piece(int row, int col, char piece)
{
    int x = BOARD_OFFSET_X + col * CELL_SIZE + (CELL_SIZE - 16) / 2;
    int y = BOARD_OFFSET_Y + row * CELL_SIZE + (CELL_SIZE - 16) / 2;

    // draw cursor marker
    int cx = BOARD_OFFSET_X + cursorX * CELL_SIZE + (CELL_SIZE - 6) / 2;
    int cy = BOARD_OFFSET_Y + cursorY * CELL_SIZE + (CELL_SIZE - 6) / 2;
    display.setCursor(cx, cy);
    display.print('*');

    switch (piece)
    {
        case 'X':
            display.drawLine(x, y, x + 16, y + 16, WHITE);
            display.drawLine(x + 16, y, x, y + 16, WHITE);
            break;
        case 'O': display.drawCircle(x + 8, y + 8, 7, WHITE); break;
    }
}

void draw_game_screen()
{
    display.clearDisplay();

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

    for (uint8_t row = 0; row < 3; ++row)
        for (uint8_t col = 0; col < 3; ++col)
            if (board[row][col] != ' ')
                draw_piece(row, col, board[row][col]);

    display.setCursor(5, 10);
    display.setTextSize(2);
    display.print(currentPlayer);
    display.setTextSize(1);

    display.display();
}

void animate_line(int x0, int y0, int x1, int y1)
{
    const int steps = 16;   // smoothness
    for (int i = 1; i <= steps; ++i)
    {
        int xi = x0 + (x1 - x0) * i / steps;
        int yi = y0 + (y1 - y0) * i / steps;
        draw_game_screen();  // redraw board and pieces
        display.drawLine(x0, y0, xi, yi, WHITE);
        display.display();
        delay(150);
    }
}

Player check_winner()
{
    // check rows
    for (uint8_t row = 0; row < 3; ++row)
        if (board[row][0] != ' ' && board[row][0] == board[row][1] && board[row][1] == board[row][2])
        {
            animate_line(BOARD_OFFSET_X, 
                         BOARD_OFFSET_Y + row * CELL_SIZE + CELL_SIZE / 2,
                         BOARD_OFFSET_X + BOARD_SIZE, 
                         BOARD_OFFSET_Y + row * CELL_SIZE + CELL_SIZE / 2);
            return (Player)board[row][0];
        }

    // check columns
    for (uint8_t col = 0; col < 3; ++col)
        if (board[0][col] != ' ' && board[0][col] == board[1][col] && board[1][col] == board[2][col])
        {
            animate_line(BOARD_OFFSET_X + col * CELL_SIZE + CELL_SIZE / 2,
                         BOARD_OFFSET_Y,
                         BOARD_OFFSET_X + col * CELL_SIZE + CELL_SIZE / 2,
                         BOARD_OFFSET_Y + BOARD_SIZE);
            return (Player)board[0][col];
        }

    // check diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        animate_line(BOARD_OFFSET_X, BOARD_OFFSET_Y,
                     BOARD_OFFSET_X + BOARD_SIZE, BOARD_OFFSET_Y + BOARD_SIZE);
        return (Player)board[0][0];
    }

    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        animate_line(BOARD_OFFSET_X + BOARD_SIZE, BOARD_OFFSET_Y,
                     BOARD_OFFSET_X, BOARD_OFFSET_Y + BOARD_SIZE);
        return (Player)board[0][2];
    }

    return NO_PLAYER;
}

void draw_winner(Player winner)
{
    display.clearDisplay();
    display.setTextSize(2);
    centerText("Player", 5);
    centerText(winner == X_PLAYER ? "X" : "O", 25);
    centerText("Wins!", 45);

    display.display();
}

void reset_game()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    for (uint8_t row = 0; row < 3; ++row)
        for (uint8_t col = 0; col < 3; ++col)
            board[row][col] = ' ';

    choose_pos = moves = currentPosY = currentPosX = oldPosY = oldPosX = 0;
    currentPlayer                                                      = X_PLAYER;
}

void play_multip_ttt()
{
    reset_game();
    delay(200);
    int currentButton = 0;

    while (true)
    {
        if (is_board_full())
        {
            delay(100);
            display.clearDisplay();
            display.setTextSize(2);
            centerText("Board Full", 32);
            display.display();
            delay(2000);
            reset_game();
            continue;
        }

        choose_pos    = false;
        oldPosX       = currentPosX;
        oldPosY       = currentPosY;
        currentPlayer = (moves % 2 == 0) ? X_PLAYER : O_PLAYER;
        currentButton = get_current_button();
        switch (currentButton)
        {
            case RRED_BUTTON_PIN:
                if (currentPosX >= 2 && currentPosY < 2)
                {
                    currentPosX = 0;
                    ++currentPosY;
                }
                else if (currentPosX < 2)
                {
                    ++currentPosX;
                }
                delay(200);
                break;
            case LRED_BUTTON_PIN:
                if (currentPosX == 0 && currentPosY > 0)
                {
                    currentPosX = 2;
                    --currentPosY;
                }
                else if (currentPosX > 0)
                {
                    --currentPosX;
                }
                delay(200);
                break;
            case RBLUE_BUTTON_PIN:
                choose_pos = true;
                delay(200);
                break;
        }
        cursorX = currentPosX;
        cursorY = currentPosY;

        if (board[currentPosY][currentPosX] == ' ')
            board[currentPosY][currentPosX] = '*';

        draw_game_screen();

        if (choose_pos && board[currentPosY][currentPosX] == '*')
        {
            board[currentPosY][currentPosX] = currentPlayer;
            currentPosX = currentPosY = 0;
            ++moves;
        }
        else
        {
            if (board[oldPosX][oldPosY] == '*')
                board[oldPosX][oldPosY] = ' ';
            continue;
        }

        Player winner = check_winner();
        if (winner != NO_PLAYER)
        {
            draw_winner(winner);
            delay(3000);
            reset_game();
        }
    }
}
