#include <graphics.h>
#include <conio.h>

void bresenham(int x0,int y0,int x1,int y1,int color){
    int dx=abs(x1-x0), dy=abs(y1-y0);
    int sx=(x0<x1)?1:-1, sy=(y0<y1)?1:-1;
    int err=dx-dy;
    while(1){
        putpixel(x0,y0,color);
        if(x0==x1 && y0==y1) break;
        int e2=2*err;
        if(e2>-dy){ err -= dy; x0 += sx; }
        if(e2<dx){ err += dx; y0 += sy; }
    }
}

void dda(int x1,int y1,int x2,int y2, int color){
    int dx=abs(x2-x1), dy=abs(y2-y1);
    int sx=(x1<x2)?1:-1, sy=(y1<y2)?1:-1;
    int steps = dx > dy ? dx : dy;
    float dxp = (float)dx/steps;
    float dyp = (float)dy/steps;
    float x = x1, y = y1;
    for (int i = 0; i <= steps; i++) {
        putpixel(x, y, color);
        x += dxp;
        y += dyp;
    }
}

int main(){
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int x1 = 50, y1 = 50, x2 = 150, y2 = 150;
    int x11 = 150, y11 = 150, x22 = 250, y22 = 250;
    setcolor(RED);
    bresenham(x1, y1, x2, y2, RED);
    setcolor(GREEN);
    dda(x11 , y11, x22, y22, GREEN);

    getch();
    closegraph();
    return 0;
}