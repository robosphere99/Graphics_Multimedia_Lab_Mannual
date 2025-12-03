#include <graphics.h>
void bresenham(int x0,int y0,int x1,int y1,int color){
    int dx=abs(x1-x0), dy=abs(y1-y0);
    int sx=(x0<x1)?1:-1, sy=(y0<y1)?1:-1;
    int err=dx-dy;
    while(1){
        putpixel(x0,y0,color);
        if(x0==x1 && y0==y1) break;
        int e2=2*err;
        if(e2>-dy){ err -= dy; x0 += sx; }
        if(e2< dx){ err += dx; y0 += sy; }
    }
}
int main(){
    initwindow(640,480,"Bresenham Demo");
    bresenham(50,50,300,200,WHITE);
    getch();
    closegraph();
    return 0;
}
