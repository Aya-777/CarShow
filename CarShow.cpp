#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include <Windows.h>
#include <GL/stb_image.h>
#include <GL/freeglut.h>
#include "Point.h"
#include "Cuboid.h"
#include "Camera.h"
#include "Building.h"
#include "Skybox.h"
#include "ModelTree.h"
#include "StreetLamp.h"
#include "Sidewalk.h"

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
Building buildingStructure;
//Sky:
Texture texFront, texBack, texLeft, texRight, texUp, texDown;
Texture texRoad, texGrass;
SkyBox mySky;
//tree:
SmartTreeModel myTree;
GLuint texTrunk, texLeaves;
//street lamp & side walk:
Sidewalk mySidewalk;
GLuint texSidewalk;
StreetLamp myLamp;

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

GLuint loadTextureSTB(const char* filename) {
	int width, height, channels;
	unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
	if (!data) {
		printf("❌ فشل تحميل الصورة: %s\n", filename);
		return 0;
	}

	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
	printf("✅ تم تحميل الصورة بنجاح: %s\n", filename);
	return texID;
}

GLuint loadBMP_custom(const char* imagepath) {
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char* data;

	FILE* file = fopen(imagepath, "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }

	if (fread(header, 1, 54, file) != 54) { printf("Not a correct BMP file\n"); return 0; }
	if (header[0] != 'B' || header[1] != 'M') { printf("Not a correct BMP file\n"); return 0; }

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0)    imageSize = width * height * 3;
	if (dataPos == 0)      dataPos = 54;

	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

	delete[] data;
	return textureID;
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(g_iHeight, g_iWidth);
	glutCreateWindow("weee");
	glutFullScreen();
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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	drawGround();

	buildingStructure.draw();

	glCallList(displayListID);
	float pivotX = -600.0f;
	float pivotZ = -380.0f;

	glPushMatrix();
	glTranslatef(pivotX + 500.0f, -2.9f, pivotZ);
	mySidewalk.draw(1000.0f, 5.0f, 80.0f, texSidewalk);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(pivotX, -3.9f, pivotZ - 250.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	mySidewalk.draw(500.0f, 5.0f, 80.0f, texSidewalk);
	glPopMatrix();

	for (int i = 0; i < 3; i++)
	{
		float xBase = -600.0f + (i * 200.0f); // مسافة 200 بين الشجر
		float zPos = -450.0f;
		glPushMatrix();
		glTranslatef(xBase, -3.0f, zPos);
		glScalef(10.0f, 10.0f, 10.0f);
		myTree.draw(1.0f, texTrunk, texLeaves);
		glPopMatrix();
		if (i < 3) {
			glPushMatrix();
			glTranslatef(xBase + 100.0f, -3.0f, zPos);
			glScalef(2.5f, 2.5f, 2.5f);
			myLamp.draw();
			glPopMatrix();
		}
	}
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
	g_background.r =1;
	g_background.g = 1;
	g_background.b =1;
	glEnable(GL_DEPTH_TEST);
	//load textures here
	texFront.loadTexture("Textures/Sky_Clouds.jpg");
	texBack.loadTexture("Textures/Sky_Clouds.jpg");
	texLeft.loadTexture("Textures/Sky_Clouds.jpg");
	texRight.loadTexture("Textures/Sky_Clouds.jpg");
	texUp.loadTexture("Textures/Sky_Clouds.jpg");
	texDown.loadTexture("Textures/Sky_Clouds.jpg");
	mySky.SKYFRONT = texFront.textureID;
	mySky.SKYBACK = texBack.textureID;
	mySky.SKYLEFT = texLeft.textureID;
	mySky.SKYRIGHT = texRight.textureID;
	mySky.SKYUP = texUp.textureID;
	mySky.SKYDOWN = texDown.textureID;
	//side walk texture:
	texSidewalk = loadTextureSTB("Textures/sidewalk2.jpg");
	//load tree model

	myTree.loadOBJ("models/Tree-Model/Tree1.obj");
	texTrunk = loadTextureSTB("models/Tree-Model/bark_loo.bmp");
	texLeaves = loadTextureSTB("models/Tree-Model/bat.bmp");
	
	//display list
	displayListID = glGenLists(1);
	glNewList(displayListID, GL_COMPILE);
	mySky.Draw_Skybox(0, 0, 0, 10000, 10000, 10000);
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

static void specialKeysCallback(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        camera.Move(10.0);
        break;
    case GLUT_KEY_DOWN:
        camera.Move(-2.0);
        break;
    case GLUT_KEY_LEFT:
        camera.Strafe(-2.0);
        break;
    case GLUT_KEY_RIGHT:
        camera.Strafe(2.0);
        break;
    }
    glutPostRedisplay();
}
static void keyboardCallback(unsigned char key, int x, int y)
{
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
		glutPostRedisplay();
	}
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


