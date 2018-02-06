
#ifdef __WIN32
#include <windows.h>
#include <GL/glut.h>
#elif __APPLE__
// Compile on OSX with clang
//   $ clang main.cpp -framework OpenGL -framework GLUT -Wno-deprecated-declarations -o demo
#include <GLUT/glut.h>

#elif __LINUX__
// Untested
#include <GLUT/glut.h>
#endif


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>


// Based on the code from programming-technique.blogspot.com

using namespace std;

bool redFirst;
bool rotateFirst;
float t = 0.0f;
float dt = 0.001f;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
  switch (key) {
    case 'r': // use 'r' to control order of the rectangles to be drawn in drawSceneAlpha()
      redFirst = !redFirst;
      glutPostRedisplay();
      break;
    case 't': // use 't' to control order of the transformations in drawTriangleWhite()
      rotateFirst = !rotateFirst;
      glutPostRedisplay();
      break;
    case 27: //Escape key
      exit(0);
  }
}

//Initializes 3D rendering
void initRendering() {
  redFirst = true;
  rotateFirst = true;
  // //Makes 3D drawing work when something is in front of something else
  glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
  //Tell OpenGL how to convert from coordinates to pixel values
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
  //Set the camera perspective
  glLoadIdentity(); //Reset the camera
  gluPerspective(45.0,                  //The field of view angle, in degrees, in the y direction
                 (double) w / (double) h, //The width-to-height ratio
                 1.0,                   //The near z clipping coordinate
                 200.0);                //The far z clipping coordinate
}


//Draws the 3D scene
void drawCube() {
  //Clear information from last draw
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
  glLoadIdentity(); //Reset the drawing perspective

  glTranslatef(1.5f, 0.0f, -7.0f);
  glScalef(0.5f, 0.5f, 0.5f);

  glPushMatrix();
  glTranslatef(sin(t), 0, 0);
  glRotatef(t * 1000, 0, 1, 1);

  glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
  // Top face (y = 1.0f)
  // Define vertices in counter-clockwise (CCW) order with normal pointing out
  glColor3f(0.0f, 1.0f, 0.0f);     // Green
  glVertex3f(1.0f, 1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);

  // Bottom face (y = -1.0f)
  glColor3f(1.0f, 0.5f, 0.0f);     // Orange
  glVertex3f(1.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);

  // Front face  (z = 1.0f)
  glColor3f(1.0f, 0.0f, 0.0f);     // Red
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);

  // Back face (z = -1.0f)
  glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
  glVertex3f(1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);

  // Left face (x = -1.0f)
  glColor3f(0.0f, 0.0f, 1.0f);     // Blue
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);

  // Right face (x = 1.0f)
  glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
  glVertex3f(1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glEnd();  // End of drawing color-cube
  glPopMatrix();

  glutSwapBuffers(); //Send the 3D scene to the screen

  t += dt; // Move the time forward
  glutPostRedisplay(); // Invoke drawing another frame
}

void drawTriangleWhite() {
  //Clear information from last draw
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity(); //Reset the drawing perspective
  glPushMatrix();
  glScalef(0.08, 0.1, 0.1);

  if (rotateFirst) {
    glRotatef(90, 0, 0, 1);
    glTranslatef(-2, -2, 0);
  } else {
    glTranslatef(-2, -2, 0);
    glRotatef(90, 0, 0, 1);
  }


  glBegin(GL_TRIANGLES);
  glVertex2f(-2.0, -1.0);
  glVertex2f(1.0, -1.0);
  glVertex2f(0.0, 2.0);

  glVertex2f(4.0, -4.0);
  glVertex2f(4.0, 5.0);
  glVertex2f(3.0, 5.0);
  glEnd();

  glPopMatrix();
  glutSwapBuffers(); //Send the 3D scene to the screen
}

void drawDotsLines() {
  //Clear information from last draw
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); //Reset the drawing perspective

  glPushMatrix();
  glScalef(0.1, 0.1, 0.1);

  glBegin(GL_POINTS);
  glVertex2f(-3, 2);
  glVertex2f(2, 1);
  glEnd();

  glLineWidth(2.0); // Specify line width
  glBegin(GL_LINES); // Draw line
  glVertex2f(-5, 7);
  glVertex2f(5, -7);
  glEnd();

  glPopMatrix();
  glutSwapBuffers(); //Send the 3D scene to the screen
}

void drawTriangleColored() {
  //Clear information from last draw
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); //Reset the drawing perspective

  glPushMatrix();
  glScalef(0.1, 0.1, 0.1);

  glBegin(GL_TRIANGLES);
  glColor3f(1.0, 0, 0); // specify color for one vertex
  glVertex2f(-2.0, -1.0);

  glColor3f(0, 1.0, 0);
  glVertex2f(1.0, -1.0);

  glColor3f(0, 0.0, 1.0);
  glVertex2f(0.0, 2.0);
  glEnd();

  glPopMatrix();

  glutSwapBuffers(); //Send the 3D scene to the screen
}

void drawGreenSquare() {
  glColor4f(0.5, 1, 0.5, 0.5); // alpha!!!
  glPushMatrix();
  glScalef(0.25, 0.25, 0.25);
  glTranslatef(-0.25, 0.25, 0);

  glBegin(GL_QUADS);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
  glEnd();

  glPopMatrix();
}

void drawRedSquare() {
  glColor4f(1, 0.5, 0.5, 0.5); // alpha!!!

  glPushMatrix();
  glScalef(0.25, 0.25, 0.25);
  glTranslatef(0.25, -0.25, 0);

  glBegin(GL_QUADS);
  glVertex2f(-1, -1);
  glVertex2f(1, -1);
  glVertex2f(1, 1);
  glVertex2f(-1, 1);
  glEnd();

  glPopMatrix();
}

void drawSceneAlpha() {
  //Clear information from last draw
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
  glLoadIdentity(); //Reset the drawing perspective

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // many possible blend modes here!

  if (redFirst) {
    drawRedSquare();
    glTranslatef(0, 0, -0.01);
    drawGreenSquare();
  } else {
    drawGreenSquare();
    glTranslatef(0, 0, -0.01);
    drawRedSquare();
  }

  glDisable(GL_BLEND);

  glutSwapBuffers();
}

int main(int argc, char **argv) {
  //Initialize GLUT
  glutInit(&argc, argv);

  // TOGGLE ME!
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);


  //Create the window
  glutInitWindowSize(1280, 800); //Set the window size
  glutCreateWindow("15-462 OpenGL Tutorial");
  initRendering(); //Initialize rendering

  // Main draw routine(s)
//  glutDisplayFunc(drawTriangleWhite);
//    glutDisplayFunc(drawDotsLines);

//  glutDisplayFunc(drawTriangleColored);
    glutDisplayFunc(drawCube);
//	 glutDisplayFunc(drawSceneAlpha);

  //Set handler functions for keypresses, and window resizes
  glutKeyboardFunc(handleKeypress);
  glutReshapeFunc(handleResize);
  glutMainLoop(); //Start the main loop

  return 0;
}
