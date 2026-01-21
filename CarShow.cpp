#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include <Windows.h>
#include <GL/stb_image.h>
#include <GL/freeglut.h>
#include <vector>
#include <cmath>
#include <iostream>
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
#include "MountainHall.h" 

using namespace std;

// THIS LINE WAS NEEDED. The error "unresolved external" means it was missing.
vector<Door*> globalDoors;

// --- 1. Global Variables ---
Camera camera;
Building buildingStructure;
MountainHall mountainHall;
Truck t(Point(-300, 3.5, 450));
bool isInsideView = false, g_mouseCaptured = false, g_darkMode = false;
int g_lastMouseX = 0, g_lastMouseY = 0;
int g_iWidth = 1200, g_iHeight = 800;
float g_mouseSensitivity = 0.0025f;
const float g_fNear = 1, g_fFar = 1000000000.0f;

// Environment Objects
SkyBox mySky;
SmartTreeModel myTree;
Sidewalk mySidewalk;
StreetLamp myLamp;
Road mainRoad(-700.0f, -3.0f, -2000.0f, 200.0f, 4000.0f, 0.0f);
Road sideRoad(-606.0f, -3.0f, 440.0f, 80.0f, 760.0f, 90.0f);
ParkingRoad parking(0.0f, -3.0f, 360.0f, 80.0f, 155.0f, 90.0f, 2.0f, 40.0f);
Plaza buildingPlaza;
CityLayout myCity;

// Textures
Texture texFront, texBack, texLeft, texRight, texUp, texDown;
Texture texSidewalk, texPlaza, texGrass, texResturant, texTrunk, texLeaves;

// Display List
GLuint displayListID;

// --- 2. Function Prototypes ---
void display();
void reshape(int w, int h);
void init();
void idle();
void timer(int value);
void setupLighting();
void drawGround();
//void keyboardCallback(unsigned char key, int x, int y);
//void specialKeysCallback(int key, int x, int y);
//void mouseMove(int x, int y);
//void mouseButton(int button, int state, int x, int y);
void updateScene();

// --- 3. Main Function ---
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(g_iWidth, g_iHeight);
    glutCreateWindow("Car Show | Final Version");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(Controller::keyboard);
    //glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(Controller::specialKeys);
    //glutSpecialFunc(specialKeysCallback);
    glutPassiveMotionFunc(Controller::mouseMove);
    //glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(Controller::mouseButton);
    //glutMouseFunc(mouseButton);

    camera.SetPos(-500.0f, 20.0f, 800.0f);
    camera.RotateYaw(-1.0);
    glutTimerFunc(1, timer, 0);
    glutMainLoop();
    return 0;
}

// --- 4. Display Function ---
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (g_darkMode) glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
    else glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.Refresh();
    setupLighting();

    glCallList(displayListID);

    drawGround();
    buildingStructure.draw();
    mountainHall.draw();
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

    glutSwapBuffers();
}

// --- 5. Initialization Function ---
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    Controller::init(camera, t, buildingStructure, isInsideView);
    Texture tempTex1, tempTex2;
    tempTex1.loadTexture("Textures/outside.jpg");
    buildingStructure.wallTex = tempTex1.textureID;
    tempTex2.loadTexture("Textures/insideWall.jpg");
    buildingStructure.wallTex2 = tempTex2.textureID;
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

// --- 6. Other Functions ---
void reshape(int w, int h) {
    g_iWidth = w; g_iHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.f, (float)w / (float)h, g_fNear, g_fFar);
    glMatrixMode(GL_MODELVIEW);
}

void idle() {
    updateScene();
    t.checkMusicDistance(camera.GetPos());
    display();
}

void timer(int value) {
    glutTimerFunc(1000 / 30, timer, 0);
}

void updateScene() {
    t.update();
    if (isInsideView) {
        float rad = t.rotationAngle * (3.1415926535 / 180.0f);
        float localX = (t.length * 0.4f) - 14.0f;
        float localY = t.height * 0.6f;
        float localZ = t.width * 0.2f;
        float finalX = t.position.x + (localX * cos(rad) - localZ * sin(rad));
        float finalZ = t.position.z - (localX * sin(rad) + localZ * cos(rad));
        float finalY = t.position.y + localY;
        camera.SetPos(finalX, finalY - 3, finalZ);
        camera.SetYaw(-rad);
    }
}

void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat ambientLight[4];
    GLfloat diffuseLight[4];
    GLfloat lightPos[4] = { 0.0f, 500.0f, 500.0f, 1.0f };
    if (g_darkMode) {
        ambientLight[0] = 0.15f; ambientLight[1] = 0.15f; ambientLight[2] = 0.20f; ambientLight[3] = 1.0f;
        diffuseLight[0] = 0.3f; diffuseLight[1] = 0.3f; diffuseLight[2] = 0.35f; diffuseLight[3] = 1.0f;
    }
    else {
        ambientLight[0] = 0.6f; ambientLight[1] = 0.6f; ambientLight[2] = 0.6f; ambientLight[3] = 1.0f;
        diffuseLight[0] = 1.0f; diffuseLight[1] = 1.0f; diffuseLight[2] = 1.0f; diffuseLight[3] = 1.0f;
    }
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void drawGround() {
    glPushMatrix();
    texGrass.Use();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    if (g_darkMode) glColor3f(0.4f, 0.4f, 0.4f);
    else glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-2000.0f, -3.01f, -2000.0f);
    glTexCoord2f(50.0f, 0.0f);  glVertex3f(2000.0f, -3.01f, -2000.0f);
    glTexCoord2f(50.0f, 50.0f); glVertex3f(2000.0f, -3.01f, 2000.0f);
    glTexCoord2f(0.0f, 50.0f);  glVertex3f(-2000.0f, -3.01f, 2000.0f);
    glEnd();
    glPopMatrix();
}