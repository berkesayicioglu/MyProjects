/*********
   CTIS164 - Template Source Program
----------
STUDENT : 
SECTION : 
HOMEWORK: 
----------
PROBLEMS: 
----------
ADDITIONAL FEATURES:
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

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  16 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

typedef struct {
    int r, g, b;
} color_t;

typedef struct {
    int x, y;
} points_t;

typedef struct {
    points_t pos;
    int angle;
    bool activated;
} web_t;

typedef struct {
    points_t pos;    
    int angle;     
    float ra
} spider_t;
typedef struct {
    points_t pos;
    int radius;
    int r;
    int g;
    int b;
} bug_t;


typedef struct {
    int   angle;
    float   r;
} line_t;
/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height
float line1, line2;
web_t web = { { 0 + 70 * cos(90), 0 + 70 * sin(0) }, 10, false };
spider_t p = {0,0};
bug_t bug = { {rand() % (700)-400,rand() % (700) - 400},10,rand() % 256, rand() % 256, rand() % 256 };
//
// to draw circle, center at (x,y)
// radius r
//
void circle( int x, int y, int r )
{
#define PI 3.1415
   float angle ;
   glBegin( GL_POLYGON ) ;
   for ( int i = 0 ; i < 100 ; i++ )
   {
      angle = 2*PI*i/100;
      glVertex2f( x+r*cos(angle), y+r*sin(angle)) ;
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
      angle = 2 * PI*i / 100;
      glVertex2f(x + r*cos(angle), y + r*sin(angle));
   }
   glEnd();
}

void print(int x, int y, const char *string, void *font )
{
   int len, i ;

   glRasterPos2f( x, y );
   len = (int) strlen( string );
   for ( i =0; i<len; i++ )
   {
      glutBitmapCharacter( font, string[i]);
   }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void *font, const char *string , ...)
{
   va_list ap;
   va_start ( ap, string );
   char str[1024] ;
   vsprintf_s( str, string, ap ) ;
   va_end(ap) ;
   
   int len, i ;
   glRasterPos2f( x, y );
   len = (int) strlen( str );
   for ( i =0; i<len; i++ )
   {
      glutBitmapCharacter( font, str[i]);
   }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char *string, ...) {
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
      for (i = 0; i<len; i++)
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
    glColor3ub(0, 0, 255);
    glVertex2f(-500, -400);
    glVertex2f(500, -400);
    glColor3f(0, 0, 0);
    glVertex2f(500, 500);
    glVertex2f(-500, 500);
    glEnd();

    glColor3f(0, 0, 0);  // line color
    glLineWidth(3);   // line thickness
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(3, 0xf0f0);
    
    glEnd();
    glLineWidth(0.5);   // line thickness
    glDisable(GL_LINE_STIPPLE);

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    // x axis
    glVertex2f(-800, 0);
    glVertex2f(800, 0);

    // y axis
    glVertex2f(0, -500);
    glVertex2f(0, 500);
    glEnd();

    glColor3f(1, 1, 1);
    vprint(300, 350, GLUT_BITMAP_9_BY_15, "Berke Sayicioglu");
    vprint(370, 330, GLUT_BITMAP_9_BY_15, "22101821");
}

void line()
{
    line1 = 75*cos(lineangle * D2R);
    line2 = 75*sin(lineangle * D2R);
    
    glColor3f(1, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2d(0, 0);
    glVertex2d(line1,line2+15);
    glEnd();

}
void spider()
{
    
    glColor3ub(0, 0,0);//body
    circle(0 , 15 , 22);
    glColor3ub(0, 0, 0);
    circle(0, -10, 10);
    glColor3ub(245, 0, 0);//eyes
    circle(-5, -10, 2);
    glColor3ub(245, 0, 0);
    circle(5,-10, 2);
    int i = -1;
    for (int k = 0; k < 2; k++)
    {
        glLineWidth(4);//leg
        glColor3ub(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(3*i, 15);
        glVertex2f(-40*i, 57);
        glEnd();
        glLineWidth(4);
        glColor3ub(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(-15*i, 90);
        glVertex2f(-40*i, 57);
        glEnd();
        if (i == -1)
            i = 1;
        else i = -1;
    }
    
    for (int k = 0; k < 2; k++)
    {
        glLineWidth(2);// leg
        glColor3ub(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(3 * i, 15);
        glVertex2f(-45 * i, 15);
        glEnd();
        glLineWidth(4);
        glColor3ub(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(-60* i, 45);
        glVertex2f(-45 * i, 15);
        glEnd();
        if (i == -1)
            i = 1;
        else i = -1;
    }
    for (int k = 0; k < 2; k++)
    {
        glLineWidth(4);//leg
        glColor3ub(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(3 * i, -15+30);
        glVertex2f(-40 * i, -57+30);
        glEnd();
        glLineWidth(4);
        glColor3ub(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(-15 * i, -90+30);
        glVertex2f(-40 * i, -57+30);
        glEnd();
        if (i == -1)
            i = 1;
        else i = -1;
    }

    glColor3f(1, 1, 1);
    vprint(p.pos.x-10, p.pos.y +7, GLUT_BITMAP_8_BY_13, "%d",lineangle);
}
void drawFire(web_t w)
{
 
        if (w.activated)
        {
            glColor3f(1, 1, 1);
            circle(w.pos.x, w.pos.y, 6);
        }
 
}
void bugs(bug_t t)
{
   
    glColor3f(0, 0, 0);
    circle( t.pos.x+ 100,t.pos.y+ 100, 10);
    glColor3f(1, 1, 1);
    circle(t.pos.x + 96, t.pos.y + 103, 2);
    glColor3f(1, 1, 1);
    circle(t.pos.x + 100, t.pos.y + 103, 2);
    glColor3f(0, 0, 0);
    circle(t.pos.x + 110,t.pos.y + 100, 8);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(t.pos.x + 105, t.pos.y + 105);
    glVertex2f(t.pos.x + 105, t.pos.y + 105);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(1, 1, 1);
        glVertex2f(t.pos.x + 98, t.pos.y + 95);
        glVertex2f(t.pos.x + 95, t.pos.y + 95);
        glEnd();
        glBegin(GL_LINES);//wing1
        glColor3f(0, 0, 0);
        glVertex2f(t.pos.x + 108, t.pos.y + 108);
        glVertex2f(t.pos.x + 115, t.pos.y + 115);
        glEnd();
        glBegin(GL_LINES);//wing2
        glColor3f(0, 0, 0);
        glVertex2f(t.pos.x + 102, t.pos.y + 102);
        glVertex2f(t.pos.x + 108, t.pos.y + 115);
        glEnd();

}

void display() {
   //
   // clear window to black
   //
   glClearColor(0, 0, 0, 0);
   glClear(GL_COLOR_BUFFER_BIT);
  
   background();
   spider();
   line();
   drawFire(web);
   bugs(bug);
   glutSwapBuffers();
   
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y )
{
   // exit when ESC is pressed.
   if ( key == 27 )
      exit(0);
    
   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}

void onKeyUp(unsigned char key, int x, int y )
{
   // exit when ESC is pressed.
   if ( key == 27 )
      exit(0);
    
   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown( int key, int x, int y )
{
   // Write your codes here.
   switch (key) {
   case GLUT_KEY_UP: up = true; break;
   case GLUT_KEY_DOWN: down = true; break;
   case GLUT_KEY_LEFT: left = true; break;
   case GLUT_KEY_RIGHT: right = true; break;
   }

   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp( int key, int x, int y )
{
   // Write your codes here.
   switch (key) {
   case GLUT_KEY_UP: up = false; break;
   case GLUT_KEY_DOWN: down = false; break;
   case GLUT_KEY_LEFT: left = false; break;
   case GLUT_KEY_RIGHT: right = false; break;
   }

   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick( int button, int stat, int x, int y )
{
   // Write your codes here.


   
   // to refresh the window it calls display() function
   glutPostRedisplay() ; 
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize( int w, int h )
{
   winWidth = w;
   winHeight = h;
   glViewport( 0, 0, w, h ) ;
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho( -w/2, w/2, -h/2, h/2, -1, 1);
   glMatrixMode( GL_MODELVIEW);
   glLoadIdentity();
   display(); // refresh window.
}

void onMoveDown( int x, int y ) {
   // Write your codes here.


   
   // to refresh the window it calls display() function   
   glutPostRedisplay() ;
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove( int x, int y ) {
   // Write your codes here.


   
   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}
bool testCollision(web_t t, bug_t bug) {
    float dx = bug.pos.x - t.pos.x;
    float dy = bug.pos.y - t.pos.y;
    float d = sqrt(dx * dx + dy * dy);
    return d<=bug.radius;
}

void resetTarget() {
    int yPos = rand() % 2 ? 225 : -225;
    bug.pos = { -500, yPos};
    bug.r = rand() % 256;
    bug.g = rand() % 256;
    bug.b = rand() % 256;
   
}

#if TIMER_ON == 1
void onTimer( int v ) {
    
   glutTimerFunc( TIMER_PERIOD, onTimer, 0 ) ;
   // Write your codes here.
   int anglet = atan2(bug.pos.y,bug.pos.x) / D2R;
   if (anglet < 0)
       anglet += 360;
   if (abs(anglet - p.angle) < 180)
   {
       if (anglet < p.angle)
           p.angle--;
       else if (anglet > p.angle)
           (p.angle++) % 360;
   }
   else if (abs(anglet - p.angle) > 180)
   {
       if (anglet < p.angle)
           p.angle = (p.angle++) % 360;
       else if (anglet > p.angle)
           p.angle = 360 + (p.angle--);
   }
   if (anglet == lineangle)
   {
       if (web.activated = true) 
       {
           web.pos.x += 10 * cos(lineangle * D2R);
           web.pos.y += 10 * sin(lineangle * D2R);

           if (web.pos.x > 500 || web.pos.x < -500 || web.pos.y>400 || web.pos.y < -400) {
               web.activated = false;
           }
           if (testCollision(web, bug))
           {
               web.activated = false;
               resetTarget();
           }
       }
   }
   lineangle++;
   if (lineangle > 360)
   {
       lineangle-=360;
   }
   
   // to refresh the window it calls display() function
   glutPostRedisplay() ; // display()

}
#endif

void Init() {
   
   // Smoothing shapes
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
}

void main( int argc, char *argv[] ) {
   glutInit(&argc, argv );
   glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
   glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
   //glutInitWindowPosition(100, 100);
   glutCreateWindow("CTIS164-HOMEWORK2");

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
   glutTimerFunc( TIMER_PERIOD, onTimer, 0 ) ;
   #endif

   Init();
   
   glutMainLoop();
}
