#include <Windows.h>
#include <GL/freeglut.h>
#include "Point.h"
#include "Cuboid.h"

using namespace std;

struct color3f
{
	float r, g, b;
	color3f() { r = 0; g = 0; b = 0; }
	color3f(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
};

//definition of all functions

void display();
void reshape(int w, int h);
void init();
void timer(int value);
void idle();


Cuboid buildingStructure(Point(0, 0, 0), 50, 300, 630);
// Global variables
Point center = Point(0, -3, 0);
Texture texture;
Texture up, left, Right, down, front, back;
int g_iWidth = 800;
int g_iHeight = 600;
const float g_fNear = 1;
const float g_fFar = 1000000000.0f;
color3f g_background;
GLuint displayListID;


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(g_iHeight, g_iWidth);
	glutCreateWindow("weee");
	glutFullScreen();
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);


	glutTimerFunc(1, timer, 0);
	glutMainLoop();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(g_background.r, g_background.g, g_background.b, 1.0);
	glLoadIdentity();
	glTranslatef(0, 0, -10);

	//setupLighting();
	//setupShadow();
	glCallList(displayListID);

	glutSwapBuffers();
}


void idle()
{
	display();
}

void timer(int value)
{
	glutTimerFunc(1000 / 30, timer, 0);	//call the timer again each 1 millisecond

}
//initialize some variables
void init()
{
	g_background.r = 255;
	g_background.g = 255;
	g_background.b = 255;

	//load textures here

	//display list
	displayListID = glGenLists(1);
	glNewList(displayListID, GL_COMPILE);
	//glColor3ub(80, 80, 80);
	buildingStructure.draw();
	glEndList();



}

// function to call when the window is resized
void reshape(int w, int h)
{
	g_iHeight = h;
	g_iWidth = w;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.f, (float)w / (float)h, g_fNear, g_fFar);
	glMatrixMode(GL_MODELVIEW);
}