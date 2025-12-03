#include <graphics.h>
#include <conio.h>

void drawArchitecture() {
    int pts1[] = {100,100, 200,100, 200,200, 100,200};
    int pts2[] = {200,100, 300,100, 200,200};
    int pts3[] = {300,100, 400,200, 200,200};
    int pts4[] = {100,200, 300,200, 300,400};
    int pts5[] = {300,200, 400,200, 400,300};
    int pts6[] = {300,200, 500,400, 300,400};
    int pts7[] = {400,200, 500,300, 500,400, 400,300};

    setfillstyle(SOLID_FILL, GREEN);
    setcolor(BLACK);
    fillpoly(4, pts1);

    setfillstyle(SOLID_FILL, 5);
    setcolor(BLACK);
    fillpoly(3, pts2);

    setfillstyle(SOLID_FILL, LIGHTMAGENTA);
    setcolor(BLACK);
    fillpoly(3, pts3);
    
    setfillstyle(SOLID_FILL, BLUE);
    setcolor(BLACK);
    fillpoly(3, pts4);
    setfillstyle(SOLID_FILL, RED);
    setcolor(BLACK);
    fillpoly(3, pts5);
    setfillstyle(SOLID_FILL, COLOR(255, 165, 0));
    setcolor(BLACK);
    fillpoly(3, pts6);
    setfillstyle(SOLID_FILL, YELLOW);
    setcolor(BLACK);
    fillpoly(4, pts7);
}
int main(){
    initwindow(640,480,"Drawing Architecture");
    drawArchitecture();
    getch();
    closegraph();
    return 0;
}
