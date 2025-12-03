/* Brick Breaker - graphics.h version
   Compile with Code::Blocks + WinBGIm or Turbo C BGI.
   If using WinBGIm, link libbgi and include directories appropriately.
*/

#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>    // for delay in some compilers; otherwise use delay from graphics.h
#include <math.h>

#define MAX_BRICKS_ROW 8
#define MAX_BRICKS_COL 5

// Screen / game area
int maxx_scr, maxy_scr;

// Paddle
int paddle_w = 120;
int paddle_h = 12;
int paddle_x, paddle_y;
int paddle_speed = 20;

// Ball
float ball_x, ball_y;
float ball_dx = 3.0f, ball_dy = -3.0f;
int ball_radius = 6;
int ball_served = 0; // 0 = on paddle, 1 = moving

// Bricks
int bricks[MAX_BRICKS_COL][MAX_BRICKS_ROW]; // 1 = alive, 0 = destroyed
int brick_w, brick_h, brick_gap = 6;
int bricks_offset_x, bricks_offset_y;

// Score / lives
int score = 0;
int total_bricks = 0;
int lives = 3;

// Utility: draw paddle
void drawPaddle() {
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(paddle_x, paddle_y, paddle_x + paddle_w, paddle_y + paddle_h);
}

// Utility: draw ball
void drawBall() {
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse((int)ball_x, (int)ball_y, ball_radius, ball_radius);
}

// Draw bricks grid
void drawBricks() {
    int r, c;
    for (r = 0; r < MAX_BRICKS_COL; r++) {
        for (c = 0; c < MAX_BRICKS_ROW; c++) {
            if (bricks[r][c]) {
                int x1 = bricks_offset_x + c * (brick_w + brick_gap);
                int y1 = bricks_offset_y + r * (brick_h + brick_gap);
                int x2 = x1 + brick_w;
                int y2 = y1 + brick_h;
                // color by row
                int col = (r % 6) + 1;
                setfillstyle(SOLID_FILL, col + 1);
                bar(x1, y1, x2, y2);
                // brick border
                rectangle(x1, y1, x2, y2);
            }
        }
    }
}

// Initialize game state and brick layout
void initGame() {
    maxx_scr = getmaxx();
    maxy_scr = getmaxy();

    // paddle position bottom center
    paddle_y = maxy_scr - 60;
    paddle_x = (maxx_scr - paddle_w)/2;

    // ball on paddle center
    ball_x = paddle_x + paddle_w/2;
    ball_y = paddle_y - ball_radius - 2;
    ball_dx = 3.0f; ball_dy = -3.0f;
    ball_served = 0;

    // bricks sizing: occupy upper area
    brick_w = (maxx_scr - 120 - (MAX_BRICKS_ROW - 1) * brick_gap) / MAX_BRICKS_ROW;
    brick_h = 22;
    bricks_offset_x = 60;
    bricks_offset_y = 60;

    total_bricks = 0;
    for (int r=0; r<MAX_BRICKS_COL; r++) {
        for (int c=0; c<MAX_BRICKS_ROW; c++) {
            bricks[r][c] = 1;
            total_bricks++;
        }
    }

    score = 0;
    lives = 3;
}

