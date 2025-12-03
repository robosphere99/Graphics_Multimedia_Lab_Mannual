//  C PROGRAM TO DIPLAYING TEXT IN DIFFERENT SIZE, DIFFERENT COLOR AND DIFFERENT FONT STYLE BY USING outtextxy(), settextstyle() FUNCTION,setcolor() FUNCTION
#include <graphics.h>
#include <conio.h>


int main()
{
    int height = 1000, width = 1200;
    initwindow(width, height, "Anil Alok's Resume");
    setbkcolor(WHITE);
    cleardevice();

    settextstyle(3, HORIZ_DIR, 6);
    setcolor(BLACK);
    outtextxy(450, 100, "RESUME");

    settextstyle(4, HORIZ_DIR, 2);
    setcolor(GREEN);
    outtextxy(50, 175, "Name : Anil Alok    ");

    settextstyle(4, HORIZ_DIR, 2);
    setcolor(RED);
    outtextxy(50, 215, "Registration Number : 2023UG1022");

    settextstyle(4, HORIZ_DIR, 2);
    setcolor(BLUE);
    outtextxy(50, 245, "Section : A");

    //SUBJECTS
    settextstyle(4, HORIZ_DIR, 2);
    setcolor(GREEN);
    outtextxy(50, 285, "Subject : Computer Graphics & Multimedia");

    settextstyle(4, HORIZ_DIR, 2);
    setcolor(BROWN);
    outtextxy(50, 325, "Educational Qualification");
    settextstyle(4, HORIZ_DIR, 1);
    setcolor(BLACK);
    outtextxy(50, 345, "1. High School: Secure 94.20 % in 10th from CBSE Board");
    outtextxy(50, 365, "2. Intermediate: Secure 80 % in 12th from CBSE Board");
    outtextxy(50, 385, "3. Currently Pursuing B.Tech from IIIT RANCHI with 8.42 CGPA");

    settextstyle(4, HORIZ_DIR, 2);
    setcolor(GREEN);
    outtextxy(50, 425, "Eperience");
    settextstyle(4, HORIZ_DIR, 1);
    setcolor(BLACK);
    outtextxy(50, 445, "1. Running a YouTube Channel 'Robosphere' related to IoT");
    outtextxy(50, 465, "2. Iot engineer intern at 'Invent Lab Tech Pvt Ltd' for 6 months");
    outtextxy(50, 485, "3. Selected for e-Toys Hackathon 2023 conducted by CDAC NOIDA");
    settextstyle(4, HORIZ_DIR, 1);
    setcolor(BLACK);
    // all Different color and Different Font Style
    

    


    getch();
    closegraph();
    return 0;
}