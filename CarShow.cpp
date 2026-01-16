#include <Windows.h>
#include <GL/freeglut.h>
#include "Point.h"
#include "Cuboid.h"
#include "Camera.h"
#include "Truck.h"
#include "Sofa.h"
#include "Window.h"
//#include "Building.h"

using namespace std;

struct color3f
{
	float r, g, b;
	color3f() { r = 0; g = 0; b = 0; }
	color3f(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
};

//definition of all functions

void display();
void updateScene();
void reshape(int w, int h);
void init();
void timer(int value);
void idle();
void specialKeysUp(int key, int x, int y);
static void keyboardCallback(unsigned char key, int x, int y);
static void specialKeysCallback(int key, int x, int y);
static void mouseMove(int x, int y);
static void mouseButton(int button, int state, int x, int y);




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
Camera camera;
bool g_mouseCaptured = false;
int g_lastMouseX = 0;
int g_lastMouseY = 0;
float g_mouseSensitivity = 0.0025f;
//Building buildingStructure;
bool isInsideView = false;
Truck t(Point(110, 3.5, 0));
Cuboid c(Point (300, 0, 0),30,30,30);
Window myWindow(Point(0, 0, 0), 100.0f, 200.0f, 200.0f, 5.15f, 5.15f, 5.15f, 5.15f, true);
//Window leftWindow(Point(0, 0,0), 1, 100.0, 100, 20, 20, 0.5, 0.5, true);

void drawGround()
{
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);
	glVertex3f(-2000.0f, -3.0f, -2000.0f);
	glVertex3f(2000.0f, -3.0f, -2000.0f);
	glVertex3f(2000.0f, -3.0f, 2000.0f);
	glVertex3f(-2000.0f, -3.0f, 2000.0f);
	glEnd();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(g_iHeight, g_iWidth);
	glutCreateWindow("weee");
	//glutFullScreen();
	init();
	glutSpecialUpFunc(specialKeysUp);
	glutSpecialFunc(specialKeysCallback);
	glutKeyboardFunc(keyboardCallback);
	glutPassiveMotionFunc(mouseMove);
	glutMouseFunc(mouseButton);
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

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	drawGround();
	glPushMatrix();

	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	glColor3f(0.8, 0.1, 0.1);
	c.draw();
	t.draw();
	//myWindow.draw(0.8f, 0.3f, 0.3f);
	//leftWindow.draw(0.8f, 0.1f, 0.1f);
	
	glPopMatrix();
	//buildingStructure.draw();

	glCallList(displayListID);

	glutSwapBuffers();
}


void idle()
{
	t.update();
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
	//glColor3f(0.2f, 0.3f, 0.8f);

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
		// 1. Define the LOCAL position of the driver's head relative to truck center
		float localX = t.length * 0.2f;   // Inside the cabin area
		float localY = t.height * 0.35f;  // Eye level
		float localZ = t.width * 0.0001f;  // Driver side seat

		// 2. Convert truck's logical rotation to Radians
		float rad = t.rotationAngle * (M_PI / 180.0f);

		// 3. Calculate Logical World Position
		float logicX = t.position.x + (localX * cos(rad) + localZ * sin(rad));
		float logicZ = t.position.z - (localX * sin(rad) - localZ * cos(rad));
		float logicY = t.position.y + localY;

		// 4. ACCOUNT FOR THE 180° FLIP in display()
		// Since display() does glRotatef(180, 0, 1, 0), the actual visual 
		// position is the negative of the logical X and Z.
		float finalX = -logicX;
		float finalZ = -logicZ;

		camera.SetPos(finalX, logicY, finalZ);

		// 5. SET THE DIRECTION (Yaw)
		float finalYaw = -rad + M_PI;
		camera.SetYaw(finalYaw);
	}

	glutPostRedisplay();
}
static void specialKeysCallback(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		camera.Move(20.0);
		break;
	case GLUT_KEY_DOWN:
		camera.Move(-10.0);
		break;
	case GLUT_KEY_LEFT:
		camera.Strafe(10.0);
		break;
	case GLUT_KEY_RIGHT:
		camera.Strafe(-10.0);
		break;
	}
	glutPostRedisplay();
}
static void keyboardCallback(unsigned char key, int x, int y)
{
	float rad = t.rotationAngle * (M_PI / 180.0f);
	float step = 2.0f;
	switch (key)
	{
	case 'a':
		camera.RotateYaw(-0.02);
		break; // Rotate Left
	case 'd':
		camera.RotateYaw(0.02);
		break; // Rotate Right
	case 'w':
		camera.Fly(2.0);
		break; // Move Up
	case 's':
		camera.Fly(-2.0);
		break; // Move Down
	case 'o': // 'O' for Open
	case 'O':
		t.doorsOpen = !t.doorsOpen;
		break;
		glutPostRedisplay();
	case 'p':
		t.driverDoorOpen = !t.driverDoorOpen;
		break;
	case '1': // FORWARD
		t.position.x += cos(rad) * step;
		t.position.z -= sin(rad) * step;
		t.wheelSpin -= 10.0f; // Spin wheels when moving
		break;

	case '2': // BACKWARD
		t.position.x -= cos(rad) * step;
		t.position.z += sin(rad) * step;
		t.wheelSpin += 10.0f;
		break;

	case '3': // ROTATE LEFT (Turn truck)
		t.rotationAngle += 5.0f;
		t.steerAngle = 20.0f; // Visual steering effect
		break;

	case '4': // ROTATE RIGHT (Turn truck)
		t.rotationAngle -= 5.0f;
		t.steerAngle = -20.0f;
		break;

	case ' ': // SPACE KEY
		isInsideView = !isInsideView;
		if (isInsideView) {
			cout << "Entered Driver View" << endl;
		}
		else {
			camera.Strafe(20);
		}
		break;
	}
	//Camera Position : x = 96.5 y = 17.25z = -6.25
	//	Camera Position : x = -0.994844 y = 0z = 0.101421
}
void specialKeysUp(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		cout << "up released" << endl;
	if (key == GLUT_KEY_DOWN)
		cout << "down released" << endl;
	if (key == GLUT_KEY_RIGHT)
		cout << "right released" << endl;
	if (key == GLUT_KEY_LEFT)
		cout << "left released" << endl;
}
static void mouseMove(int x, int y)
{
	if (!g_mouseCaptured)
		return;

	int dx = x - g_lastMouseX;
	int dy = y - g_lastMouseY;

	g_lastMouseX = x;
	g_lastMouseY = y;

	camera.RotateYaw(dx * g_mouseSensitivity);
	camera.RotatePitch(-dy * g_mouseSensitivity);

	glutPostRedisplay();
}

static void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		g_mouseCaptured = true;
		g_lastMouseX = x;
		g_lastMouseY = y;

		glutSetCursor(GLUT_CURSOR_NONE);
	}
}