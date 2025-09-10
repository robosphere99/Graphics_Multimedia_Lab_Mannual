#include <graphics.h>
#include <conio.h>
#include <math.h>

int main() {
    int gd = DETECT, gm;
    // initgraph(&gd, &gm, "");
    initwindow(1280,780,"Robosphere");
    cleardevice();

    int x[7] = {0, 50, 50, 75, 50, 50, 0};
    int y[7] = {60, 60, 50, 65, 80, 70, 70};

    char ch;
    float angle = 0;
    float scale = 1.0;

    while (1) {
        cleardevice();

        line(x[0], y[0], x[1], y[1]);
        line(x[2], y[2], x[3], y[3]);
        line(x[3], y[3], x[4], y[4]);
        line(x[2], y[2], x[4], y[4]);
        line(x[5], y[5], x[6], y[6]);
        line(x[0], y[0], x[6], y[6]);
        setcolor(RED);
        circle(1000,600,100);
        setcolor(GREEN);
        circle(1000,600,80);
        setcolor(YELLOW);
        circle(1000,600,50);
        setcolor(WHITE);
        ch = getch();
        if (ch == 27) break;  

        if (ch == 0) {
            ch = getch();
            if (ch == 72) { 
                for (int i=0; i<7; i++) y[i] -= 10;
            }
            else if (ch == 80) { 
                for (int i=0; i<7; i++) y[i] += 10;
            }
            else if (ch == 75) { 
                for (int i=0; i<7; i++) x[i] -= 10;
            }
            else if (ch == 77) { 
                for (int i=0; i<7; i++) x[i] += 10;
            }
        }
    }
    closegraph();
}