/*
POOJA GOYAL
109896598
CSCI 173
LAB 02 - CODE FOR USING PARAMETRIC EQUATION
CALCULATE THE PATH OF A BOUNCING
 SPHERE INSIDE THE SKYBOX
*/#include "SOIL.h"
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h> /* printf, scanf, puts, NULL */
#include <time.h>  /* time */
#include <iostream>
#include <math.h>

using namespace std;

bool WireFrame= false;

GLuint tex[6]; // Texture pointer

float RotateX =0;
float RotateY =0;
float RotateZ =0;
float translate_z =-1;
float t, xp, yp, zp,xpos, ypos, my_x, my_y,zpos,my_z;
float Wwidth;
float Wheight;


const GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };



static void resize(int width, int height)
{
   Wwidth = (float)width; // Global float Wwidth
    Wheight = (float)height; // Global float Wheight


   double Ratio = (double)width/(double)height;
    glViewport(0,0,(GLsizei) width,(GLsizei) height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective (45.0f, Ratio ,0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

static
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,0,10,0.0,0.0,0.0,0.0,1.0,100.0);

    if(WireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Draw Our Mesh In Wireframe Mesh
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME

    // your code here

    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();

    glTranslated(0,0,translate_z);
    glRotated(RotateX,1,0,0);
    glRotated(RotateY,0,1,0);
    glRotated(RotateZ,0,0,1);

    //front face
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.3f, -2.3f,  -2.3f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2.3f, -2.3f,  -2.3f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.3f,  2.3f,  -2.3f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.3f,  2.3f,  -2.3f);  // Top Left Of The Texture and Quad

    glEnd();

     // Back Face
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.3f, -2.3f, -2.3f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.3f,  2.3f, -2.3f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.3f,  2.3f, -2.3f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.3f, -2.3f, -2.3f);  // Bottom Left Of The Texture and Quad

    glEnd();


    // Top Face
    glBindTexture(GL_TEXTURE_2D, tex[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.3f,  -2.3f, -2.3f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.3f,  -2.3f,  2.3f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.3f,  -2.3f,  2.3f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.3f,  -2.3f, -2.3f);  // Top Right Of The Texture and Quad

    glEnd();


    // Bottom Face
    glBindTexture(GL_TEXTURE_2D, tex[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.3f, 2.3f, -2.3f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 2.3f, 2.3f, -2.3f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 2.3f, 2.3f,  2.3f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.3f, 2.3f,  2.3f);  // Bottom Right Of The Texture and Quad

    glEnd();

    //RIGHT face
    glBindTexture(GL_TEXTURE_2D, tex[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( -2.3f, -2.3f, -2.3f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( -2.3f,  2.3f, -2.3f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( -2.3f,  2.3f,  2.3f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( -2.3f, -2.3f,  2.3f);  // Bottom Left Of The Texture and Quad
    glEnd();

    // Left Face
    glBindTexture(GL_TEXTURE_2D, tex[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(2.3f, -2.3f, -2.3f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2.3f, -2.3f,  2.3f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(2.3f,  2.3f,  2.3f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(2.3f,  2.3f, -2.3f);  // Top Left Of The Texture and Quad

    glEnd();
    glPopMatrix();
    glPushMatrix();
    glColor3f(0.1,0.1,2.0);
    glTranslated(xpos, ypos, zpos);
    glutSolidSphere(0.3,20,20);
glPopMatrix();


    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {   case 'a':
	  translate_z += (float) 1.0f;
		break;
	  case 'z':
	  translate_z -= (float) 1.0f;
		break;
    }
}

void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_END:
	  translate_z += (float) 1.0f;
		break;
	case GLUT_KEY_HOME:
	  translate_z -= (float) 1.0f;
		break;
    case GLUT_KEY_UP:                       /* Clockwise rotation over X */
	 	RotateX = ((int)RotateX +5)%360;
		break;
	case GLUT_KEY_DOWN:                        /* Counter Clockwise rotation over X */
		RotateX = ((int)RotateX -5)%360;
		  break;
	case GLUT_KEY_LEFT:
    	RotateY =((int)RotateY +5)%360;        /* Clockwise rotation over Y */
		break;
	case GLUT_KEY_RIGHT:
		RotateY = ((int)RotateY -5)%360;        /* Counter Clockwise rotation over Y */
		 break;
		 case GLUT_KEY_PAGE_UP:
    	RotateZ =((int)RotateZ +5)%360;        /* Clockwise rotation over Z */
		break;
	case GLUT_KEY_PAGE_DOWN:
		RotateZ = ((int)RotateZ -5)%360;        /* Counter Clockwise rotation over Z */
		 break;

   }
  glutPostRedisplay();
}

int collision(float xpos, float ypos, float zpos){
    if(xpos<-2|| xpos >2 ){
          return 1;
    }
    else if(ypos<-2|| ypos>2){
        return 2;
    }
        else if(zpos<-2 || zpos>2){
        return 3;
    }
    return 0;
}

static void idle(void)
{

    t += 0.02;

    int iscollision = 0;
    xpos = xp + t*(my_x - xp);
    ypos = yp + t*(my_y - yp);
    zpos = zp + t*(my_z - zp);

    iscollision = collision(xpos, ypos,zpos);



if(iscollision == 3){
    my_x = xp;
        my_y = yp;
        my_z = -my_z;
        xp = xpos;
        yp = ypos;
        zp = zpos;
        t=0;
     }
   else if(iscollision == 2){
        my_x = -xp + xpos;
        my_y = yp;
        my_z = zp;
        xp = xpos;
        yp = ypos;
        zp = zpos;
        t=0;
    }
    else if(iscollision == 1){
        my_x =  xp;
        my_y = -yp + ypos;
        my_z = zp;
        xp = xpos;
        yp = ypos;
        zp = zpos;
        t=0;
    }
    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y){

    float scaler = (Wwidth/Wheight)*100;
    my_x = (float)(x-Wwidth/2)/scaler;
    my_y = (float)(Wheight/2 - y)/scaler;
    my_z = rand() % (-2) + 2;    /* generate random number between -2 and 2 */


    switch(btn){
    case GLUT_LEFT_BUTTON:

        if(state==GLUT_DOWN){
            t = 0.00;
            xp = xpos;
            yp = ypos;
            zp = zpos;
        }
        break;
    }
    glutPostRedisplay();
}

void textureloader(string imagelink, GLuint t){
     glBindTexture(GL_TEXTURE_2D, t);  // images are 2D arrays of pixels, bound to the GL_TEXTURE_2D target.

     int width, height;  // width & height for the image reader
     unsigned char* image;

     image = SOIL_load_image(imagelink.c_str() , &width, &height, 0, SOIL_LOAD_RGB);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    // binding image data
     SOIL_free_image_data(image);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
};

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
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    t = xp = yp = zp= my_x = my_y = my_z=0.0;

    glEnable(GL_TEXTURE_2D);
    glGenTextures(6, tex);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    //texture for front and back faces
    textureloader("/Users/poojagoyal/Desktop/173labs/skybox/images/front.jpg", tex[0]);
    textureloader("/Users/poojagoyal/Desktop/173labs/skybox/images/back.jpg", tex[1]);


    //texture for top and bottom faces
    textureloader("/Users/poojagoyal/Desktop/173labs/skybox/images/top.jpg", tex[2]);
    textureloader("/Users/poojagoyal/Desktop/173labs/skybox/images/bottom.jpg", tex[3]);


    //texture for right and left faces
    textureloader("/Users/poojagoyal/Desktop/173labs/skybox/images/right.jpg", tex[4]);
    textureloader("/Users/poojagoyal/Desktop/173labs/skybox/images/left.jpg", tex[5]);
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
