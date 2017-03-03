
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

float t, xp, yp, xpos, ypos, my_x, my_y;	//time
float Wwidth;	//width of screen
float Wheight;	//height of screen

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
    
    float Ratio = Wwidth/Wheight;
    glViewport(0,0,(GLsizei) width,(GLsizei) height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective (45.0f, Ratio ,0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(0,0,10,0.0,0.0,0.0,0.0,1.0,100.0);
    
    if(WireFrame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Draw Our Mesh In Wireframe Mesh
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME
    
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(xpos, ypos, -1);
    glutSolidSphere(0.2, 40, 40);
    glPopMatrix();
    
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(4.3,4.3,-1);
    glVertex3f(-4.3,4.3,-1);
    glVertex3f(-4.3,-4.3,-1);
    glVertex3f(4.3,-4.3,-1);
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
    }
    glutPostRedisplay();
}

int collision(float xpos, float ypos)
{
    if(xpos<-4.0 || xpos >4.0 )
    {    //if out of bound in the x-axis
        return 1;
    }
    else if(ypos<-4.0 || ypos>4.0)
    {     //if out of bound in the y-axis
        return 2;
    }
    return 0;
}


static void idle(void)
{
    t += 0.01;
    //calculate parametric equation for x and y
    int iscollision = 0;
    xpos = xp + t*(my_x - xp);
    ypos = yp + t*(my_y - yp);
    
    iscollision = collision(xpos, ypos);
    
    if(iscollision == 2){ //outside y
        my_x = -xp + xpos;
        my_y = yp;
        xp = xpos;
        yp = ypos;
        t=0;              //reset because a new line must be followed after collision
    }
    else if(iscollision == 1){ //outside x
        my_x =  xp;
        my_y = -yp + ypos;
        xp = xpos;
        yp = ypos;
        t=0;
    }
    
    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y){
    //convert window screen pixels to viewport coordinates
    float scaler = (Wwidth/Wheight)*100;
    my_x = (float)(x-Wwidth/2)/scaler;
    my_y = (float)(Wheight/2 - y)/scaler;
    
    /*code here*/
    switch(btn){
        case GLUT_LEFT_BUTTON:
            //cout<<my_x<<" "<<my_y<<endl;
            //cout<<"sphere: "<<xp<<" "<<yp<<endl;
            if(state==GLUT_DOWN){
                t = 0.0;    //update t to 0 so can reapply t for new line/movement
                xp = xpos;
                yp = ypos;
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
    t = xp = yp = my_x = my_y =0.0; //initialize global variables
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
    
    
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}
