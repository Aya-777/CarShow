#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/freeglut.h>
#include "Camera.h"
#include "Truck.h"
#include "Building.h"

class Controller {
public:
    // References to the objects the controller needs to manipulate
    static Camera* cameraRef;
    static Truck* truckRef;
    static Building* buldingRef;
    static bool* isInsideViewRef;

    // Mouse state
    static bool mouseCaptured;
    static int lastMouseX;
    static int lastMouseY;
    static float mouseSensitivity;

    // Static callback functions (GLUT requires static functions)
    static void keyboard(unsigned char key, int x, int y);
    static void specialKeys(int key, int x, int y);
    static void mouseMove(int x, int y);
    static void mouseButton(int button, int state, int x, int y);

    // Initialization
    static void init(Camera& cam, Truck& trk, Building& bld, bool& viewFlag);
};

#endif
