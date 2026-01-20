#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/freeglut.h>
#include <vector>
#include "Camera.h"
#include "Vehicle.h"  // Add this

class Controller {
public:
    // References
    static Camera* cameraRef;
    static bool* isInsideViewRef;

    // Vehicle system
    static std::vector<Vehicle*> vehicles;
    static Vehicle* currentVehicle;

    // Mouse state
    static bool mouseCaptured;
    static int lastMouseX;
    static int lastMouseY;
    static float mouseSensitivity;

    // Static callback functions
    static void keyboard(unsigned char key, int x, int y);
    static void specialKeys(int key, int x, int y);
    static void mouseMove(int x, int y);
    static void mouseButton(int button, int state, int x, int y);

    // Initialization
    static void init(Camera& cam, bool& viewFlag);

    // Vehicle management
    static void addVehicle(Vehicle* vehicle);
};

#endif