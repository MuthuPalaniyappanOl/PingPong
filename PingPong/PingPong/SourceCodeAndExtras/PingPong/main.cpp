#include <windows.h>
#include <iostream>
#include <GL/glut.h>
#include <Math.h>
#include <unistd.h>
#include <cmath>
#include <string>
#include <stdio.h>
#define PI 3.14159265f
typedef float GameCoordinates;
using namespace std;

char title[] = "PingPong";
int windowWidth  = 640;
int windowHeight = 480;
int windowPosX   = 50;
int windowPosY   = 50;

bool GameStart = true,
     GameMode1 = false,
     GameMode2 = false,
     GameMode3 = false,
     GameMode1Result = false,
     GameMode2Result = false,
     GameMode3Result = false,
     Credits = false;

int refreshMillis = 30;
GLdouble xMaxNegative, xMaxPositive, yMaxNegative, yMaxPositive;
bool fullScreenMode = false;
bool Player1UpPress = false;
bool Player1DownPress = false;
bool Player2UpPress = false;
bool Player2DownPress = false;

#include "extra.h"
#include "main.h"

void initGL() {
   glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(GameStart == true){
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0,1.0,1.0);
        renderBitmapString(-0.25,0.2,GLUT_BITMAP_9_BY_15,"Ping Pong Game");
        glColor3f(1.0,1.0,1.0);
        DrawCenteredRectangle(0,0,1,0.25);
        glColor3f(0.0, 0.0, 0.0);
        renderBitmapString(-0.20,0.0,GLUT_BITMAP_9_BY_15,"Classic Play");

        glColor3f(1.0,1.0,1.0);
        DrawCenteredRectangle(-0.13,-0.155,0.475,0.3);
        glColor3f(0.0, 0.0, 0.0);
        renderBitmapString(-0.38,-0.32,GLUT_BITMAP_9_BY_15,"VS CPU");

        glColor3f(1.0,1.0,1.0);
        DrawCenteredRectangle(0.13,-0.155,0.475,0.3);
        glColor3f(0.0, 0.0, 0.0);
        renderBitmapString(0.17,-0.32,GLUT_BITMAP_9_BY_15,"Pro");
        renderBitmapString(0.17,-0.38,GLUT_BITMAP_9_BY_15,"Dual");

        glColor3f(1.0,1.0,1.0);
        DrawCenteredRectangle(-0.13,-0.27,0.475,0.1);
        glColor3f(0.0, 0.0, 0.0);
        renderBitmapString(-0.38,-0.55,GLUT_BITMAP_9_BY_15,"Credits");

        glColor3f(1.0,1.0,1.0);
        DrawCenteredRectangle(0.13,-0.27,0.475,0.1);
        glColor3f(0.0, 0.0, 0.0);
        renderBitmapString(0.17,-0.55,GLUT_BITMAP_9_BY_15,"Exit");
    }
    else if(GameMode1 == true){
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.5,0.5,0.5);
        DrawBodRectangle(0.05);
        Ball.PlantBall();
        Ball.ApplyBallLogicsForMotion();
        Player1.DrawPaddle();
        Player2.DrawPaddle();
        int num1 = Player1.showScore();
        char buffer1[10]={'\0'};
        sprintf(buffer1, "%d", num1);
        renderBitmapString(-0.4f, yMaxPositive - 0.2 , GLUT_BITMAP_HELVETICA_18, buffer1);
        int num2 = Player2.showScore();
        char buffer2[10]={'\0'};
        sprintf(buffer2, "%d", num2);
        renderBitmapString(0.4f, yMaxPositive - 0.2 , GLUT_BITMAP_HELVETICA_18, buffer2);
    }
    else if(GameMode1Result == true){
        if(Player1.showScore()==7){
            glColor3f(1.0, 0.0, 0.0);
            renderBitmapString(-0.25,0,GLUT_BITMAP_9_BY_15,"Player 1 Wins");
        }
        else if(Player2.showScore()==7){
            glColor3f(1.0, 0.0, 0.0);
            renderBitmapString(-0.25,0,GLUT_BITMAP_9_BY_15,"Player 2 Wins");
        }
    }
    else if(GameMode2 == true){
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.5,0.5,0.5);
        DrawBodRectangle(0.05);
        Ball.PlantBall();
        Ball.ApplyBallLogicsForMotion();
        Player1.DrawPaddle();
        Player2.DrawPaddle();
        Player2.CPULogics();
        int num1 = Player1.showScore();
        char buffer1[10]={'\0'};
        sprintf(buffer1, "%d", num1);
        renderBitmapString(-0.4f, yMaxPositive - 0.2 , GLUT_BITMAP_HELVETICA_18, buffer1);
        int num2 = Player2.showScore();
        char buffer2[10]={'\0'};
        sprintf(buffer2, "%d", num2);
        renderBitmapString(0.4f, yMaxPositive - 0.2 , GLUT_BITMAP_HELVETICA_18, buffer2);
    }
    else if(GameMode2Result == true){
        if(Player1.showScore()==3){
            glColor3f(1.0, 0.0, 0.0);
            renderBitmapString(-0.25,0,GLUT_BITMAP_9_BY_15,"Player Wins");
        }
        else if(Player2.showScore()==3){
            glColor3f(1.0, 0.0, 0.0);
            renderBitmapString(-0.25,0,GLUT_BITMAP_9_BY_15,"CPU Wins");
        }
    }
    else if(GameMode3 == true){
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.5,0.5,0.5);
        DrawBodRectangle(0.05);
        Ball.PlantBall();
        Ball.ApplyBallLogicsForMotion();
        Ball.proLogics();
        Player1.DrawPaddle();
        Player2.DrawPaddle();
        int num1 = Player1.showScore();
        char buffer1[10]={'\0'};
        sprintf(buffer1, "%d", num1);
        renderBitmapString(-0.4f, yMaxPositive - 0.2 , GLUT_BITMAP_HELVETICA_18, buffer1);
        int num2 = Player2.showScore();
        char buffer2[10]={'\0'};
        sprintf(buffer2, "%d", num2);
        renderBitmapString(0.4f, yMaxPositive - 0.2 , GLUT_BITMAP_HELVETICA_18, buffer2);
    }
    else if(GameMode3Result == true){
        if(Player1.showScore()==10){
            glColor3f(1.0, 0.0, 0.0);
            renderBitmapString(-0.25,0,GLUT_BITMAP_9_BY_15,"Player 1 Wins");
        }
        else if(Player2.showScore()==10){
            glColor3f(1.0, 0.0, 0.0);
            renderBitmapString(-0.25,0,GLUT_BITMAP_9_BY_15,"Player 2 Wins");
        }
    }
    else if(Credits == true){
        glColor3f(0.0, 1.0, 0.0);
        renderBitmapString(-0.5,0.1,GLUT_BITMAP_9_BY_15,"Done By : Muthu Palaniyapan Ol");
        renderBitmapString(-0.25,0.0,GLUT_BITMAP_9_BY_15,"Country : India");
        renderBitmapString(-0.35,-0.1,GLUT_BITMAP_9_BY_15,"Game Name : PingPong");
        renderBitmapString(-0.5,-0.2,GLUT_BITMAP_9_BY_15,"Completed On : 20-OCTOBER-2019");
        renderBitmapString(-0.35,-0.3,GLUT_BITMAP_9_BY_15,"Version : 3.00 00 00");
    }
    else{
        exit(0);
    }
    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height) {
        xMaxNegative   = -1.0 * aspect;
        xMaxPositive  = 1.0 * aspect;
        yMaxNegative = -1.0;
        yMaxPositive    = 1.0;
    } else {
        xMaxNegative   = -1.0;
        xMaxPositive  = 1.0;
        yMaxNegative = -1.0 / aspect;
        yMaxPositive    = 1.0 / aspect;
    }
    gluOrtho2D(xMaxNegative, xMaxPositive, yMaxNegative, yMaxPositive);
    glutReshapeWindow( 640, 480);
}

void Timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(refreshMillis, Timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
   switch (key) {
        case 27:
            break;
        case 'w':
            Player1UpPress = true;
            break;
        case 's':
            Player1DownPress = true;
            break;
        default:
            break;
   }
}

void keyboardUp(unsigned char key, int x, int y) {
   switch (key) {
        case 'w':
            Player1UpPress = false;
            break;
        case 's':
            Player1DownPress = false;
            break;
        default:
            break;
   }
}

void specialKeys(int key, int x, int y) {
   switch (key) {
      case GLUT_KEY_F1:
         break;
         case GLUT_KEY_UP:
            Player2UpPress = true;
            break;
        case GLUT_KEY_DOWN:
            Player2DownPress = true;
            break;
        default:
            break;
   }
}

void specialKeysUp(int key, int x, int y) {
   switch (key) {
      case GLUT_KEY_F1:
         break;
         case GLUT_KEY_UP:
            Player2UpPress = false;
            break;
        case GLUT_KEY_DOWN:
            Player2DownPress = false;
            break;
        default:
            break;
   }
}

void MouseFunc(int button, int state, int x, int y)
{
    float X = (float) x / (windowWidth/2) - 1.0;
    float Y = (float) (windowHeight-y) / (windowHeight/2) - 1.0;

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if((GameStart == true) && checkwithinbox(X,Y,0,0,0.75,0.25)) {
            GameMode1 = true;
            GameStart = false;
        }
        if((GameStart == true) && checkwithinbox(X,Y,-0.20,-0.3,0.36,0.3)) {
            GameMode2 = true;
            GameStart = false;
        }
        if((GameStart == true) && checkwithinbox(X,Y,0.19,-0.3,0.36,0.3)) {
            GameMode3 = true;
            GameStart = false;
        }
        else if((GameStart == true) && checkwithinbox(X,Y,-0.2,-0.55,0.35,0.1)) {
            Credits = true;
            GameStart = false;
        }
        else if((GameStart == true) && checkwithinbox(X,Y,0.2,-0.55,0.35,0.1)) {
            exit(0);
        }
        else if((GameMode1Result == true)) {
            GameMode1Result = false;
            GameStart = true;
            Player1.scoreZero();
            Player2.scoreZero();
        }
        else if((GameMode2Result == true)) {
            GameMode2Result = false;
            GameStart = true;
            Player1.scoreZero();
            Player2.scoreZero();
        }
        else if((GameMode3Result == true)) {
            GameMode3Result = false;
            GameStart = true;
            Player1.scoreZero();
            Player2.scoreZero();
        }
        else if((Credits == true)) {
            Credits = false;
            GameStart = true;
        }
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

	}
}

void Updater(){
    if(Player1UpPress == true){
        Player1.MovePaddleUp();
    }
    else{
        ;
    }
    if(Player1DownPress == true){
        Player1.MovePaddleDown();
    }
    else{
        ;
    }
    if(Player2UpPress == true && (GameMode1 == true||GameMode3==true)){
        Player2.MovePaddleUp();
    }
    else{
        ;
    }
    if(Player2DownPress == true && (GameMode1 == true||GameMode3==true)){
        Player2.MovePaddleDown();
    }
    else{
        ;
    }
}
int main(int argc, char** argv) {
   seed();
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE);
   glutInitWindowSize(windowWidth, windowHeight);
   glutInitWindowPosition(windowPosX, windowPosY);
   glutCreateWindow(title);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutTimerFunc(0, Timer, 0);
   glutSpecialFunc(specialKeys);
   glutSpecialUpFunc(specialKeysUp);
   glutKeyboardFunc(keyboard);
   glutKeyboardUpFunc(keyboardUp);
   glutMouseFunc(MouseFunc);
   glutIdleFunc(Updater);
   initGL();
   glutMainLoop();
   return 0;
}
