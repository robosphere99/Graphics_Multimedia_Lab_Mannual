#include<graphics.h>
#include<conio.h>
int main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,(char*)"");
    rectangle(10,10,110,110);
    rectangle(20,20,100,100);
    rectangle(30,30,90,90);
    circle(60,60,25);
    getch();
    closegraph();
}   