// Check ball collisions with walls, paddle, bricks
void updateBall() {
    // tentative next pos
    float nx = ball_x + ball_dx;
    float ny = ball_y + ball_dy;

    // left/right walls
    if (nx - ball_radius <= 0) {
        ball_dx = fabs(ball_dx);
        nx = ball_radius + 1;
    } else if (nx + ball_radius >= maxx_scr) {
        ball_dx = -fabs(ball_dx);
        nx = maxx_scr - ball_radius - 1;
    }

    // top wall
    if (ny - ball_radius <= 0) {
        ball_dy = fabs(ball_dy);
        ny = ball_radius + 1;
    }

    // bottom (missed paddle)
    if (ny + ball_radius >= maxy_scr) {
        lives--;
        // reset ball on paddle if lives left
        if (lives > 0) {
            ball_served = 0;
            ball_x = paddle_x + paddle_w/2;
            ball_y = paddle_y - ball_radius - 2;
            ball_dx = 3.0f; ball_dy = -3.0f;
        } else {
            // game over handled outside
            ball_x = nx; ball_y = ny;
        }
        return;
    }

    // paddle collision (simple AABB with top)
    if (ny + ball_radius >= paddle_y && ny - ball_radius <= paddle_y + paddle_h &&
        nx >= paddle_x && nx <= paddle_x + paddle_w && ball_dy > 0) {
        // reflect y and adjust dx depending on hit position
        float hitPos = (nx - paddle_x) - paddle_w/2; // -half..half
        float normalize = hitPos / (paddle_w/2);
        ball_dx = ball_dx + normalize * 2.0f; // change angle
        if (fabs(ball_dx) < 1.0f) {
            if (ball_dx >= 0) ball_dx = 1.5f; else ball_dx = -1.5f;
        }
        ball_dy = -fabs(ball_dy);
        ny = paddle_y - ball_radius - 1;
    }

    // brick collisions (check bounding boxes)
    for (int r = 0; r < MAX_BRICKS_COL; r++) {
        for (int c = 0; c < MAX_BRICKS_ROW; c++) {
            if (!bricks[r][c]) continue;
            int x1 = bricks_offset_x + c * (brick_w + brick_gap);
            int y1 = bricks_offset_y + r * (brick_h + brick_gap);
            int x2 = x1 + brick_w;
            int y2 = y1 + brick_h;
            // approximate collision with ball circle -> check overlap with rect
            if (nx + ball_radius >= x1 && nx - ball_radius <= x2 &&
                ny + ball_radius >= y1 && ny - ball_radius <= y2) {
                // destroy brick
                bricks[r][c] = 0;
                total_bricks--;
                score += 10;
                // reflect ball: decide whether to flip dx or dy based on approach
                // check which side was hit: previous position
                float prevX = ball_x;
                float prevY = ball_y;
                if (prevY + ball_radius <= y1) {
                    // hit from top
                    ball_dy = -fabs(ball_dy);
                } else if (prevY - ball_radius >= y2) {
                    // hit from bottom
                    ball_dy = fabs(ball_dy);
                } else if (prevX + ball_radius <= x1) {
                    // hit from left
                    ball_dx = -fabs(ball_dx);
                } else if (prevX - ball_radius >= x2) {
                    // hit from right
                    ball_dx = fabs(ball_dx);
                } else {
                    // fallback: invert vertical
                    ball_dy = -ball_dy;
                }
                // small speed up as game progresses
                if (ball_dx > 0) ball_dx += 0.1f; else ball_dx -= 0.1f;
                if (ball_dy > 0) ball_dy += 0.05f; else ball_dy -= 0.05f;
                return; // only one brick destroy per update to avoid multiple hits same frame
            }
        }
    }

    // commit
    ball_x = nx;
    ball_y = ny;
}

// Draw HUD
void drawHUD() {
    setcolor(WHITE);
    char buf[64];
    sprintf(buf, "Score: %d   Lives: %d   Bricks: %d", score, lives, total_bricks);
    outtextxy(10, maxy_scr - 20, buf);
}

// main
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, ""); // in WinBGIm, third param can be ""
    initGame();

    // main loop
    while (1) {
        // clear screen
        cleardevice();

        // input handling (non-blocking)
        if (kbhit()) {
            int ch = getch();
            // arrow keys produce 0 or 0xE0 then code (in some compilers)
            if (ch == 0 || ch == 0xE0) {
                int ch2 = getch();
                if (ch2 == 75) { // left arrow
                    paddle_x -= paddle_speed;
                    if (paddle_x < 0) paddle_x = 0;
                    if (!ball_served) {
                        ball_x = paddle_x + paddle_w/2;
                    }
                } else if (ch2 == 77) { // right arrow
                    paddle_x += paddle_speed;
                    if (paddle_x + paddle_w > maxx_scr) paddle_x = maxx_scr - paddle_w;
                    if (!ball_served) {
                        ball_x = paddle_x + paddle_w/2;
                    }
                }
            } else {
                if (ch == 32) { // space serve / pause toggle (simple)
                    if (!ball_served) ball_served = 1;
                    else ball_served = 1; // we keep serving once pressed
                } else if (ch == 27) { // ESC quit
                    break;
                }
            }
        }

        // update ball if served
        if (ball_served) updateBall();
        else {
            // keep ball on paddle
            ball_x = paddle_x + paddle_w/2;
            ball_y = paddle_y - ball_radius - 2;
        }

        // draw bricks, paddle, ball, HUD
        drawBricks();
        drawPaddle();
        drawBall();
        drawHUD();

        // win condition
        if (total_bricks == 0) {
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(maxx_scr/2 - 80, maxy_scr/2, "YOU WIN!");
            outtextxy(maxx_scr/2 - 150, maxy_scr/2 + 30, "Press ESC to quit");
            // freeze until ESC
            if (kbhit()) {
                int c = getch();
                if (c == 27) break;
            }
        }

        // lose condition
        if (lives <= 0) {
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(maxx_scr/2 - 80, maxy_scr/2, "GAME OVER");
            outtextxy(maxx_scr/2 - 160, maxy_scr/2 + 30, "Press ESC to quit");
            if (kbhit()) {
                int c = getch();
                if (c == 27) break;
            }
        }

        delay(12); // frame rate control (ms)
    }

    closegraph();
    return 0;
}
