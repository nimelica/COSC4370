/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <GL/glut.h>

#include "./freeglut-3.2.1/include/GL/freeglut.h"

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0,1,4,1}; 
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 4; // TODO: change this number to try different examples.

float specular[] = {1.0, 1.0, 1.0, 1.0};
float shininess[] = {50.0};

/***********************************************************************************/

/*PROBLEM #1: Utah Teopot Cycle*/
void problem1(){
  float radius{.0f};  //start from radius 0...
  float full_degree{360};  //...end when radius 360 (cycle)
  float teapot_size{.3f}; //size of the every single teapot 

  //create a new teapot while the camera angle access 360 degree
  while(radius != full_degree){ 
    glPushMatrix(); //duplicate/push matrix
    glTranslatef(0, 0, 0); //move along x=0, y=0, z=0 axis
    glRotatef(radius, 0, 0, 1); //rotate radius on z axis
    glTranslatef(1, 0, 0); //along with x-axis
    glutSolidTeapot(teapot_size); //create/draw teapot with a size of 0.3
    glPopMatrix();
    radius += 36; //provides 10 teapots
   }
}

/*PROBLEM #2: The Cube Ladder/Stairs*/
void problem2(){
  unsigned int max_stair{16}; //we want 15 stair (cube)
  unsigned int curr_num{1}; //start from one stair cube
  float xdir{-7}; //x-direction/position
  float ydir{0};  //y-direction/position
  float stair_size{1}; //size of each stair level/cube
  float increment_height{.26f}; //the next stair will be above from the previous as 0.25

  // while num of cube/stair will be 15 (not 16)
  while(curr_num < max_stair){
    glPushMatrix();
    glTranslatef(xdir, ydir, 0); //move along x and y direction
    glScalef(1, curr_num*.5, 1); //1 x, currnum*1/2 y (increase height), 1 is z axis
    glutSolidCube(stair_size); 
    glPopMatrix();

   ++xdir, ydir += increment_height; //increase heigt along with the y-axis
    ++curr_num;
  }
}

/*PROBLEM #3: Utah Teopot Pyramid*/
void problem3(){
  int pyramid_level{6}; //# of level/row in the pyramid
  int level{1};
  float teapot_size{0.25};
  for(; level <= pyramid_level; ++level){
    float ratio{}; //to balance
    if(level % 2 == 0){
      ratio = -0.5f * level + 0.5f;
    }else{
      ratio = -level/2;
    }
    // Draw new teapots with .6f distance between
   for(int teapot = 1; teapot <= level; ++teapot){
      glPushMatrix();
      //pyramid_level/2 -> to put the camera at the center of the pyramid
      //-level because otherwise the picramid will going to upside down
      glTranslatef(ratio, (pyramid_level/2 - level) * .60f, 0);
      glutSolidTeapot(teapot_size); //create teapot with determined size

      ++ratio;
      glPopMatrix();
      }
    }
}

