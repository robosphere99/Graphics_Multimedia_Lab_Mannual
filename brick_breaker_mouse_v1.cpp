#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include <cmath>      
#pragma comment(lib, "winmm.lib")
#include <stdlib.h>

#define MAX_BRICKS_ROW 8
#define MAX_BRICKS_COL 5

// Screen
int maxx_scr, maxy_scr;

// Paddle
int paddle_w = 120;
int paddle_h = 12;
int paddle_x, paddle_y;

// Ball
float ball_x, ball_y;
float ball_dx = 3.0f, ball_dy = -3.0f;
int ball_radius = 6;
int ball_served = 0;

// Bricks
int bricks[MAX_BRICKS_COL][MAX_BRICKS_ROW];
int brick_w, brick_h, brick_gap = 6;
int bricks_offset_x, bricks_offset_y;

// Score / lives
int score = 0;
int total_bricks = 0;
int lives = 3;

// ---------- SOUND FUNCTIONS ---------- //
void playBackground() {
    PlaySound("bg.wav", NULL, SND_LOOP | SND_ASYNC);
}
void playBrickSound() {
    PlaySound("brick.wav", NULL, SND_ASYNC);
}
void playLifeLost() {
    PlaySound("life.wav", NULL, SND_ASYNC);
}
void playServe() {
    PlaySound("serve.wav", NULL, SND_ASYNC);
}
// stop all
void stopSound() {
    PlaySound(NULL, NULL, 0);
}

// ---------- DRAWING FUNCTIONS ---------- //
void drawPaddle() {
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(paddle_x, paddle_y, paddle_x + paddle_w, paddle_y + paddle_h);
}

void drawBall() {
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse((int)ball_x, (int)ball_y, ball_radius, ball_radius);
}

void drawBricks() {
    int r, c;
    for (r = 0; r < MAX_BRICKS_COL; r++) {
        for (c = 0; c < MAX_BRICKS_ROW; c++) {
            if (bricks[r][c]) {
                int x1 = bricks_offset_x + c * (brick_w + brick_gap);
                int y1 = bricks_offset_y + r * (brick_h + brick_gap);
                int x2 = x1 + brick_w;
                int y2 = y1 + brick_h;
                setfillstyle(SOLID_FILL, (r % 6) + 2);
                bar(x1, y1, x2, y2);
                rectangle(x1, y1, x2, y2);
            }
        }
    }
}

void drawHUD() {
    setcolor(WHITE);
    char buf[64];
    sprintf(buf, "Score: %d   Lives: %d   Bricks: %d", score, lives, total_bricks);
    outtextxy(10, maxy_scr - 20, buf);
}

// ---------- INIT ---------- //
void initGame() {
    maxx_scr = getmaxx();
    maxy_scr = getmaxy();

    paddle_y = maxy_scr - 60;
    paddle_x = (maxx_scr - paddle_w)/2;

    ball_x = paddle_x + paddle_w/2;
    ball_y = paddle_y - ball_radius - 2;
    ball_dx = 3.0f; ball_dy = -3.0f;
    ball_served = 0;

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
    playBackground(); // start background music
}

// ---------- UPDATE BALL ---------- //
void updateBall() {
    float nx = ball_x + ball_dx;
    float ny = ball_y + ball_dy;

    if (nx - ball_radius <= 0) { ball_dx = fabs(ball_dx); nx = ball_radius + 1; }
    else if (nx + ball_radius >= maxx_scr) { ball_dx = -fabs(ball_dx); nx = maxx_scr - ball_radius - 1; }

    if (ny - ball_radius <= 0) { ball_dy = fabs(ball_dy); ny = ball_radius + 1; }

    if (ny + ball_radius >= maxy_scr) {
        lives--;
        playLifeLost();
        if (lives > 0) {
            ball_served = 0;
            ball_x = paddle_x + paddle_w/2;
            ball_y = paddle_y - ball_radius - 2;
            ball_dx = 3.0f; ball_dy = -3.0f;
        }
        return;
    }

    // paddle collision
    if (ny + ball_radius >= paddle_y && nx >= paddle_x && nx <= paddle_x + paddle_w && ball_dy > 0) {
        float hitPos = (nx - paddle_x) - paddle_w/2;
        float normalize = hitPos / (paddle_w/2);
        ball_dx = ball_dx + normalize * 2.0f;
        if (fabs(ball_dx) < 1.0f) ball_dx = (ball_dx >= 0 ? 1.5f : -1.5f);
        ball_dy = -fabs(ball_dy);
        ny = paddle_y - ball_radius - 1;
    }

    // brick collisions
    for (int r=0; r<MAX_BRICKS_COL; r++) {
        for (int c=0; c<MAX_BRICKS_ROW; c++) {
            if (!bricks[r][c]) continue;
            int x1 = bricks_offset_x + c * (brick_w + brick_gap);
            int y1 = bricks_offset_y + r * (brick_h + brick_gap);
            int x2 = x1 + brick_w;
            int y2 = y1 + brick_h;

            if (nx + ball_radius >= x1 && nx - ball_radius <= x2 &&
                ny + ball_radius >= y1 && ny - ball_radius <= y2) {
                bricks[r][c] = 0; total_bricks--; score += 10;
                playBrickSound();
                ball_dy = -ball_dy; // simple bounce
                return;
            }
        }
    }

    ball_x = nx; ball_y = ny;
}

// ---------- MAIN ---------- //
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
    initGame();

    while (1) {
        cleardevice();

        // Mouse position
        int mx = mousex();
        int my = mousey();

        paddle_x = mx - paddle_w/2;
        if (paddle_x < 0) paddle_x = 0;
        if (paddle_x + paddle_w > maxx_scr) paddle_x = maxx_scr - paddle_w;

        if (!ball_served) {
            ball_x = paddle_x + paddle_w/2;
            ball_y = paddle_y - ball_radius - 2;
        }

        // Left click to serve
        if (ismouseclick(WM_LBUTTONDOWN)) {
            clearmouseclick(WM_LBUTTONDOWN);
            if (!ball_served) {
                ball_served = 1;
                playServe();
            }
        }

        if (ball_served) updateBall();

        drawBricks();
        drawPaddle();
        drawBall();
        drawHUD();

        if (total_bricks == 0) {
            outtextxy(maxx_scr/2 - 40, maxy_scr/2, (char*)"YOU WIN!");
            stopSound();
            if (kbhit() && getch()==27) break;
        }

        if (lives <= 0) {
            outtextxy(maxx_scr/2 - 40, maxy_scr/2, (char*)"GAME OVER");
            stopSound();
            if (kbhit() && getch()==27) break;
        }

        delay(10);
    }

    closegraph();
    stopSound();
    return 0;
}
