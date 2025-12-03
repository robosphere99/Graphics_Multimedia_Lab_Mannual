#include <graphics.h>
#include <conio.h>
#include <math.h>

int main() {
    initwindow(1280,780,"Robosphere");
    cleardevice();
    char name[]= "Name: Anil Alok";
    char roll[]= "Roll No: 2023UG1022";
    char section[]= "Section: A";
    char subject[]= "Subject: MultiMedia";
    char college[]= "College Name: IIIT Ranchi";
    char strength[]= "Strengths: A Online Educator on youtube ,ROBOSPHERE (With 500 Subscribers). \n 7K Followers on LinkedIN. \n 1k Followers on IG.Problem Solver and Quick Learner.";
    char weakness[]= "Weakness: Can focous on only one work at a time. Gets distracted easily.";
    char technical_skills[]= "Skills: C,C++,Python,HTML,CSS,JavaScript,Arduino,Python,OpenCV.";
    char hobbies[]= "Hobbies: Gardening,Reading Books,MAKING ROBOTS,Drone Flying and Coding.";
    char achievements[]= "Achievements: Selected For National level in Robotics and Model Making Compettition 2025.";
    char goals[]= "Goals: To become a successful Entreprenuer.";
    // settextstyle(3,0,5);
    setcolor(WHITE);


    outtextxy(100,100,name);
    outtextxy(100,120,roll);
    outtextxy(100,140,subject);
    outtextxy(100,160,college);
    outtextxy(100,210,strength);
    outtextxy(100,240,weakness);
    outtextxy(100,290,technical_skills);
    outtextxy(100,340,hobbies);
    outtextxy(100,390,achievements);
    outtextxy(100,440,goals);
    getch();
    closegraph();
}