/*SOURCE for this particular problem solution:*/
/*https://github.com/RockefellerA/RobotArm*/
/*http://inf.ufes.br/~thomas/graphics/OpenGL/robot/robot_opengl.html*/
/*PROBLEM #4: High Five Hand Gesture*/
void problem4(){
   float r{0.5f};
   float g{0.35f};
   float b{0.05f};
   glClear (GL_DEPTH_BUFFER_BIT);
   glDisable(GL_LIGHTING);
   glColor3f(r, g, b);
   
   static float hand_body = 90, tumb_fngr = 35, point_fngr = 10, middle_fngr = 10, ring_fngr = 35, tiny_fngr = 35;
   static float tumb_up = 30, point_up = 15, middle_up = 10, ring_up = 35, tiny_up = 35;

  //Hand
   glTranslatef (0.0, 0.0, 0.0);
   glRotatef ((GLfloat) hand_body, 0.0, 0.0, 5.0);
   glTranslatef (0.20, 0.5, 0.5); 
   glPushMatrix();
   glColor3f(r, g, b);
   glScalef (0.5, 0.1, 1.0);
   glutSolidCube (1.0);
   glPopMatrix();
   
   //Bottom Joint of Thumb finger
   glPushMatrix();
   glTranslatef (0.0, 0.125, -0.1);
   glRotatef ((GLfloat) tumb_fngr, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.0, 0.8);
   glPushMatrix();
   glColor3f(r, g, b);
   glScalef (0.5, 0.2, 0.2);
   glutSolidCube (0.7);
   glPopMatrix();

   //Upper Joint of Thumb finger
   glTranslatef (0.15, 0.0, -0.8);
   glRotatef ((GLfloat) tumb_up, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.0, 0.8);
   glPushMatrix();
   glColor3f(r, g, b);
   glScalef (0.5, 0.2, 0.2);
   glutSolidCube (0.7);
   glPopMatrix();
   glPopMatrix();
   
   //Bottom Joint Pointer Finger
   glPushMatrix();
   glTranslatef (0.5, 0.1, 0.0);
   glRotatef ((GLfloat) point_fngr, 0.0, 0.0, 1.0);
   glTranslatef (0.0, 0.0, 0.4);
   glPushMatrix();
   glColor3f(r, g, b);
   glScalef (0.6, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();

   //Upper Joint of Pointer finger
   glTranslatef (0.5, 0.0, 0.0);
   glRotatef ((GLfloat) point_up, 0.0, 0.0, 1.0);
   glTranslatef (0.0, 0.0, 0.0);
   glPushMatrix();
   glColor3f(r, g, b);
   glScalef (0.6, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();       
   glPopMatrix();
 
   //Upper Joint of Middle Finger
   glPushMatrix();
   glTranslatef (0.5, 0.10, 0.0);
   glRotatef ((GLfloat) middle_fngr, 0.0, 0.0, 1.0);
   glTranslatef (0.0, 0.0, 0.0);
   glPushMatrix();
   glColor3f(r, g, b);
   glScalef (0.6, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();

   //Bottom Joint of Middle Finger
   glTranslatef (0.5, 0.0, 0.0);
   glRotatef ((GLfloat) middle_up, 0.0, 0.0, 1.0);
   glTranslatef (0.0, 0.0, 0.0);
   glPushMatrix();
   glColor3f(r, g, b);
   glScalef (0.6, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();
   glPopMatrix();
   
   //Upper Joint of Ring Finger
   glPushMatrix();
   glTranslatef (0.5, 0.1, 0.0);
   glRotatef ((GLfloat) ring_fngr, 0.0, 0.0, 1.0);
   glTranslatef (0.0, 0.0, -0.4);
   glPushMatrix();
   glColor3f(r, g, b);
   glScalef (0.6, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();

  //Bottom Joint of Ring Finger
   glTranslatef (0.5, 0.1, 0.0);
   glRotatef ((GLfloat) ring_up, 0.0, 0.0, 1.0);
   glTranslatef (0.0, -0.1,  0.0);
   glPushMatrix();
   glColor3f(r, g, b);
   glScalef (0.6, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();
   glPopMatrix();
   
   //Bottom Joint Pinky Finger
   glPushMatrix();
   glTranslatef (0.2, 0.1, 0.0);
   glRotatef ((GLfloat) tiny_fngr, 0.0, 0.0, 1.0);
   glTranslatef (0.0, 0.0, -0.6);
   glPushMatrix();
   glColor3f(r, g, b);
   glScalef (0.5, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();

   //Upper Joint of Pinky Finger
   glTranslatef (0.4, 0.1, 0.0);
   glRotatef ((GLfloat) tiny_up, 0.0, 0.0, 1.0);
   glTranslatef (0.0, -0.1, 0.0);
   glPushMatrix();
   glColor3f(r, g, b);
   glScalef (0.6, 0.2, 0.2);
   glutSolidCube (0.8);
   glPopMatrix();
   glPopMatrix();

   //End
   glPopMatrix();
   glutSwapBuffers();
}

/**************************************************************************************/

void display() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
	glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis
	glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis
	glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,windowWidth,windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot,0,1,0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0])*.1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1,(y-lastPos[1])*.1);
	}
	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    curProblem = key-'0';
    if (key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
