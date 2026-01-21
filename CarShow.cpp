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
//#include "ModelTree.h"
#include "StreetLamp.h"
#include "Sidewalk.h"
#include "FamilyCar.h"
#include "Road.h"
#include "ParkingRoad.h"
#include "Controller.h"
#include "frontOfBuilding.h"
#include "OutSide.h"
#include "MountainHall.h" 
#include "Mercedes.h";
#include "Bureau.h" //salma
#include "AdminDoor.h" //salma
#include "Chair.h"
#include "ModelTree.h"


using namespace std;

// THIS LINE WAS NEEDED. The error "unresolved external" means it was missing.
vector<Door*> globalDoors;

// --- 1. Global Variables ---
Camera camera;
Building buildingStructure;
MountainHall mountainHall;
Truck t(Point(-550, 7, 775));
Truck t2(Point(-200, 10, 200));
Truck t3(Point(-200, 10, 300));
Mercedes mercedes;
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
Cuboid ground(Point(0, -2, 0), 1, 4000, 4000);
//road:
Road mainRoad(-700.0f, -3.0f, -2000.0f, 300.0f, 4000.0f, 0.0f); //salma
Road sideRoad(-550.0f, -3.0f, 775.0f, 120.0f, 910.0f, 90.0f);    //salma
ParkingRoad parking(100.0f, -3.0f, 500.5f, 435.0f, 260.0f,90); //salma
//salma
Sofa sofa(Point(-145, 0, 630)); // salma
//Sofa sofa2(Point()); // salma
Sofa sofa2(Point(-145, 0, 520)); // salma
Sofa tripleSofa(Point(-190, 0, 614)); // salma
Bureau bureau(Point(-100, -1, 580));  // salma
AdminDoor adminDoor(Point(-200, 0, 510)); //salma
Chair adminChair(-80, -1, 580); //salma




Plaza buildingPlaza;
CityLayout myCity;

// Textures
Texture texFront, texBack, texLeft, texRight, texUp, texDown;
Texture texSidewalk, texPlaza, texStone, texResturant, texTrunk, texLeaves , texGrass;
Texture insideWallTex, outsideWallTex;

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
void forceLightingState(); // Helper to force lighting ON
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

    // 1. SETUP GLOBAL LIGHTING (SUN/MOON)
    setupLighting();

    // 2. DRAW SKYBOX
    // We disable lighting for the skybox itself (it's an environment map)
    // But we apply a dark color to tint it.
    glDisable(GL_LIGHTING);
    if (g_darkMode) glColor3f(0.3f, 0.3f, 0.4f); // Dark Blue tint for night sky
    else glColor3f(1.0f, 1.0f, 1.0f);           // White tint for day sky

    // Force texture modulate so the glColor above affects the sky texture
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glCallList(displayListID);

    // 3. RESET COLOR AND ENABLE LIGHTING FOR WORLD
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_LIGHTING);

    drawGround();
    buildingStructure.draw();
    mountainHall.draw();

    // --- CRITICAL FIX FOR ROADS ---
    // The Road class likely disables lighting internally. 
    // We force it back ON here.
    forceLightingState();
    mainRoad.draw();
    sideRoad.draw();
    parking.draw();

    // --- CRITICAL FIX FOR PLAZA & SIDEWALKS ---
    forceLightingState();
    buildingPlaza.draw(-550.0f, -500.0f, 0.0f, 720.0f, texPlaza.textureID, 20.0f);
    myCity.drawAllSidewalks(mySidewalk, myLamp, texSidewalk.textureID);
    myCity.drawCityBuildings(myLamp, texResturant.textureID, texStone);

    forceLightingState();
    sofa.setRotation(180); //salma
    sofa2.setRotation(0); //salma
    tripleSofa.setRotation(90);//salma

    sofa.draw(); //salma
    sofa2.draw(); //salma
    tripleSofa.drawTriple();
    bureau.draw(); //salma
    adminDoor.update(); //salma
    adminDoor.draw();//salma
    adminChair.draw();//salma


    // --- VEHICLES ---
    forceLightingState();
    glPushMatrix();
	//glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // اذا كبيتها ببطل راكبها
    glColor3f(0.8, 0.1, 0.1);
    t.draw(0.8, 0.8, 0.7);
    mercedes.Draw();
    glPopMatrix();
    glPushMatrix();
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        t2.draw(0.3,0.4,0.4);
        t3.draw(0.5, 0.4, 0.3);
    glPopMatrix();
    // Draw Again (As per your original code)
    forceLightingState();
    buildingStructure.draw();
	mainRoad.draw(); //salma
	sideRoad.draw(); //salma
	parking.draw(); //salma

    glutSwapBuffers();
}

