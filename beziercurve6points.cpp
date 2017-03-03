//
//  main.cpp
//  lab06
//
//  Created by pooja goyal on 3/3/17.
//  Copyright © 2017 pooja goyal. All rights reserved.
//

#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

/* GLUT function Headers */
void mouse(int, int, int,int);
void DrawPoints();

bool WireFrame= false;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


/* GLUT callback Handlers */

float xp[6]= {0.0,0.0,0.0,0.0,0.0,0.0};
float yp[6] ={1.0,1.0,1.0,1.0,1.0,1.0};
float Wwidth, Wheight;
float mx, my;
float t;
int counter = 0;
float xpos,ypos;

static void resize(int width, int height){
    Wwidth = (float)width; // Global float Wwidth
    Wheight = (float)height; // Global float Wheight
    double Ratio = Wwidth/Wheight;
    glViewport(0,0,(GLsizei) width,(GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (45.0f,Ratio,0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(0,5,10,0.0,0.0,0.0,0.0,1.0,0.0);
    
    if(WireFrame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Draw Our Mesh In Wireframe Mesh
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME
    
    // your code here
    
    glPushMatrix();
    DrawPoints();
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1, 0, 1);
    glTranslated(xpos,ypos, -0.5);
    glutSolidSphere(0.3,20,20);
    
    glPopMatrix();
    
    
    glPushMatrix();
    
    glBegin(GL_POINTS);
    glPointSize(8);

    
    for(float a=0; a<=1; a+=0.0005)
    {

glVertex3f(
(1-a)*(1-a)*(1-a)*(1-a)*(1-a)*xp[0]+
           5*(1-a)*(1-a)*(1-a)*(1-a)*a*xp[1]+
           10*(1-a)*(1-a)*(1-a)*a*a*xp[2]+
           10*a*a*a*(1-a)*(1-a)*xp[3] +
           5*a*a*a*a*(1-a)*xp[4]+
           a*a*a*a*a*xp[5],
        (1-a)*(1-a)*(1-a)*(1-a)*(1-a)*yp[0] + 5*(1-a)*(1-a)*(1-a)*(1-a)*a*yp[1] + 10*(1-a)*(1-a)*(1-a)*a*a*yp[2] + 10*a*a*a*(1-a)*(1-a)*yp[3]+5*a*a*a*a*(1-a)*yp[4]+a*a*a*a*a*yp[5],
           -0.5);
        
        }
    
    
        
        glEnd();
    
    
    glPopMatrix();
   
    
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
            
        case 'w':
            WireFrame =!WireFrame;
            break;
    }
}

void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            break;
    }
    glutPostRedisplay();
}

static void idle(void)
{   t+=0.02;
    if(t<=1)
    {
        xpos = (1-t)*(1-t)*(1-t)*(1-t)*(1-t)*xp[0]+5*(1-t)*(1-t)*(1-t)*(1-t)*t*xp[1]+10*(1-t)*(1-t)*(1-t)*t*t*xp[2]+10*t*t*t*(1-t)*(1-t)*xp[3] + 5*t*t*t*t*(1-t)*xp[4]+  t*t*t*t*t*xp[5];
        ypos =(1-t)*(1-t)*(1-t)*(1-t)*(1-t)*yp[0]+5*(1-t)*(1-t)*(1-t)*(1-t)*t*yp[1]+10*(1-t)*(1-t)*(1-t)*t*t*yp[2]+10*t*t*t*(1-t)*(1-t)*yp[3] + 5*t*t*t*t*(1-t)*yp[4]+  t*t*t*t*t*yp[5];

    }
glutPostRedisplay();
}

static void init(void)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    
    glClearColor(0.0, 1.0, 20.0, 0.0);
}


void DrawPoints(){
    glPointSize(8);
    glColor3f(1.0, 1.0, 0.0);
    
    glBegin(GL_POINTS);
    glVertex3f(xp[0], yp[0], -0.5);
    glVertex3f(xp[1], yp[1], -0.5);
    glVertex3f(xp[2], yp[2], -0.5);
     glVertex3f(xp[3], yp[3], -0.5);
    glVertex3f(xp[4], yp[4], -0.5);
    glVertex3f(xp[5], yp[5], -0.5);
    
    glEnd();
    
}

void mouse(int btn, int state, int x, int y){
    // Create scaler value to help tranlate mouse coordiantes to OpenGL coordinates
    float scaler = (Wwidth / Wheight) * 100;
    
    // Calculate correct mouse positions based on windows size and scaler values.
    mx = (float)(x-(Wwidth/2))/scaler;
    my = (float)((Wheight/2)-y)/scaler;
    
    switch(btn){
        case GLUT_LEFT_BUTTON: // Creates event on left mouse click
    if (state == GLUT_DOWN){
                counter++;
                counter = counter %6;
                xp[counter] = mx;
                yp[counter] = my;
                t = 0;
                break;
            }
    }
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    
    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutCreateWindow("GLUT Shapes");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMouseFunc(mouse);
    glutSpecialFunc(Specialkeys);
    
    glutIdleFunc(idle);
    glutMainLoop();
    
    return EXIT_SUCCESS;
}
