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

    int tx = 400, ty = 50;

    setcolor(GREEN);
    rectangle(50 + tx, 150 + ty, 150 + tx, 250 + ty);
    line(50 + tx, 150 + ty, 100 + tx, 100 + ty);
    line(100 + tx, 100 + ty, 150 + tx, 150 + ty);
    line(150 + tx, 150 + ty, 50 + tx, 150 + ty);
    outtextxy(70 + tx, 200 + ty, (char*)"Translated");

    getch();
    closegraph();
    return 0;
}