// --- 5. Initialization Function ---
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    Controller::init(camera, t, buildingStructure, isInsideView, mercedes);
    // building textures
    outsideWallTex.loadTexture("Textures/outside.jpg");
    buildingStructure.wallTex = outsideWallTex.textureID;
    insideWallTex.loadTexture("Textures/insideWall.jpg");
    buildingStructure.wallTex2 = insideWallTex.textureID;

    // sky textures
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

    // side walk and plaza textures
    texSidewalk.loadTexture("Textures/sidewalk.jpg");
    texPlaza.loadTexture("Textures/tile2.jpg");
    texStone.loadTexture("Textures/ground.jpg");
    texGrass.loadTexture("Textures/grass5.jpg");
    texResturant.loadTexture("Textures/building.jpg");
    // building's ground texture 
    buildingStructure.groundTex = texPlaza.textureID;

    // tree model textures
    myTree.loadOBJ("models/Tree-Model/Tree1.obj");
    texTrunk.loadTexture("models/Tree-Model/bark_loo.bmp");
    texLeaves.loadTexture("models/Tree-Model/bat.bmp");
    

    for (const AABB& wall : buildingStructure.getWalls()) {
        camera.addWall(wall);
    }
	camera.addWall(ground.getAABB());
	t.walls = camera.walls;
    //std::cout<< "Total Walls in Camera Collision System: " << camera.walls.size() << std::endl;
	
    /*mercedes.Load("./resources/models/mercedes/mercedes-benz_amg_gt_black_series.obj", 10.0f);
    mercedes.SetPosition(-432.036, 0.3087, 441.793);
    mercedes.SetRotationY(90.0f);
    mercedes.EnterVehicle(true);*/

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
    t.Update();
    mercedes.Update();

    if (isInsideView) {
        if (Controller::activeVehicle == 1) {
            float rad = t.rotationAngle * (M_PI / 180.0f);
            float localX = (t.length * 0.4f) - 14.0f;
            float localY = t.height * 0.6f;
            float localZ = t.width * 0.2f;
            camera.SetPos(t.position.x + (localX * cos(rad) - localZ * sin(rad)),
                t.position.y + localY - 8,
                t.position.z - (localX * sin(rad) + localZ * cos(rad)));
            camera.SetYaw(-rad);
        }
        else if (Controller::activeVehicle == 2) {
            Point seat = mercedes.GetDriverSeatPosition();
            camera.SetPos(seat.x, seat.y, seat.z);


            float rad = mercedes.GetRotationY() * (3.14159f / 180.0f);

            camera.SetYaw(-rad + 1.5708f);
        }
    }
}

// Helper to force correct lighting state
void forceLightingState() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    // Force modulate mode so textures take light into account
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void setupLighting() {
    forceLightingState();
    GLfloat ambientLight[4];
    GLfloat diffuseLight[4];
    GLfloat lightPos[4] = { 0.0f, 500.0f, 500.0f, 1.0f };
    if (g_darkMode) {
        ambientLight[0] = 0.1f; ambientLight[1] = 0.1f; ambientLight[2] = 0.15f; ambientLight[3] = 1.0f;
        diffuseLight[0] = 0.1f; diffuseLight[1] = 0.1f; diffuseLight[2] = 0.15f; diffuseLight[3] = 1.0f;
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
	ground.drawWithTexture(texGrass.textureID, 50, 50);
    glEnd();
    glPopMatrix();
}