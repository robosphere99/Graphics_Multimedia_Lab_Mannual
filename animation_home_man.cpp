#include <graphics.h>
#include <conio.h>
#include <math.h>

int main() {
    int gd = DETECT, gm;
    initwindow(1280,780,"Robosphere");
    cleardevice();

    int x[7] = {0, 50, 50, 75, 50, 50, 0};
    int y[7] = {60, 60, 50, 65, 80, 70, 70};

    char ch;
    int cx = 1000, cy = 600;
    int r1 = 100, r2 = 80, r3 = 50;

    while (1) {
        cleardevice();

   
        setcolor(RED); circle(cx, cy, r1);
        setcolor(GREEN); circle(cx, cy, r2);
        setcolor(YELLOW); circle(cx, cy, r3);

   
        setcolor(WHITE);
        line(x[0], y[0], x[1], y[1]);
        line(x[2], y[2], x[3], y[3]);
        line(x[3], y[3], x[4], y[4]);
        line(x[2], y[2], x[4], y[4]);
        line(x[5], y[5], x[6], y[6]);
        line(x[0], y[0], x[6], y[6]);

    
        int tipX = x[3], tipY = y[3];
        int dx = tipX - cx;
        int dy = tipY - cy;
        int dist2 = dx*dx + dy*dy;

        if (dist2 <= r1*r1 && dist2 > r2*r2) {
            setfillstyle(SOLID_FILL, RED);
            fillellipse(cx, cy, r1, r1);
            setfillstyle(SOLID_FILL, BLACK);
            fillellipse(cx, cy, r2, r2); 
            setcolor(GREEN); circle(cx, cy, r2);
            setcolor(YELLOW); circle(cx, cy, r3);
        }
        else if (dist2 <= r2*r2 && dist2 > r3*r3) {
            setfillstyle(SOLID_FILL, GREEN);
            fillellipse(cx, cy, r2, r2);
            setfillstyle(SOLID_FILL, BLACK);
            fillellipse(cx, cy, r3, r3);
            setcolor(YELLOW); circle(cx, cy, r3);
        }
        else if (dist2 <= r3*r3) {
            setfillstyle(SOLID_FILL, YELLOW);
            fillellipse(cx, cy, r3, r3);
        }

        ch = getch();
        if (ch == 27) break;

        if (ch == 0) {
            ch = getch();
            if (ch == 72) { for (int i=0; i<7; i++) y[i] -= 10; }
            else if (ch == 80) { for (int i=0; i<7; i++) y[i] += 10; }
            else if (ch == 75) { for (int i=0; i<7; i++) x[i] -= 10; }
            else if (ch == 77) { for (int i=0; i<7; i++) x[i] += 10; }
        }
    }
    closegraph();
}
