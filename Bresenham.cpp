#include <graphics.h>
#include <conio.h>

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int X0 = 0, Y0 = 0, Xn = 540, Yn = 220;
    int dx = Xn - X0;
    int dy = Yn - Y0;
    int Pk = 2 * dy - dx;
    int x = X0, y = Y0;

    putpixel(x, y, WHITE);
    for (int i = 0; i < dx; i++) {
        if (Pk >= 0) {
            x = x + 1;
            y = y + 1;
            Pk = Pk + 2 * dy - 2 * dx;
        } else {
            x = x + 1;
            Pk = Pk + 2 * dy;
        }
        putpixel(x, y, WHITE);
    }

    getch();
    closegraph();
    return 0;
}