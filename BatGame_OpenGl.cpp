/*********
   CTIS164 - Template Source Program
----------
STUDENT : Berke Sayicioglu
SECTION : 02
HOMEWORK: CTIS164-HOMEWORK1
----------
PROBLEMS: -
----------
ADDITIONAL FEATURES: BY CLICKING AT RIGHT MOUSE BOTTON, YOU CAN CHANGE THE EYE COLOR OF THE BAT.
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  10 // Period for the timer.
#define TIMER_ON         1// 0:disable timer, 1:enable timer

#define D2R 0.0174532

#define START 0
#define DISPLAY 1

#define STILL 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define MANUAL 0
#define AUTO 1

int red=1, green=1, blue = 1;
/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height
int xA =0 , xB =0;
int AppStt = START;
int CurrentMode = MANUAL;
int CurrentKey = STILL;
//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

//
// To display onto window using OpenGL commands
//
void background()
{
    glBegin(GL_POLYGON); //background color
    glColor3ub(0, 111, 255);
    glVertex2f(-500, -400);
    glVertex2f(500, -400);
    glColor3f(0, 0, 0);
    glVertex2f(500, 500);
    glVertex2f(-500, 500);
    glEnd();
    glColor3f(0, 0, 0);//ground color
    glRectf(-500, -400, 500, -200);//ground
    glColor3ub(211, 223, 102);//moon
    circle(-400, 300, 60);
    glColor3ub(184, 201, 31);
    circle(-400, 280, 10);
    glColor3ub(164, 164, 65);
    circle(-380, 310, 15);
    glColor3ub(164, 164, 65);
    circle(-400, 280, 10);
    glColor3ub(164, 164, 65);
    circle(-435, 330, 10);
    glColor3ub(164, 164, 65);
    circle(-435, 290, 20);

    glColor3ub(82, 82, 82);
    glRectf(200, -100, 450, -200);//castle
    glColor3ub(82, 82, 82);//tower1
    glRectf(200, -10, 250, -200);
    glColor3ub(82, 82, 82);//tower2
    glRectf(305, -10, 345, -200);
    glColor3ub(119, 53, 14);//door
    glRectf(305, -150, 345, -200);
    glColor3ub(119, 53, 14);
    circle(325, -155, 20);
    glColor3ub(82, 82, 82);//right-tower
    glRectf(450, -10, 400, -200);

    glBegin(GL_TRIANGLES);//castle3
    glColor3ub(119,53,14);
    glVertex2f(450, -10);
    glVertex2f(400, -10);
    glVertex2f(425, 75);
    glEnd();

    glBegin(GL_TRIANGLES);//castle2
    glColor3ub(119, 53, 14);
    glVertex2f(250, -10);
    glVertex2f(200, -10);
    glVertex2f(225,75);
    glEnd();

    glBegin(GL_TRIANGLES);//castle1
    glColor3ub(119, 53, 14);
    glVertex2f(345, -10);
    glVertex2f(305, -10);
    glVertex2f(325, 75);
    glEnd();
    glColor3f(1, 1, 1);
    vprint(300, 350, GLUT_BITMAP_9_BY_15, "Berke Sayicioglu");
    vprint(370, 330, GLUT_BITMAP_9_BY_15, "22101821");
    
    glColor3f(1, 0, 0);
    if(CurrentMode==MANUAL)
        vprint(300, -300, GLUT_BITMAP_9_BY_15, "MODE: MANUAL");
    else if (CurrentMode == AUTO) 
       vprint(300, -300, GLUT_BITMAP_9_BY_15, "MODE: AUTO");

    glColor3f(1, 1, 0);
    if (CurrentKey==UP)
        vprint(300, -320, GLUT_BITMAP_9_BY_15, "DIRECTION: UP");
    else if (CurrentKey == DOWN)
        vprint(300, -320, GLUT_BITMAP_9_BY_15, "DIRECTION: DOWN");
    else if (CurrentKey == LEFT)
        vprint(300, -320, GLUT_BITMAP_9_BY_15, "DIRECTION: LEFT");
    else if (CurrentKey == RIGHT)
        vprint(300, -320, GLUT_BITMAP_9_BY_15, "DIRECTION: RIGHT");
    else if (CurrentKey == STILL)
        vprint(300, -320, GLUT_BITMAP_9_BY_15, "DIRECTION: - ");

   
    glColor3f(1, 0.5, 0);
    vprint(-250, -300, GLUT_BITMAP_9_BY_15, "Click <F1> to switch modes and Arrow keys to move the bat");
    glColor3f(1, 0.80, 0);
    vprint(-240, -340, GLUT_BITMAP_9_BY_15, "To change the eye color, press down Right Click.");
    
}
void bat()
{
   
    glColor3ub(7, 3, 28);//body
    circle(0+xA, 0+xB, 40);
    glColor3ub(7, 3, 28);//head
    circle(0+xA, 55+xB, 25);
    glColor3f(red,green,blue);//eyes
   circle(-10+xA, 60+xB, 4);
   glColor3f(red, green, blue);
   circle(10+xA, 60+xB, 4);
   glColor3f(0, 0, 0);
   circle(-10+xA, 60+xB, 3);
   glColor3f(0, 0, 0);
   circle(10+xA, 60+xB, 3);

   glBegin(GL_TRIANGLES);//ear
   glColor3ub(7, 3, 28);
   glVertex2f(-5+xA, 65+xB);
   glVertex2f(-20+xA, 65+xB);
   glVertex2f(-10+xA, 95+xB);
   glEnd();

   glBegin(GL_TRIANGLES);//ear
   glColor3ub(7, 3, 28);
   glVertex2f(20+xA, 65+xB);
   glVertex2f(5+xA, 65+xB);
   glVertex2f(15+xA, 95+xB);
   glEnd();

   glBegin(GL_TRIANGLES);//wing1-right
   glColor3ub(7, 3, 28);
   glVertex2f(-10+xA, -25+xB);
   glVertex2f(12+xA, 25+xB);
   glVertex2f(100+xA, 50+xB);
   glEnd();
   glBegin(GL_TRIANGLES);//wing2-right
   glColor3ub(7, 3, 28);
   glVertex2f(10+xA, -25+xB);
   glVertex2f(18+xA, 5+xB);
   glVertex2f(100+xA, 10+xB);
   glEnd();
   glBegin(GL_TRIANGLES);//wing3-right
   glColor3ub(7, 3, 28);
   glVertex2f(10+xA, -25+xB);
   glVertex2f(10+xA, 5+xB);
   glVertex2f(100+xA, 25+xB);
   glEnd();

   glBegin(GL_TRIANGLES);//wing1-left
   glColor3ub(7, 3, 28);
   glVertex2f(10+xA, -25+xB);
   glVertex2f(-12+xA, 25+xB);
   glVertex2f(-100+xA, 50+xB);
   glEnd();
   glBegin(GL_TRIANGLES);//wing2-left
   glColor3ub(7, 3, 28);
   glVertex2f(-10+xA, -25+xB);
   glVertex2f(-18+xA, 5+xB);
   glVertex2f(-100+xA, 10+xB);
   glEnd();
   glBegin(GL_TRIANGLES);//wing3-left
   glColor3ub(7, 3, 28);
   glVertex2f(-10+xA, -25+xB);
   glVertex2f(-10+xA, 5+xB);
   glVertex2f(-100+xA, 25+xB);
   glEnd();

   glLineWidth(8);//left leg
   glColor3ub(7, 3, 28);
   glBegin(GL_LINES);
   glVertex2f(-5+xA,-10+xB);
   glVertex2f(-25+xA,-47+xB);
   glEnd();
   glLineWidth(8);//right leg
   glColor3ub(7, 3, 28);
   glBegin(GL_LINES);
   glVertex2f(5+xA, -10+xB);
   glVertex2f(25+xA, -47+xB);
   glEnd();
   glLineWidth(1);//mouth
   glColor3ub(255, 255, 255);
   glBegin(GL_LINES);
   glVertex2f(10+xA, 45+xB);
   glVertex2f(-10+xA, 45+xB);
   glEnd();

   glBegin(GL_TRIANGLES);//teeth
   glColor3ub(255, 255, 255);
   glVertex2f(10+xA, 45+xB);
   glVertex2f(4+xA, 45+xB);
   glVertex2f(7+xA, 40+xB);
   glEnd();
   glBegin(GL_TRIANGLES);//teeth
   glColor3ub(255, 255, 255);
   glVertex2f(-10+xA, 45+xB);
   glVertex2f(-04+xA, 45+xB);
   glVertex2f(-06+xA, 40+xB);
   glEnd();
   
   
   
   


}
void bat()
{

    glColor3ub(7, 3, 28);//body
    circle(0 + xA, 0 + xB, 40);
    glColor3ub(7, 3, 28);//head
    circle(0 + xA, 55 + xB, 25);
    glColor3f(red, green, blue);//eyes
    circle(-10 + xA, 60 + xB, 4);
    glColor3f(red, green, blue);
    circle(10 + xA, 60 + xB, 4);
    glColor3f(0, 0, 0);
    circle(-10 + xA, 60 + xB, 3);
    glColor3f(0, 0, 0);
    circle(10 + xA, 60 + xB, 3);

    glBegin(GL_TRIANGLES);//ear
    glColor3ub(7, 3, 28);
    glVertex2f(-5 + xA, 65 + xB);
    glVertex2f(-20 + xA, 65 + xB);
    glVertex2f(-10 + xA, 95 + xB);
    glEnd();

    glBegin(GL_TRIANGLES);//ear
    glColor3ub(7, 3, 28);
    glVertex2f(20 + xA, 65 + xB);
    glVertex2f(5 + xA, 65 + xB);
    glVertex2f(15 + xA, 95 + xB);
    glEnd();

    glBegin(GL_TRIANGLES);//wing1-right
    glColor3ub(7, 3, 28);
    glVertex2f(-10 + xA, -25 + xB);
    glVertex2f(12 + xA, 25 + xB);
    glVertex2f(100 + xA, 50 + xB);
    glEnd();
    glBegin(GL_TRIANGLES);//wing2-right
    glColor3ub(7, 3, 28);
    glVertex2f(10 + xA, -25 + xB);
    glVertex2f(18 + xA, 5 + xB);
    glVertex2f(100 + xA, 10 + xB);
    glEnd();
    glBegin(GL_TRIANGLES);//wing3-right
    glColor3ub(7, 3, 28);
    glVertex2f(10 + xA, -25 + xB);
    glVertex2f(10 + xA, 5 + xB);
    glVertex2f(100 + xA, 25 + xB);
    glEnd();

    glBegin(GL_TRIANGLES);//wing1-left
    glColor3ub(7, 3, 28);
    glVertex2f(10 + xA, -25 + xB);
    glVertex2f(-12 + xA, 25 + xB);
    glVertex2f(-100 + xA, 50 + xB);
    glEnd();
    glBegin(GL_TRIANGLES);//wing2-left
    glColor3ub(7, 3, 28);
    glVertex2f(-10 + xA, -25 + xB);
    glVertex2f(-18 + xA, 5 + xB);
    glVertex2f(-100 + xA, 10 + xB);
    glEnd();
    glBegin(GL_TRIANGLES);//wing3-left
    glColor3ub(7, 3, 28);
    glVertex2f(-10 + xA, -25 + xB);
    glVertex2f(-10 + xA, 5 + xB);
    glVertex2f(-100 + xA, 25 + xB);
    glEnd();

    glLineWidth(8);//left leg
    glColor3ub(7, 3, 28);
    glBegin(GL_LINES);
    glVertex2f(-5 + xA, -10 + xB);
    glVertex2f(-25 + xA, -47 + xB);
    glEnd();
    glLineWidth(8);//right leg
    glColor3ub(7, 3, 28);
    glBegin(GL_LINES);
    glVertex2f(5 + xA, -10 + xB);
    glVertex2f(25 + xA, -47 + xB);
    glEnd();
    glLineWidth(1);//mouth
    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2f(10 + xA, 45 + xB);
    glVertex2f(-10 + xA, 45 + xB);
    glEnd();

    glBegin(GL_TRIANGLES);//teeth
    glColor3ub(255, 255, 255);
    glVertex2f(10 + xA, 45 + xB);
    glVertex2f(4 + xA, 45 + xB);
    glVertex2f(7 + xA, 40 + xB);
    glEnd();
    glBegin(GL_TRIANGLES);//teeth
    glColor3ub(255, 255, 255);
    glVertex2f(-10 + xA, 45 + xB);
    glVertex2f(-04 + xA, 45 + xB);
    glVertex2f(-06 + xA, 40 + xB);
    glEnd();


}
void display() {
    //
    // clear window to black
    //
    
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0.5, 0);
    vprint(-250, -300, GLUT_BITMAP_9_BY_15, "Click <F1> to switch modes and Arrow keys to move the bat");
    
    background();
    glColor3f(1, 0.5, 0);
    if (AppStt == START) {
        
        vprint(-180, 80, GLUT_BITMAP_9_BY_15, "Click on the screen to display a cute bat.");
    }
    if (AppStt==DISPLAY)
    bat();
   
    
    
    

    glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = true; break;
    case GLUT_KEY_DOWN: down = true; break;
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
    }

    if (key == GLUT_KEY_F1)
    {
        if (CurrentMode == MANUAL)
            CurrentMode = AUTO;
        else
           CurrentMode = MANUAL;
    }

    if (CurrentMode == MANUAL) 
    {
        if (key == GLUT_KEY_UP)
        {
            if (xB < winHeight / 2 - 90)
                xB++;
        }
        if (key == GLUT_KEY_DOWN)
        {
            if (xB > -(winHeight-650 ) / 2 - 90)
                xB--;
        }
        if (key == GLUT_KEY_RIGHT)
        {
            if (xA < winWidth / 2 - 90)
                xA++;
        }
        if (key == GLUT_KEY_LEFT)
        {
            if (xA > -(winWidth - 355) / 2 - 90)
                xA--;
        }
    }


    
    
    

        if (key == GLUT_KEY_UP)
            CurrentKey = UP;
        else if (key == GLUT_KEY_DOWN)
            CurrentKey = DOWN;
        else if (key == GLUT_KEY_LEFT)
            CurrentKey = LEFT;
        else if (key == GLUT_KEY_RIGHT)
            CurrentKey = RIGHT;
        else
            CurrentKey = STILL;
        
        

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN)
    
        if (AppStt == START) {
            AppStt = DISPLAY;
            
            xA = x - winWidth / 2;
            xB = winHeight / 2 - y;
        }
        else
        {
            xA = x - winWidth / 2;
            xB = winHeight / 2 - y;

        }
    
    if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN) {
        red =1;
        green = 0;
        blue = 0;
    }
    if (button == GLUT_RIGHT_BUTTON && stat == GLUT_UP) {
        red = 1;
        green = 1;
        blue = 1;
    }


}


//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    // Write your codes here.
   
    if (CurrentMode == AUTO)
    {
        if (CurrentKey == UP)

            if (xB < (winHeight / 2 - 90))
                xB++;
            else
                CurrentKey = DOWN;
        
        if(CurrentKey == DOWN)
        
            if (xB > -(winHeight  / 2 - 240))
                xB--;
            else
                CurrentKey = UP;
        
        if (CurrentKey == LEFT)
        
            if (xA > -(winWidth  / 2 - 90))
                xA--;
            else
                CurrentKey = RIGHT;
              
        
        if (CurrentKey == RIGHT)
        
            if (xA < (winWidth/ 2 - 90))
                xA++;
            else
                CurrentKey = LEFT;
        

    }

    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}
#endif

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("CTIS164-HOMEWORK");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}
