/******************************************************************************
* Name Application  : TextBind
* Language          : Graphics OpenGL on Visual C++ Console 2010 
* Writer            : Damme88_Phamtoanbonmat@gmail.com
* Role              : Electronic_Communication_And_Graphics_C++_Developer 
* Time              : 22h 53p 28/03/2013
* Run OS            : Windows 7 Ultimate X86
******************************************************************************/
#include "stdafx.h"

// set properties at first time for object 
void init (void) {

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // clear screen
  glShadeModel(GL_SMOOTH);  // set smooth

  // set material ambien style
  GLfloat mat_ambien[] = {0.0f, 1.0f, 1.0f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambien);

  // set material specular style
  GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);

  // set material shininess style
  GLfloat mat_shininess[] = {50.0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

  // set lighting position for object
  GLfloat lighting_position[] = {1.0f, 1.0f, 1.0f, 0.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, lighting_position);

  glEnable(GL_LIGHTING);    // enable lighting 
  glEnable(GL_LIGHT0);      // chose light source is 0 source
  glEnable(GL_DEPTH_TEST);  // enalbe depth
}

// this function will render object 
void display(void) {
  // clear buffer (color buffer and depth buffer)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutSolidSphere(1.0f, 200, 16);  // create a solid sphere with r = 1.0
  glFlush();  // push into buffer
}

// this function will set model view, mode light, mode depth 
void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
         1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
         1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main()
{
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("OpenGL_Lighting");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}

