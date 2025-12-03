#include<graphics.h>
#include<conio.h>

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    setcolor(RED);
    rectangle(50, 150, 150, 250);
    

    getch();
    closegraph();
    return 0;
}
