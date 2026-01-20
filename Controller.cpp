#include "Controller.h"
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Initialize static members
Camera* Controller::cameraRef = nullptr;
Truck* Controller::truckRef = nullptr;
bool* Controller::isInsideViewRef = nullptr;
bool Controller::mouseCaptured = false;
int Controller::lastMouseX = 0;
int Controller::lastMouseY = 0;
float Controller::mouseSensitivity = 0.0025f;
//salma
extern bool g_darkMode;


void Controller::init(Camera& cam, Truck& trk, bool& viewFlag) {
    cameraRef = &cam;
    truckRef = &trk;
    isInsideViewRef = &viewFlag;
}

void Controller::keyboard(unsigned char key, int x, int y) {
    if (!truckRef || !cameraRef) return;

    float rad = truckRef->rotationAngle * (M_PI / 180.0f);
    float step = 2.0f;

    switch (key) {
    case 'a': cameraRef->RotateYaw(-0.02f); break;
    case 'd': cameraRef->RotateYaw(0.02f); break;
    case 'w': cameraRef->Fly(2.0f); break;
    case 's': cameraRef->Fly(-2.0f); break;
    case 'o':
    case 'O': truckRef->backDoors.open = !truckRef->backDoors.open; break;
    case 'p': truckRef->driverDoor.open = !truckRef->driverDoor.open; break;
    case '1': // FORWARD
        truckRef->position.x += cos(rad) * step;
        truckRef->position.z -= sin(rad) * step;
        truckRef->wheelSpin -= 10.0f;
        break;
    case '2': // BACKWARD
        truckRef->position.x -= cos(rad) * step;
        truckRef->position.z += sin(rad) * step;
        truckRef->wheelSpin += 10.0f;
        break;
    case '3': // TURN LEFT
        truckRef->rotationAngle += 5.0f;
        truckRef->steerAngle = 20.0f;
        break;
    case '4': // TURN RIGHT
        truckRef->rotationAngle -= 5.0f;
        truckRef->steerAngle = -20.0f;
        break;
    case ' ':
        *isInsideViewRef = !(*isInsideViewRef);
        if (!(*isInsideViewRef)) cameraRef->Strafe(20);
        break;
    case 'n':
        cameraRef->openNearestDoor();
        break;
        //salma
    case 'm':
        g_darkMode = !g_darkMode;
        break;
        //*****//

    }
    glutPostRedisplay();
}

void Controller::specialKeys(int key, int x, int y) {
    if (!cameraRef) return;
    switch (key) {
    case GLUT_KEY_UP:    cameraRef->Move(20.0); break;
    case GLUT_KEY_DOWN:  cameraRef->Move(-10.0); break;
    case GLUT_KEY_LEFT:  cameraRef->Strafe(10.0); break;
    case GLUT_KEY_RIGHT: cameraRef->Strafe(-10.0); break;
    }
    glutPostRedisplay();
}

void Controller::mouseMove(int x, int y) {
    if (!mouseCaptured || !cameraRef) return;

    int dx = x - lastMouseX;
    int dy = y - lastMouseY;
    lastMouseX = x;
    lastMouseY = y;

    cameraRef->RotateYaw(dx * mouseSensitivity);
    cameraRef->RotatePitch(-dy * mouseSensitivity);
    glutPostRedisplay();
}

void Controller::mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseCaptured = true;
        lastMouseX = x;
        lastMouseY = y;
        glutSetCursor(GLUT_CURSOR_NONE);
    }
}