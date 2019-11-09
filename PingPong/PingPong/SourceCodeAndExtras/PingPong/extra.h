#ifndef EXTRA_H_INCLUDED
#define EXTRA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include<time.h>

void seed(){
    srand (time(NULL));
}

int random(int a){
    return (rand()%a);
}

void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void DrawCenteredRectangle(float x, float y, float width, float height){
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x+width/2, y+height/2);
    glVertex2f(x-width/2, y+height/2);
    glVertex2f(x-width/2, y-height/2);
    glVertex2f(x+width/2, y-height/2);
    glEnd();
    glPopMatrix();
}

void DrawToppedRectangle(float x, float y, float width, float height){
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x+width, y);
    glVertex2f(x, y);
    glVertex2f(x, y+height);
    glVertex2f(x+width, y+height);
    glEnd();
    glPopMatrix();
};

void DrawBodRectangle(float rectangleborder){
    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex2f(xMaxPositive,yMaxPositive);
    glVertex2f(xMaxNegative,yMaxPositive);
    glVertex2f(xMaxNegative,yMaxPositive-rectangleborder);
    glVertex2f(xMaxPositive,yMaxPositive-rectangleborder);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(xMaxNegative+rectangleborder,yMaxPositive);
    glVertex2f(xMaxNegative,yMaxPositive);
    glVertex2f(xMaxNegative,yMaxNegative);
    glVertex2f(xMaxNegative+rectangleborder,yMaxNegative);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(xMaxPositive,yMaxNegative+rectangleborder);
    glVertex2f(xMaxNegative,yMaxNegative+rectangleborder);
    glVertex2f(xMaxNegative,yMaxNegative);
    glVertex2f(xMaxPositive,yMaxNegative);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(xMaxPositive,yMaxPositive);
    glVertex2f(xMaxPositive-rectangleborder,yMaxPositive);
    glVertex2f(xMaxPositive-rectangleborder,yMaxNegative);
    glVertex2f(xMaxPositive,yMaxNegative);
    glEnd();
    glPopMatrix();
}

bool checkwithinbox(float X,float Y,float Xcoord,float Ycoord,float Width,float Height){
if(X>(Xcoord-(Width/2)) && X<(Xcoord+(Width/2)) && Y>(Ycoord-(Height/2)) && Y<(Ycoord+(Height/2)))
{
    return true;
}
else{
    return false;
}
}

bool checkwithinlimit(float X,float Y,float x1,float y1,float x2,float y2){
if(X>x2 && X<x1 && Y>y1 && Y<y2)
{
    return true;
}
else{
    return false;
}
}

#endif
