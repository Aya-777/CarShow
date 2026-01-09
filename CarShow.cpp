#include <Windows.h>
#include <GL/freeglut.h>
#include "Point.h"

using namespace std;

struct color3f
{
	float r, g, b;
	color3f() { r = 0; g = 0; b = 0; }
	color3f(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
};

void display();
void idle();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Idk");
	glutFullScreen();
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutMainLoop();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glutSwapBuffers();
}

void idle()
{
	display();
}
