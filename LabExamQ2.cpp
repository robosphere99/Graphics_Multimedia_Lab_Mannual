#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>

#define INSIDE 0
#define LEFT   1
#define RIGHT  2
#define BOTTOM 4
#define TOP    8

int computeOutCode(int x, int y, int x_min, int y_min, int x_max, int y_max) {
	int code = INSIDE;
	if (x < x_min) code |= LEFT;
	else if (x > x_max) code |= RIGHT;
	if (y < y_min) code |= BOTTOM;
	else if (y > y_max) code |= TOP;
	return code;
}

void cohenSutherlandLineClip(int x1, int y1, int x2, int y2) {
	int x_min = 50, x_max = 150, y_min = 50, y_max = 150;

	int outcode1 = computeOutCode(x1, y1, x_min, y_min, x_max, y_max);
	int outcode2 = computeOutCode(x2, y2, x_min, y_min, x_max, y_max);

	setcolor(WHITE);
	rectangle(x_min, y_min, x_max, y_max);

	int accept = 0;
	while (1) {
		if ((outcode1 | outcode2) == 0) {
			accept = 1;
			break;
		} else if (outcode1 & outcode2) {
			break;
		} else {
			int outcodeOut = outcode1 ? outcode1 : outcode2;
			float x, y;

			if (outcodeOut & TOP) {
				x = x1 + (float)(x2 - x1) * (y_max - y1) / (y2 - y1);
				y = y_max;
			} else if (outcodeOut & BOTTOM) {
				x = x1 + (float)(x2 - x1) * (y_min - y1) / (y2 - y1);
				y = y_min;
			} else if (outcodeOut & RIGHT) {
				y = y1 + (float)(y2 - y1) * (x_max - x1) / (x2 - x1);
				x = x_max;
			} else { 
				y = y1 + (float)(y2 - y1) * (x_min - x1) / (x2 - x1);
				x = x_min;
			}

			if (outcodeOut == outcode1) {
				x1 = (int)round(x);
				y1 = (int)round(y);
				outcode1 = computeOutCode(x1, y1, x_min, y_min, x_max, y_max);
			} else {
				x2 = (int)round(x);
				y2 = (int)round(y);
				outcode2 = computeOutCode(x2, y2, x_min, y_min, x_max, y_max);
			}
		}
	}

	if (accept) {
		setcolor(GREEN);
		line(x1, y1, x2, y2);
	} else {
		setcolor(RED);
	}
}

int main() {
	int gd = DETECT, gm;
	initgraph(&gd, &gm, (char *)"");

	int x1 = 20, y1 = 20, x2 = 180, y2 = 180;
	setcolor(RED);
	line(x1, y1, x2, y2);

	cohenSutherlandLineClip(x1, y1, x2, y2);

	getch();
	closegraph();
	return 0;
}
