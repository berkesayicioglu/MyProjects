/*********
   CTIS164 - Template Source Program
----------
STUDENT : Berke Sayicioglu
SECTION : 02
HOMEWORK:
----------
PROBLEMS:
----------
ADDITIONAL FEATURES: 
1-If the bat catches the bee, bat's eyes instantly turn into red untill the end of the program. 
2-Every second the score increases until the bat chases the bee.If the bee is catched,score is set to 0.
3-If the bat catches the bee,a proper message is displayed on the screen.
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
#include "vec.h"

#define ENEMY_SPEED 4
#define OUTSIDE 0
#define INSIDE 1
bool space = 0;
int mouse = INSIDE;

int mode = INSIDE;

#define WINDOW_WIDTH  1400
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  20 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height
int sposx = 0, sposy = 0;
bool redeye = false;
int count = 0;
bool gameover = false;
typedef struct {
    vec_t pos;
    vec_t vel;  //velocity
    bool  visibility; // visibility: true if the player sees the enemy
} bat_t;

bat_t  s = { { 0, 45 } };

typedef struct {
    vec_t pos;
    float angle;
} bug_t;

bug_t b = { { 0, 0 }, 200 };

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

void vertex(vec_t bg, vec_t trg, double angle)
{
    double bgx = (bg.x * cos(angle) - bg.y * sin(angle) )+ trg.x;

    double bgy = (bg.x * sin(angle) + bg.y * cos(angle)) + trg.x;

    glVertex2d(bgx, bgy);

}
void background()
{

    glBegin(GL_POLYGON); //background color
    glColor3ub(241,0, 131);
    glVertex2f(-600, -300);
    glVertex2f(600, -300);
    glColor3f(241, 0, 131);
    glVertex2f(600, 300);
    glVertex2f(-600, 300);
    glEnd();

   
    polar_t ang = rec2pol(s.vel);

    vprint(400, -320, GLUT_BITMAP_8_BY_13, "Bat's Chasing Angle: %.0f", ang.angle);

    if (b.pos.x > 600 || b.pos.x < -600 || b.pos.y > 300 ||b.pos.y < -300) 
    {
        vprint(-600, -320, GLUT_BITMAP_9_BY_15, "Little Bee is <OUTSIDE>");
        mouse = OUTSIDE;
    }
    else 
    {
        vprint(-600, -320, GLUT_BITMAP_9_BY_15, "Little Bee is >INSIDE<");
        mouse = INSIDE;
    }
    if (space == 0)
        vprint(-95, -320, GLUT_BITMAP_9_BY_15, "Press |SPACEBAR| to pause");
    else
        vprint(-95, -320, GLUT_BITMAP_9_BY_15, "Press |SPACEBAR| to restart");
    glColor3f(1, 1, 1);

    vprint(-50, 370, GLUT_BITMAP_9_BY_15, "Berke Sayicioglu");
    vprint(-20, 350, GLUT_BITMAP_9_BY_15, "22101821");
    vprint(-100, 330, GLUT_BITMAP_9_BY_15, "-A bat is chasing a bee-");

    vprint(-600, 325, GLUT_BITMAP_9_BY_15, "SCORE: %d",count/10);
    
   


}
void bat()
{
    double angle = b.angle * D2R;

    vec_t vEnd = addV(s.pos, pol2rec({ 30, b.angle }));

    glColor3ub(7, 3, 28);//body
    circle(0 + s.pos.x, 0 + s.pos.y, 40);
    glColor3ub(7, 3, 28);//head
    circle(0 + s.pos.x, 55 + s.pos.y, 25);


    glColor3f(1,1,1);//eyes
    circle(-10 + s.pos.x, 60 + s.pos.y, 4);
    glColor3f(1,1,1);
    circle(10 + s.pos.x, 60 +s.pos.y, 4);
   
    //this part doesnt work//
    if (!redeye)
    {
        glColor3f(0, 0, 0);
        circle(-10 + s.pos.x, 60 + s.pos.y, 3);
        glColor3f(0, 0, 0);
        circle(10 + s.pos.x, 60 + s.pos.y, 3);
    }
    else
    {
        glColor3f(1, 0, 0);
        circle(-10 + s.pos.x, 60 + s.pos.y, 4);
        glColor3f(1, 0, 0);
        circle(10 + s.pos.x, 60 + s.pos.y, 4);
    }
   
    glBegin(GL_TRIANGLES);//ear
    glColor3ub(7, 3, 28);
    glVertex2f(-5 + s.pos.x, 65 + s.pos.y);
    glVertex2f(-20 + s.pos.x, 65 + s.pos.y);
    glVertex2f(-10 + s.pos.x, 95 + s.pos.y);
    glEnd();

    glBegin(GL_TRIANGLES);//ear
    glColor3ub(7, 3, 28);
    glVertex2f(20 + s.pos.x, 65 + s.pos.y);
    glVertex2f(5 + s.pos.x, 65 + s.pos.y);
    glVertex2f(15 + s.pos.x, 95 + s.pos.y);
    glEnd();

    glBegin(GL_TRIANGLES);//wing1-right
    glColor3ub(7, 3, 28);
    glVertex2f(-10 + s.pos.x, -25 + s.pos.y);
    glVertex2f(12 + s.pos.x, 25 + s.pos.y);
    glVertex2f(100 + s.pos.x, 50 + s.pos.y);
    glEnd();
    glBegin(GL_TRIANGLES);//wing2-right
    glColor3ub(7, 3, 28);
    glVertex2f(10 + s.pos.x, -25 + s.pos.y);
    glVertex2f(18 + s.pos.x, 5 + s.pos.y);
    glVertex2f(100 + s.pos.x, 10 + s.pos.y);
    glEnd();
    glBegin(GL_TRIANGLES);//wing3-right
    glColor3ub(7, 3, 28);
    glVertex2f(10 + s.pos.x, -25 + s.pos.y);
    glVertex2f(10 + s.pos.x, 5 + s.pos.y);
    glVertex2f(100 + s.pos.x, 25 + s.pos.y);
    glEnd();

    glBegin(GL_TRIANGLES);//wing1-left
    glColor3ub(7, 3, 28);
    glVertex2f(10 + s.pos.x, -25 + s.pos.y);
    glVertex2f(-12 + s.pos.x, 25 + s.pos.y);
    glVertex2f(-100 + s.pos.x, 50 + s.pos.y);
    glEnd();
    glBegin(GL_TRIANGLES);//wing2-left
    glColor3ub(7, 3, 28);
    glVertex2f(-10 + s.pos.x, -25 + s.pos.y);
    glVertex2f(-18 + s.pos.x, 5 + s.pos.y);
    glVertex2f(-100 + s.pos.x, 10 + s.pos.y);
    glEnd();
    glBegin(GL_TRIANGLES);//wing3-left
    glColor3ub(7, 3, 28);
    glVertex2f(-10 + s.pos.x, -25 + s.pos.y);
    glVertex2f(-10 + s.pos.x, 5 + s.pos.y);
    glVertex2f(-100 + s.pos.x, 25 + s.pos.y);
    glEnd();

    glLineWidth(8);//left leg
    glColor3ub(7, 3, 28);
    glBegin(GL_LINES);
    glVertex2f(-5 + s.pos.x, -10 + s.pos.y);
    glVertex2f(-25 + s.pos.x, -47 + s.pos.y);
    glEnd();
    glLineWidth(8);//right leg
    glColor3ub(7, 3, 28);
    glBegin(GL_LINES);
    glVertex2f(5 + s.pos.x, -10 + s.pos.y);
    glVertex2f(25 + s.pos.x, -47 + s.pos.y);
    glEnd();
    glLineWidth(1);//mouth
    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2f(10 + s.pos.x, 45 + s.pos.y);
    glVertex2f(-10 + s.pos.x, 45 + s.pos.y);
    glEnd();

    glBegin(GL_TRIANGLES);//teeth
    glColor3ub(255, 255, 255);
    glVertex2f(10 + s.pos.x, 45 + s.pos.y);
    glVertex2f(4 + s.pos.x, 45 + s.pos.y);
    glVertex2f(7 + s.pos.x, 40 + s.pos.y);
    glEnd();
    glBegin(GL_TRIANGLES);//teeth
    glColor3ub(255, 255, 255);
    glVertex2f(-10 + s.pos.x, 45 + s.pos.y);
    glVertex2f(-04 + s.pos.x, 45 + s.pos.y);
    glVertex2f(-06 + s.pos.x, 40 + s.pos.y);
    glEnd();

}
void bugs(bug_t b)
{

    glColor3f(0, 0, 0);
    circle(b.pos.x, b.pos.y, 10);
    glColor3f(1, 1, 1);
    circle(b.pos.x-4, b.pos.y+3, 2);
    glColor3f(1, 1, 1);
    circle(b.pos.x, b.pos.y +3, 2);
    glColor3f(0, 0, 0);
    circle(b.pos.x + 10, b.pos.y, 8);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(b.pos.x +5, b.pos.y + 5);
    glVertex2f(b.pos.x +5, b.pos.y +5);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(b.pos.x -2, b.pos.y-5);
    glVertex2f(b.pos.x -5, b.pos.y -5);
    glEnd();
    glBegin(GL_LINES);//wing1
    glColor3f(0, 0, 0);
    glVertex2f(b.pos.x + 8, b.pos.y + 8);
    glVertex2f(b.pos.x + 15, b.pos.y + 15);
    glEnd();
    glBegin(GL_LINES);//wing2
    glColor3f(0, 0, 0);
    glVertex2f(b.pos.x +2, b.pos.y + 2);
    glVertex2f(b.pos.x +8, b.pos.y + 15);
    glEnd();

}
void display() {
    //
    // clear window to black
    //
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    background();
    bat();
    bugs(b);
    if (gameover)
    {
        glColor3ub(0, 0, 0);
        vprint(-100, 0, GLUT_BITMAP_8_BY_13, "THE BAT WANTS MORE BLOOD !! ");
    }

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

    if (key == ' ')
        if (space == 0)
            space = 1;
        else
            space = 0;

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
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
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

    b.pos.x = x - winWidth / 2;
    b.pos.y = winHeight / 2 - y;

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    // Write your codes here.
    if (mouse == INSIDE)
        s.vel = mulV(ENEMY_SPEED, unitV(subV(b.pos, s.pos)));
    if (!space)
        s.pos = addV(s.pos,s.vel);

    if (s.pos.x > 500 || s.pos.x < -500)
        s.vel.x = s.vel.x * (-1);

    if (s.pos.y > 200 || s.pos.y < -250)
        s.vel.y = s.vel.y * (-1);

    if ((int)s.pos.x == (int)b.pos.x && (int)s.pos.y == (int)b.pos.y)
    {
        redeye = true;
    }
   

    if ((int)s.pos.x != (int)b.pos.x && (int)s.pos.y != (int)b.pos.y)
    {
        count++;
    }
    else
        count = 0;

    if ((int)s.pos.x == (int)b.pos.x && (int)s.pos.y == (int)b.pos.y)
    {
        gameover = true;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()


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
    glutCreateWindow("CTIS164-HOMEWORK3");

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
