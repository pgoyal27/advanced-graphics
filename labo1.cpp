// NAME - POOJA GOYAL
//STUDENT ID - 109896598
//CLASS - CSCI173
//mouse click movement of sphere.
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

bool WireFrame= false;
float t,xp,yp,xpos,ypos,mx,my,x,y;
float Wwidth, Wheight;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


/* GLUT callback Handlers */

static void resize(int width, int height)
{
    Wwidth = (float)width; // Global float Wwidth
    Wheight = (float)height; // Global float Wheight
    
    
    float Ratio= Wwidth/Wheight;
    
    
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
    
    glTranslated(xpos,ypos,-1);
    glutSolidSphere(0.2,40,40);
    
    glPopMatrix();
    glEnd();
    
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
{
      t+= 0.01;
    xpos =xp+t*(mx-xp);
    
    ypos= yp+t*(my-yp);
    
      glutPostRedisplay();
}

    void mouse(int btn , int state, int x , int y){
        float scaler = (Wwidth/Wheight)*100;
        
        mx = (float)(x-Wwidth/2)/scaler ;
        my = (float)(Wheight/2 -y) /scaler;

    
    switch(btn){
        case GLUT_LEFT_BUTTON:
            
            
            if(state == GLUT_DOWN){
                t=0.0;
                
                 xp = xpos;
                 yp= ypos;
            }
            break;
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
    xpos=ypos=4;
    x=y=0;
    
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
    glutSpecialFunc(Specialkeys);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutMainLoop();
    
    return EXIT_SUCCESS;
}
