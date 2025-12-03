#include<graphics.h>
#include<conio.h>
void DDA(int x1,int y1,int x2,int y2){
    int delX = x2 - x1;
    int delY = y2 - y1;
    int steps = abs(delX) > abs(delY) ? abs(delX) : abs(delY);
    float dx = delX / (float)steps;
    float dy = delY / (float)steps;
    float x = x1;
    float y = y1;
    for (int i = 0; i <= steps; i++) {
        putpixel(x, y, WHITE);
        x = x + dx;
        y = y + dy;
    }
}
void dabba(int x1,int y1,int x2,int y2){
    DDA(x1,y1,x2,y1);
    DDA(x2,y1,x2,y2);
    DDA(x2,y2,x1,y2);
    DDA(x1,y2,x1,y1);
}

int main() {
    int gd=DETECT,gm;
    initgraph(&gd,&gm,(char*)"Robosphere");

    dabba(100,100,200,200);
    // line()
    getch();
    closegraph();
    return 0;
}