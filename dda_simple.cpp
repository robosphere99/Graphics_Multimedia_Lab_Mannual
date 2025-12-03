#include <graphics.h>
#include <math.h>
#include <conio.h>

void DDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float Xinc = dx / (float) steps;
    float Yinc = dy / (float) steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        putpixel(round(x), round(y), WHITE);
        x += Xinc;
        y += Yinc;
    }
}

int main() {
    initwindow(800, 600, "DDA Line Algorithm");
    DDA(100, 100, 400, 300);
    getch();
    closegraph();
    return 0;
}
