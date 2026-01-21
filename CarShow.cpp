#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <GL/freeglut.h>
#include <vector>
#include <cmath>
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
#include "Road.h"  //salma
#include "ParkingRoad.h" //salma
#include "Controller.h"
#include "frontOfBuilding.h"
#include "OutSide.h"
#include "Bureau.h" //salma
#include "AdminDoor.h" //salma
#include "Chair.h"


using namespace std;
vector<Door*> globalDoors;


struct color3f
{
    float r, g, b;
    color3f() { r = 0; g = 0; b = 0; }
    color3f(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
};

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
Texture wallTexture;
Texture texSidewalk;
Texture texSidewalk2;
Texture texPlaza;
Texture texGrass;
Texture texResturant;
int g_iWidth = 800;
int g_iHeight = 600;
const float g_fNear = 1;
const float g_fFar = 1000000000.0f;
color3f g_background;
GLuint displayListID;
Truck t(Point(-300, 3.5, 450));
bool isInsideView = false;
Camera camera;
bool g_mouseCaptured = false;
int g_lastMouseX = 0;
int g_lastMouseY = 0;
float g_mouseSensitivity = 0.0025f;
Building buildingStructure;
//Sky:
Texture texFront, texBack, texLeft, texRight, texUp, texDown;
Texture texRoad;
SkyBox mySky;
//tree:
//SmartTreeModel myTree;
Texture texTrunk, texLeaves;
//street lamp & side walk:
Sidewalk mySidewalk;
StreetLamp myLamp;
//road:
Road mainRoad(-700.0f, -3.0f, -2000.0f, 300.0f, 4000.0f, 0.0f); //salma
Road sideRoad(-550.0f, -3.0f, 695.0f, 100.0f, 755.0f, 90.0f);    //salma
ParkingRoad parking(-65.0f, -3.0f, 575.5f, 140.0f, 270.0f, 90.0f, 2.0f, 40.0f); //salma
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
bool g_darkMode = false; //salma

//salma
void setupLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientLight[4];
    GLfloat diffuseLight[4];
    GLfloat lightPos[4] = { 0.0f, 500.0f, 500.0f, 1.0f };

    if (g_darkMode)
    {
        // 🌙 DARK MODE LIGHTING
        ambientLight[0] = 0.15f;
        ambientLight[1] = 0.15f;
        ambientLight[2] = 0.20f;
        ambientLight[3] = 1.0f;

        diffuseLight[0] = 0.3f;
        diffuseLight[1] = 0.3f;
        diffuseLight[2] = 0.35f;
        diffuseLight[3] = 1.0f;
    }
    else
    {
        // ☀️ NORMAL MODE LIGHTING
        ambientLight[0] = 0.6f;
        ambientLight[1] = 0.6f;
        ambientLight[2] = 0.6f;
        ambientLight[3] = 1.0f;

        diffuseLight[0] = 1.0f;
        diffuseLight[1] = 1.0f;
        diffuseLight[2] = 1.0f;
        diffuseLight[3] = 1.0f;
    }

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}


