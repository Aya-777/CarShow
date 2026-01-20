#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include <Windows.h>
#include <GL/stb_image.h>
#include <GL/freeglut.h>
#include <vector>
#include "Point.h"
#include "Cuboid.h"
#include "Camera.h"
#include "Truck.h"
#include "Sofa.h"
#include "Window.h"
#include "Building.h"
#include "Skybox.h"
#include "ModelTree.h"
#include "StreetLamp.h"
#include "Sidewalk.h"
#include "FamilyCar.h"
#include "Road.h"
#include "ParkingRoad.h"
#include "Controller.h"
#include "frontOfBuilding.h"
#include "OutSide.h"
#include "MountainHall.h" // <<< ملفك

using namespace std;
vector<Door*> globalDoors;

struct color3f {
    float r, g, b; color3f() { r = 0; g = 0; b = 0; } color3f(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
};

void display();
void updateScene();
void reshape(int w, int h);
void init();
void timer(int value);
void idle();
static void keyboardCallback(unsigned char key, int x, int y);
static void specialKeysCallback(int key, int x, int y);
static void mouseMove(int x, int y);
static void mouseButton(int button, int state, int x, int y);

Point center = Point(0, -3, 0);
Texture texture, up, left, Right, down, front, back, wallTexture;
Texture texSidewalk, texSidewalk2, texPlaza, texGrass, texResturant;
int g_iWidth = 800, g_iHeight = 600;
const float g_fNear = 1, g_fFar = 1000000000.0f;
color3f g_background;
GLuint displayListID;
Truck t(Point(-300, 3.5, 450));
bool isInsideView = false;
Camera camera;
bool g_mouseCaptured = false;
int g_lastMouseX = 0, g_lastMouseY = 0;
float g_mouseSensitivity = 0.0025f;
Building buildingStructure;
MountainHall mountainHall; // <<< الكائن الخاص بك
Texture texFront, texBack, texLeft, texRight, texUp, texDown, texRoad;
SkyBox mySky;
SmartTreeModel myTree;
Texture texTrunk, texLeaves;
Sidewalk mySidewalk;
StreetLamp myLamp;
Road mainRoad(-700.0f, -3.0f, -2000.0f, 200.0f, 4000.0f, 0.0f);
Road sideRoad(-606.0f, -3.0f, 440.0f, 80.0f, 760.0f, 90.0f);
ParkingRoad parking(0.0f, -3.0f, 360.0f, 80.0f, 155.0f, 90.0f, 2.0f, 40.0f);
Plaza buildingPlaza;
CityLayout myCity;

void drawGround() {
    glPushMatrix();
    texGrass.Use();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-2000.0f, -3.01f, -2000.0f);
    glTexCoord2f(50.0f, 0.0f);  glVertex3f(2000.0f, -3.01f, -2000.0f);
    glTexCoord2f(50.0f, 50.0f); glVertex3f(2000.0f, -3.01f, 2000.0f);
    glTexCoord2f(0.0f, 50.0f);  glVertex3f(-2000.0f, -3.01f, 2000.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Car Show");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(specialKeysCallback);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(mouseButton);
    camera.SetPos(-500.0f, 10.0f, 800.0f);
    camera.RotateYaw(-0.1);
    glutTimerFunc(1, timer, 0);
    glutMainLoop();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.Refresh();
    drawGround();
    buildingStructure.draw();
    mountainHall.draw(); // <<< رسم صالتك
    mainRoad.draw();
    sideRoad.draw();
    parking.draw();
    buildingPlaza.draw(-550.0f, -350.0f, 0.0f, 400.0f, texPlaza.textureID, 20.0f);
    myCity.drawAllSidewalks(mySidewalk, myLamp, texSidewalk.textureID);
    myCity.drawCityBuildings(myLamp, texResturant.textureID);
    glPushMatrix();
    glColor3f(0.8, 0.1, 0.1);
    t.draw(0.8, 0.8, 0.7);
    glPopMatrix();
    glCallList(displayListID);
    for (int i = 0; i < 2; i++) {
        float xBase = -500.0f + (i * 200.0f);
        float zPos = -450.0f;
        glPushMatrix();
        glTranslatef(xBase, -3.0f, zPos);
        glScalef(10.0f, 10.0f, 10.0f);
        myTree.draw(1.0f, texTrunk.textureID, texLeaves.textureID);
        glPopMatrix();
    }
    glutSwapBuffers();
}

void idle() {
    display();
}

void timer(int value) {
    glutTimerFunc(1000 / 30, timer, 0);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    wallTexture.loadTexture("textures/outside.jpg");
    buildingStructure.wallTex = wallTexture.textureID;
    wallTexture.loadTexture("textures/insideWall.jpg");
    buildingStructure.wallTex2 = wallTexture.textureID;
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
    texSidewalk.loadTexture("Textures/sidewalk.jpg");
    texPlaza.loadTexture("Textures/tile2.jpg");
    texGrass.loadTexture("Textures/grass5.jpg");
    texResturant.loadTexture("Textures/building.jpg");
    myTree.loadOBJ("models/Tree-Model/Tree1.obj");
    texTrunk.loadTexture("models/Tree-Model/bark_loo.bmp");
    texLeaves.loadTexture("models/Tree-Model/bat.bmp");
    displayListID = glGenLists(1);
    glNewList(displayListID, GL_COMPILE);
    mySky.Draw_Skybox(0, 0, 0, 10000, 10000, 10000);
    glEndList();
}

void reshape(int w, int h) {
    g_iHeight = h;
    g_iWidth = w;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.f, (float)w / (float)h, g_fNear, g_fFar);
    glMatrixMode(GL_MODELVIEW);
}

void updateScene() {}

static void specialKeysCallback(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP: camera.Move(20.0); break;
    case GLUT_KEY_DOWN: camera.Move(-10.0); break;
    case GLUT_KEY_LEFT: camera.Strafe(10.0); break;
    case GLUT_KEY_RIGHT: camera.Strafe(-10.0); break;
    }
    glutPostRedisplay();
}

static void keyboardCallback(unsigned char key, int x, int y) {
    switch (key) {
    case 'a': camera.RotateYaw(-0.02); break;
    case 'd': camera.RotateYaw(0.02); break;
    case 'w': camera.Fly(2.0); break;
    case 's': camera.Fly(-2.0); break;
    }
    glutPostRedisplay();
}

static void mouseMove(int x, int y) {
    if (!g_mouseCaptured) return;
    int dx = x - g_lastMouseX;
    int dy = y - g_lastMouseY;
    g_lastMouseX = x;
    g_lastMouseY = y;
    camera.RotateYaw(dx * g_mouseSensitivity);
    camera.RotatePitch(-dy * g_mouseSensitivity);
    glutPostRedisplay();
}

static void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        g_mouseCaptured = true;
        g_lastMouseX = x;
        g_lastMouseY = y;
        glutSetCursor(GLUT_CURSOR_NONE);
    }
}
