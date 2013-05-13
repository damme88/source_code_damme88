
/******************************************************************************
* App Name  : Robo_Handle.
* Language  : OpenGL on Visual C++ Console 2010.
* Writer    : Damme88 Phamtoanbonmat@gmail.com.
* Role      : Electronic Communication Engineering And Graphics C++ Dev.
* Time      : 23h 27 phut 13/05/2013.
* Resource  : Google.com.vn - OpenGL Red Book.
******************************************************************************/

#include "stdafx.h"

static int shoulder = 0;
static int elbow = 0;
static bool is_color = false;

void init () {
  glClearColor (0.0, 0.0, 0.0, 0.0);  // Set back ground color
  glShadeModel (GL_SMOOTH);           // view with smooth style
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();                // save current pos to stack
  glTranslatef(-1.0, 0.0, 0.0); // move coordinate
  glRotatef((GLfloat) shoulder, 0.0, 0.0, 1.0); 
  glTranslatef (1.0, 0.0, 0.0);
  glPushMatrix();
  glScalef(2.0, 0.4, 1.0);
  if (is_color == true) {
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
  } else {
    glColor3f(1.0, 1.0, 1.0);
    glutWireCube (1.0);
  }
  glPopMatrix();

  glTranslatef (1.0, 0.0, 0.0);
  glRotatef((GLfloat) elbow, 0.0, 0.0, 1.0);
  glTranslatef(1.0, 0.0, 0.0);
  glPushMatrix();
  glScalef(2.0, 0.4, 1.0);
  if(is_color) {
    glColor3f(0.0, 1.0, 0.0);
    glutSolidCube(1.0);
  } else {
    glColor3f(1.0, 1.0, 1.0);
    glutWireCube(1.0);
  }
  glPopMatrix();

  glPopMatrix();
  glutSwapBuffers();
}

void reshape(int w, int h) {
  glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef (0.0, 0.0, -5.0);
}

void keyboard (unsigned char key, int x, int y) {
  switch (key) {
    case 'a':   /*  s key rotates at shoulder  */
      shoulder = (shoulder + 5) % 360;
      glutPostRedisplay();
      break;
    case 's':
      shoulder = (shoulder - 5) % 360;
      glutPostRedisplay();
      break;
    case 'd':  /*  e key rotates at elbow  */
      elbow = (elbow + 5) % 360;
      glutPostRedisplay();
      break;
    case 'f':
      elbow = (elbow - 5) % 360;
      glutPostRedisplay();
      break;
    case 'c':
      is_color = true;
      glutPostRedisplay();
      break;
    case 'x':
      is_color = false;
      glutPostRedisplay();
      break;
    default:
        break;
  }
}

void main () {
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (1000, 1000); 
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("Opengl_Console");
  printf("use key : a s d f to rotatef");
  printf("\nuse key c and x to make and clear color");
  init();
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return ;
}

