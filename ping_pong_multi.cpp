#include "util.hpp"

void resetBall();
enum
{
    PADDLE_WIDTH  = 4,
    PADDLE_HEIGHT = 16,
    BALL_SIZE     = 4,
    PADDLE_MARGIN = 5
};

static int paddleLeftY  = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
static int paddleRightY = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
static int ballX        = SCREEN_WIDTH / 2;
static int ballY        = SCREEN_HEIGHT / 2;
static int ballSpeedX   = 4;
static int ballSpeedY   = 4;
static int leftScore    = 0;
static int rightScore   = 0;

void drawGame()
{
    display.clearDisplay();

    for (int y = 0; y < SCREEN_HEIGHT; y += 4)
        display.drawPixel(SCREEN_WIDTH / 2, y, SSD1306_WHITE);

    display.fillRect(PADDLE_MARGIN, paddleLeftY, PADDLE_WIDTH, PADDLE_HEIGHT, SSD1306_WHITE);
    display.fillRect(SCREEN_WIDTH - PADDLE_MARGIN - PADDLE_WIDTH, paddleRightY, PADDLE_WIDTH, PADDLE_HEIGHT,
                     SSD1306_WHITE);

    display.fillRect(ballX, ballY, BALL_SIZE, BALL_SIZE, SSD1306_WHITE);

    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(SCREEN_WIDTH / 4 - 10, 5);
    display.println(leftScore);

    display.setCursor(3 * SCREEN_WIDTH / 4 - 10, 5);
    display.println(rightScore);

    // Game over condition
    if (leftScore >= 5 || rightScore >= 5)
    {
        display.setTextSize(1);
        display.setCursor((SCREEN_WIDTH / 2) - 28, SCREEN_HEIGHT / 2);
        display.println("GAME  OVER");

        display.setCursor((SCREEN_WIDTH / 2) - 49, (SCREEN_HEIGHT / 2) + 10);
        if (leftScore > rightScore)
            display.println("LEFT PLAYER WINS!");
        else
            display.println("RIGHT PLAYER WINS!");

        display.display();
        delay(3000);

        // Reset game
        leftScore  = 0;
        rightScore = 0;
        resetBall();
        return;
    }

    display.display();
}

void resetBall()
{
    ballX      = SCREEN_WIDTH / 2;
    ballY      = SCREEN_HEIGHT / 2;
    ballSpeedX = (ballSpeedX > 0) ? -3 : 3;  // Alternate direction
    ballSpeedY = random(-2, 5);              // Random vertical speed

    drawGame();
    delay(1000);
}

void updateGame()
{
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // Ball collision with top and bottom
    if (ballY <= 0 || ballY >= SCREEN_HEIGHT - BALL_SIZE)
    {
        ballSpeedY = -ballSpeedY;
        // Add small randomness when hitting walls
        if (random(0, 100) < 30)
        {  // 30% chance
            ballSpeedY += random(-1, 2);
            // Constrain speed to prevent too vertical movement
            ballSpeedY = constrain(ballSpeedY, -3, 3);
        }
    }

    // Ball collision with left paddle
    if (ballX <= PADDLE_MARGIN + PADDLE_WIDTH && ballX >= PADDLE_MARGIN && ballY + BALL_SIZE >= paddleLeftY &&
        ballY <= paddleLeftY + PADDLE_HEIGHT)
    {
        ballSpeedX = abs(ballSpeedX);  // Move right

        // Add randomness to Y direction when hitting paddle
        int hitPos = ballY - paddleLeftY;
        ballSpeedY = map(hitPos, 0, PADDLE_HEIGHT, -3, 3);

        // Small random adjustment to prevent repetitive patterns
        if (abs(ballSpeedY) < 1)
            ballSpeedY += random(-2, 3);
        else
            ballSpeedY += random(-1, 2);

        // Constrain speed to prevent too vertical movement
        ballSpeedY = constrain(ballSpeedY, -4, 4);

        // Ensure minimum X speed
        ballSpeedX = max(abs(ballSpeedX), 2);
    }

    // Ball collision with right paddle
    if (ballX + BALL_SIZE >= SCREEN_WIDTH - PADDLE_MARGIN - PADDLE_WIDTH &&
        ballX + BALL_SIZE <= SCREEN_WIDTH - PADDLE_MARGIN && ballY + BALL_SIZE >= paddleRightY &&
        ballY <= paddleRightY + PADDLE_HEIGHT)
    {
        ballSpeedX = -abs(ballSpeedX);  // Move left

        int hitPos = ballY - paddleRightY;
        ballSpeedY = map(hitPos, 0, PADDLE_HEIGHT, -3, 3);

        if (abs(ballSpeedY) < 1)
            ballSpeedY += random(-2, 3);
        else
            ballSpeedY += random(-1, 2);

        ballSpeedY = constrain(ballSpeedY, -4, 4);
        ballSpeedX = -max(abs(ballSpeedX), 2);
    }

    // Score points
    if (ballX < 0)
    {
        rightScore++;
        resetBall();
    }
    else if (ballX > SCREEN_WIDTH)
    {
        leftScore++;
        resetBall();
    }

    // Occasionally add very small random Y movement during normal play
    // This prevents perfectly horizontal ball movement
    // 1% chance each frame
    if (random(0, 500) < 5)
    {
        ballSpeedY += random(-1, 2);
        ballSpeedY = constrain(ballSpeedY, -4, 4);
    }
}

static int currentButton = 0;

void play_multip_ping_pong()
{
    while (true)
    {
        currentButton = get_current_button();
        switch (currentButton)
        {
            case LWHITE_BUTTON_PIN:
                if (paddleLeftY > 0)
                    paddleLeftY -= 3;
                break;
            case LRED_BUTTON_PIN:
                if (paddleLeftY < SCREEN_HEIGHT - PADDLE_HEIGHT)
                    paddleLeftY += 3;
                break;
            case RRED_BUTTON_PIN:
                if (paddleRightY > 0)
                    paddleRightY -= 3;
                break;
            case RBLUE_BUTTON_PIN:
                if (paddleRightY < SCREEN_HEIGHT - PADDLE_HEIGHT)
                    paddleRightY += 3;
                break;
        }
        updateGame();

        // Draw everything
        drawGame();

        // 60fps
        delay(16);
    }
}
