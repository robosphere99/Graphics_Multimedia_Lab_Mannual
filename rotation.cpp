#include<graphics.h>
#include<conio.h>
#include<math.h>

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    setcolor(RED);
    int x1 = 50, y1 = 150, x2 = 150, y2 = 150;
    int x3 = 150, y3 = 250, x4 = 50, y4 = 250;
    int x5 = 100, y5 = 100;

    rectangle(x1, y1, x3, y3);
    line(50, 150, 100, 100);
    line(100, 100, 150, 150);
    outtextxy(70, 260, (char *)"Original");

    int cx = 100, cy = 200;
    float angle = 30;
    float rad = angle * (M_PI / 180.0);

    
    int rx1 = cx + (x1 - cx) * cos(rad) - (y1 - cy) * sin(rad);
    int ry1 = cy + (x1 - cx) * sin(rad) + (y1 - cy) * cos(rad);
    int rx2 = cx + (x2 - cx) * cos(rad) - (y2 - cy) * sin(rad);
    int ry2 = cy + (x2 - cx) * sin(rad) + (y2 - cy) * cos(rad);
    int rx3 = cx + (x3 - cx) * cos(rad) - (y3 - cy) * sin(rad);
    int ry3 = cy + (x3 - cx) * sin(rad) + (y3 - cy) * cos(rad);
    int rx4 = cx + (x4 - cx) * cos(rad) - (y4 - cy) * sin(rad);
    int ry4 = cy + (x4 - cx) * sin(rad) + (y4 - cy) * cos(rad);
    int rx5 = cx + (x5 - cx) * cos(rad) - (y5 - cy) * sin(rad);
    int ry5 = cy + (x5 - cx) * sin(rad) + (y5 - cy) * cos(rad);

    setcolor(GREEN);
    line(rx1, ry1, rx2, ry2);
    line(rx2, ry2, rx3, ry3);
    line(rx3, ry3, rx4, ry4);
    line(rx4, ry4, rx1, ry1);
    line(rx1, ry1, rx5, ry5);
    line(rx5, ry5, rx2, ry2);
    outtextxy(250, 260, (char *)"Rotated");

    getch();
    closegraph();
    return 0;
}
