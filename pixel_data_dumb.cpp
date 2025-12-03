#include <graphics.h>
#include <conio.h>
#include <fstream>

int main() {
    const int WIDTH = 800;
    const int HEIGHT = 600;
    initwindow(WIDTH, HEIGHT, "Robosphere - Pixel Dump");

    
    setbkcolor(BLACK);
    cleardevice();


    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(20, 20, WIDTH - 20, HEIGHT - 20);

    int cx = WIDTH/2;
    int cy = HEIGHT/2 - 30;
    int r = 80;
    setfillstyle(SOLID_FILL, BLUE);
    fillellipse(cx, cy, r, r);

setfillstyle(SOLID_FILL, RED);
int trianglePoints[6] = {120, HEIGHT - 120, 260, HEIGHT - 280, 400, HEIGHT - 120};
fillpoly(3, trianglePoints);


// outtextxy(30, HEIGHT - 30, (char*)"Pixel dump saved to pixel_data.csv. Press any key to exit.");


    setfillstyle(SOLID_FILL, GREEN);
    bar(WIDTH - 160, 60, WIDTH - 60, 160);

    setcolor(WHITE);
    circle(cx, cy, r);
    rectangle(20, 20, WIDTH - 20, HEIGHT - 20);
    rectangle(WIDTH - 160, 60, WIDTH - 60, 160);

    std::ofstream fout("pixel_data.csv");
    if (!fout.is_open()) {
 
        getch();
        closegraph();
        return 0;
    }
    fout << "x,y,color_index\n";
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            int col = getpixel(x, y);
            fout << x << ',' << y << ',' << col << '\n';
            printf("Pixel (%d,%d) Color: %d\n", x, y, col); 
        }
    }
    fout.close();


    outtextxy(30, HEIGHT - 100, "Pixel dump saved to pixel_data.csv. Press any key to exit.");
    getch();

    closegraph();
    return 0;
}
