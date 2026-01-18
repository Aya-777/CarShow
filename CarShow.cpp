#include <Windows.h>
#include <GL/freeglut.h>
#include<vector>
#include "Point.h"
#include "Cuboid.h"
#include "Camera.h"
#include "Truck.h"
#include "Sofa.h"
#include "Window.h"
#include "Building.h"
#include "FamilyCar.h"
#include "Road.h"  //salma
#include "ParkingRoad.h" //salma
#include "Color.h"
#include "Controller.h"

using namespace std;
vector<Door*> globalDoors;

//Global functions
void display();
void updateScene();
void reshape(int w, int h);
void init();
void timer(int value);
void idle();

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
//Cuboid buildingStructure(Point(0, 0, 0), 100, 630, 300);
Truck t(Point(-500, 3.5, 0));
bool isInsideView = false;
Camera camera;
bool g_mouseCaptured = false;
int g_lastMouseX = 0;
int g_lastMouseY = 0;
float g_mouseSensitivity = 0.0025f;
Building buildingStructure;
Road mainRoad(-700.0f, -3.0f, -2000.0f, 200.0f, 4000.0f, 0.0f); //salma
Road sideRoad(-606.0f, -3.0f, 440.0f, 80.0f, 760.0f, 90.0f);    //salma
ParkingRoad parking(0.0f, -3.0f, 360.0f, 80.0f, 155.0f, 90.0f, 2.0f, 40.0f); //salma


void drawGround()
{
	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);
	glVertex3f(-2000.0f, -3.0f, -2000.0f);
	glVertex3f(2000.0f, -3.0f, -2000.0f);
	glVertex3f(2000.0f, -3.0f, 2000.0f);
	glVertex3f(-2000.0f, -3.0f, 2000.0f);
	glEnd();
	glPopMatrix();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(g_iHeight, g_iWidth);
	glutCreateWindow("weee");
	glutFullScreen();
	init();

	Controller::init(camera, t, isInsideView);
	// 2. Register the controller's static methods
	glutKeyboardFunc(Controller::keyboard);
	glutSpecialFunc(Controller::specialKeys);
	glutPassiveMotionFunc(Controller::mouseMove);
	glutMouseFunc(Controller::mouseButton);

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	camera.SetPos(-500.0f, 10.0f, 800.0f);
	camera.RotateYaw(-1.0);
	camera.SetPitch(0);


	glutTimerFunc(1, timer, 0);
	glutMainLoop();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(g_background.r, g_background.g, g_background.b, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera.Refresh();

	//setupLighting();
	//setupShadow();
	drawGround();

	buildingStructure.draw();
	mainRoad.draw(); //salma
	sideRoad.draw(); //salma
	parking.draw(); //salma

	glPushMatrix();
	//glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // اذا كبيتها ببطل راكبها
	glColor3f(0.8, 0.1, 0.1);
	t.draw(0.8, 0.8, 0.7);
	glPopMatrix();
	glCallList(displayListID);

	glutSwapBuffers();
}


void idle()
{
	t.update();
	//t.load();
	updateScene();
	display();
}

void timer(int value)
{
	glutTimerFunc(1000 / 30, timer, 0);	//call the timer again each 1 millisecond

}

//initialize some variables
void init()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	g_background.r = 1.0f;
	g_background.g = 1.0f;
	g_background.b = 1.0f;

	//load textures here

	//display list
	displayListID = glGenLists(1);
	glNewList(displayListID, GL_COMPILE);
	//glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
	glColor3f(0.2f, 0.3f, 0.8f);
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

void updateScene() {
	t.update();

	if (isInsideView) {
		float rad = t.rotationAngle * (M_PI / 180.0f);

		float localX = (t.length * 0.4f) - 14.0f;
		float localY = t.height * 0.6f;
		float localZ = t.width * 0.2f;

		float finalX = t.position.x + (localX * cos(rad) - localZ * sin(rad));
		float finalZ = t.position.z - (localX * sin(rad) + localZ * cos(rad));
		float finalY = t.position.y + localY;

		camera.SetPos(finalX, finalY-2, finalZ);

		camera.SetYaw(-rad);
	}
}