void drawGround()
{
    glPushMatrix();
    texGrass.Use();

    // ضبط التكرار ليكون العشب واقعياً
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //glColor3f(1.0f, 1.0f, 1.0f);
    //salma
    if (g_darkMode)
        glColor3f(0.4f, 0.4f, 0.4f);
    else
        glColor3f(1.0f, 1.0f, 1.0f);


    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);   glVertex3f(-2000.0f, -3.01f, -2000.0f);
    glTexCoord2f(50.0f, 0.0f);  glVertex3f(2000.0f, -3.01f, -2000.0f);
    glTexCoord2f(50.0f, 50.0f); glVertex3f(2000.0f, -3.01f, 2000.0f);
    glTexCoord2f(0.0f, 50.0f);  glVertex3f(-2000.0f, -3.01f, 2000.0f);
    glEnd();

    // REMOVED: glDisable(GL_TEXTURE_2D); 
    // Do not disable here, or it will turn off textures for the buildings/truck drawn afterwards.

    glPopMatrix();
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
    //glutFullScreen();
    init();

    Controller::init(camera, t, isInsideView);
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
    //glClearColor(g_background.r, g_background.g, g_background.b, 1.0);
    //salma
    if (g_darkMode)
        glClearColor(0.05f, 0.05f, 0.08f, 1.0f); // dark night sky
    else
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   // normal


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    camera.Refresh();
    //salma
    setupLighting();


    //setupLighting();
    //setupShadow();
    drawGround();

    buildingStructure.draw();
    mainRoad.draw(); //salma
    sideRoad.draw(); //salma
    parking.draw(); //salma

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


    buildingPlaza.draw(-550.0f, -350.0f, 0.0f, 400.0f, texPlaza.textureID, 20.0f); // tile of out side
    myCity.drawAllSidewalks(mySidewalk, myLamp, texSidewalk.textureID);// out side scene
    myCity.drawCityBuildings(myLamp, texResturant.textureID); // buildings of out side scene

	glPushMatrix();
	//glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // اذا كبيتها ببطل راكبها
	glColor3f(0.8, 0.1, 0.1);
	t.draw(0.8, 0.8, 0.7);
	float x, y, z;
	camera.GetPos(x, y, z);
	//cout << "CameraPos: " << x << " " << y << " "<< z << endl;
	glPopMatrix();
	buildingStructure.draw();
	mainRoad.draw(); //salma
	sideRoad.draw(); //salma
	parking.draw(); //salma

    glCallList(displayListID);

    //for (int i = 0; i < 2; i++)
    //{
    //    float xBase = -500.0f + (i * 200.0f); // مسافة 200 بين الشجر
    //    float zPos = -450.0f;
    //    glPushMatrix();
    //    glTranslatef(xBase, -3.0f, zPos);
    //    glScalef(10.0f, 10.0f, 10.0f);
    //    myTree.draw(1.0f, texTrunk.textureID, texLeaves.textureID);
    //    glPopMatrix();
    //}
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
    //salma
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    //****************//

    g_background.r = 1;
    g_background.g = 1;
    g_background.b = 1;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D); // Ensure texturing is enabled globally
    //salma
    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


    // ==========================================
    // 1. LOAD ALL TEXTURES FIRST
    // ==========================================

    // NOTE: Changed "textures" to "Textures" to match your folder name
    wallTexture.loadTexture("Textures/outside.jpg");
    buildingStructure.wallTex = wallTexture.textureID;

    wallTexture.loadTexture("Textures/insideWall.jpg");
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
	//side walk texture:
	texSidewalk.loadTexture("Textures/sidewalk.jpg");
	texSidewalk2.loadTexture("Textures/sidewalk.jpg");
	texPlaza.loadTexture("Textures/tile2.jpg");
	texGrass.loadTexture("Textures/grass5.jpg");
	texResturant.loadTexture("Textures/building.jpg");
	//load tree model

    // Tree Textures
    // Assuming 'models' folder is lowercase. If it is 'Models', change it here.
    //myTree.loadOBJ("models/Tree-Model/Tree1.obj");
    texTrunk.loadTexture("models/Tree-Model/bark_loo.bmp");
    texLeaves.loadTexture("models/Tree-Model/bat.bmp");

    // Assign Texture IDs to Skybox Object
    mySky.SKYFRONT = texFront.textureID;
    mySky.SKYBACK = texBack.textureID;
    mySky.SKYLEFT = texLeft.textureID;
    mySky.SKYRIGHT = texRight.textureID;
    mySky.SKYUP = texUp.textureID;
    mySky.SKYDOWN = texDown.textureID;

    // ==========================================
    // 2. COMPILE DISPLAY LISTS
    // ==========================================

    // Only generate one display list for ID, or generate a new ID for the second one.
    // I am re-using the variable here to match your logic, but ensuring we don't leak memory.
    displayListID = glGenLists(1);
    glNewList(displayListID, GL_COMPILE);

    // Do NOT load textures inside here. Only draw.
    mySky.Draw_Skybox(0, 0, 0, 10000, 10000, 10000);
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

        camera.SetPos(finalX, finalY - 2, finalZ);

        camera.SetYaw(-rad);
    }
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
        //salma
    case 'm':
    case 'M':
        g_darkMode = !g_darkMode;
        cout << (g_darkMode ? "Dark Mode ON" : "Dark Mode OFF") << endl;
        break;
     //*****//
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
    case 'e':
        buildingStructure.toggleDoor();
    case 'o': // 'O' for Open
    case 'O':
        t.backDoors.open = !t.backDoors.open;
        break;
        glutPostRedisplay();
    case 'p':
        t.driverDoor.open = !t.driverDoor.open;

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
	case 'n':
		cout << "hi" << endl;
		float cx, cy, cz;
		camera.GetPos(cx, cy, cz);
		camera.openNearestDoor();
		t.playMusic(Point(0, 0, 0));
		break;
	case 'c':
	case 'C':
		cout << "Assume 'camPos' is the Point/Vector of your current camera";
			float x, y, z;
			camera.GetPos(x, y, z);
			t.playMusic(Point(x, y, z));
			break;

	}
	glutPostRedisplay();
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


