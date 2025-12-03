#include <graphics.h>
#include <conio.h>
#include<iostream>
#include<math.h>
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
    setbkcolor(BLACK);
    cleardevice();
    setcolor(GREEN);
    rectangle(100,100,200,200);
    setfillstyle(SOLID_FILL, GREEN);
    floodfill(150, 150, GREEN);
    setcolor(1);
    line(200,100,200,200);
    line(200,100,300,100);
    line(200,200,300,100);
    setfillstyle(SOLID_FILL, 5);
    floodfill(230, 130, 1);
    setcolor(2);
    line(300,100,400,200);
    line(400,200,200,200);
    line(200,200,300,100);
    setfillstyle(SOLID_FILL, LIGHTMAGENTA);
    floodfill(300, 160, 2);
    
    setcolor(3);
    line(100,200,300,400);
    line(100,200,300,200);
    line(300,200,300,400);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(200, 280, 3);
    setcolor(4);
    line(300,200,300,400);
    line(300,200,500,400);
    line(300,400,500,400);
    setfillstyle(SOLID_FILL, 6);
    floodfill(380, 350, 4);
    setcolor(5);
    line(300,200,400,200);
    line(300,200,400,300);
    line(400,200,400,300);
    setfillstyle(SOLID_FILL, RED);
    floodfill(360, 230, 5);
    setcolor(6);
    line(400,200,500,300);
    line(500,300,500,400);
    line(500,400,400,300);
    line(400,200,400,300);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(450, 300, 6);
    
    getch();
    closegraph();
    return 0;
}