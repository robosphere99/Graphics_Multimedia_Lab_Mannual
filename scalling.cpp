#include<graphics.h>
#include<conio.h>

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    setcolor(RED);
    rectangle(50, 150, 150, 250);
    line(50, 150, 100, 100);
    line(100, 100, 150, 150);
    line(150, 150, 50, 150);
    outtextxy(70, 200, (char *)"Original");

    int sx = 2, ty = 1;

    setcolor(GREEN);
    rectangle(50 * sx, 150 * ty, 150 * sx, 250 * ty);
    line(50 * sx, 150 * ty, 100 * sx, 100 * ty);
    line(100 * sx, 100 * ty, 150 * sx, 150 * ty);
    line(150 * sx, 150 * ty, 50 * sx, 150 * ty);
    outtextxy(70 * sx, 200 * ty, (char*)"Scalled");

    getch();
    closegraph();
    return 0;
}
