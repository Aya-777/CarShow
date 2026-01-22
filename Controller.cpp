#include "Controller.h"
#include <iostream>
#include <cmath>
#include "AdminDoor.h" //salma
#include "Chair.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "Truck.h"
#include "Building.h"
#include "Mercedes.h"

// Initialize static members
Camera* Controller::cameraRef = nullptr;
Mercedes* Controller::mercedesRef = nullptr;
int Controller::activeVehicle = 0;
Truck* Controller::truckRef = nullptr;
Building* Controller::buldingRef = nullptr;
bool* Controller::isInsideViewRef = nullptr;
bool Controller::mouseCaptured = false;
int Controller::lastMouseX = 0;
int Controller::lastMouseY = 0;
float Controller::mouseSensitivity = 0.0025f;
//salma
extern bool g_darkMode;
extern AdminDoor adminDoor;
extern Chair adminChair;


void Controller::init(Camera& cam, Truck& trk, Building& bld, bool& viewFlag , Mercedes& m) {
    cameraRef = &cam;
    truckRef = &trk;
    buldingRef = &bld;
    isInsideViewRef = &viewFlag;
    mercedesRef = &m;
}

void Controller::keyboard(unsigned char key, int x, int y) {
    if (!truckRef || !cameraRef || !mercedesRef) return;

    switch (key) {
    case 'r':   // rotate chair
        adminChair.rotate(5.0f);
        break;
    case 'a': cameraRef->RotateYaw(-0.02f); break;
    case 'd': cameraRef->RotateYaw(0.02f); break;
    case 'w': cameraRef->Fly(2.0f); break;
    case 's': cameraRef->Fly(-2.0f); break;
        /*case 'o': truckRef->backDoors.open = !truckRef->backDoors.open; break;
        case 'p': truckRef->driverDoor.open = !truckRef->driverDoor.open; break;*/
    case 'p': truckRef->playMusic(cameraRef->GetPos()); break;
    case 'm': g_darkMode = !g_darkMode; break;
    case 'e': buldingRef->toggleDoor(); break;
    case 'o': adminDoor.toggle(); break;


    case ' ': 
        if (*isInsideViewRef) {
            
            *isInsideViewRef = false;
            if (activeVehicle == 2) mercedesRef->EnterVehicle(false);
            activeVehicle = 0;
            cameraRef->Strafe(20);
        }
        else {
            // Check proximity to Truck
            if (cameraRef->GetPos().dist(truckRef->position) <= 60.0f) {
                *isInsideViewRef = true;
                activeVehicle = 1;
            }
            // Check proximity to Mercedes
            else if (cameraRef->GetPos().dist(mercedesRef->GetPosition()) <= 60.0f) {
                *isInsideViewRef = true;
                activeVehicle = 2;
                mercedesRef->EnterVehicle(true);
            }
        }
        break;

    case 'n':
        cameraRef->openNearestDoor();
        break;
        //salma
    }
    glutPostRedisplay();
}
void Controller::specialKeys(int key, int x, int y)
{
    float truckRad = truckRef->rotationAngle * (M_PI / 180.0f);
    float truckStep = 5.0f;
    float mercStep = 0.5f;
    float camStep = 10.0f;

    switch (key)
    {
    case GLUT_KEY_UP:
        if (*isInsideViewRef) {
            if (activeVehicle == 1) {
              truckRef->speed = 2.0f; // Set backward speed
                // truckRef->position.x += cos(truckRad) * truckStep;
                // truckRef->position.z -= sin(truckRad) * truckStep;
                // truckRef->wheelSpin -= 10.0f;
            }
            else if (activeVehicle == 2) {
                mercedesRef->MoveForward(mercStep);
            }
        }
        else {
            cameraRef->Move(camStep);
        }
        break;

    case GLUT_KEY_DOWN:
        if (*isInsideViewRef) {
            if (activeVehicle == 1) { 
              truckRef->speed = -2.0f; // Set backward speed
                // truckRef->position.x -= cos(truckRad) * truckStep;
                // truckRef->position.z += sin(truckRad) * truckStep;
                // truckRef->wheelSpin += 10.0f;
            }
            else if (activeVehicle == 2) {
                mercedesRef->MoveBackward(mercStep);
            }
        }
        else {
            cameraRef->Move(-camStep);
        }
        break;

    case GLUT_KEY_LEFT:
        if (*isInsideViewRef) {
            if (activeVehicle == 1) { 
                truckRef->rotationAngle += 5.0f;
                truckRef->steerAngle = 20.0f;
                std::cout << "TRUCK: Rotating LEFT. New rotationAngle: "
                    << truckRef->rotationAngle << "°" << std::endl;
            }
            else if (activeVehicle == 2) {
                mercedesRef->RotateLeft(5.0f);
            }
        }
        else {
            cameraRef->Strafe(camStep);
        }
        break;
        
    case GLUT_KEY_RIGHT:
        if (*isInsideViewRef) {
            if (activeVehicle == 1) {
                truckRef->rotationAngle -= 5.0f;
                truckRef->steerAngle = -20.0f;
            }
            else if (activeVehicle == 2) {
                mercedesRef->RotateRight(5.0f);
            }
        }
        else {
            cameraRef->Strafe(-camStep);
        }
        break;
        
    }
    glutPostRedisplay();
}
//    float rad = truckRef->rotationAngle * (M_PI / 180.0f);
//    float step = 2.0f;
//
//    switch (key)
//    {
//    case GLUT_KEY_UP:
//        cameraRef->Move(20.0);
//        if (*isInsideViewRef) {
//            Point nextPos = truckRef->position;
//            // FORWARD MATH
//            nextPos.x += cos(rad) * step;
//            nextPos.z -= sin(rad) * step;
//
//            if (!truckRef->checkCollision(nextPos)) {
//                truckRef->position = nextPos;
//                truckRef->wheelSpin -= 10.0f;
//            }
//            else {
//                std::cout << "Collision ahead!" << std::endl;
//                truckRef->isMovable = false; // Disable auto-movement if you have any
//                truckRef->steerAngle = 0;    // Reset steering
//            }
//        }
//        break;
//
//    case GLUT_KEY_DOWN:
//        cameraRef->Move(-10.0);
//        if (*isInsideViewRef) {
//            Point nextPos = truckRef->position;
//            // BACKWARD MATH: Notice the signs are swapped (- and +)
//            nextPos.x -= cos(rad) * step;
//            nextPos.z += sin(rad) * step;
//
//            if (!truckRef->checkCollision(nextPos)) {
//                truckRef->position = nextPos; // This correctly moves it back
//                truckRef->wheelSpin += 10.0f;
//            }
//            else {
//                std::cout << "Collision behind!" << std::endl;
//                truckRef->isMovable = false; // Disable auto-movement if you have any
//                truckRef->steerAngle = 0;    // Reset steering
//            }
//        }
//        break;
//
//    case GLUT_KEY_LEFT:
//        cameraRef->Strafe(10.0);
//        if (*isInsideViewRef) {
//            // Turning usually doesn't need a nextPos check unless the truck moves while turning
//            truckRef->rotationAngle += 5.0f;
//            truckRef->steerAngle = 20.0f;
//        }
//        break;
//
//    case GLUT_KEY_RIGHT:
//        cameraRef->Strafe(-10.0);
//        if (*isInsideViewRef) {
//            truckRef->rotationAngle -= 5.0f;
//            truckRef->steerAngle = -20.0f;
//        }
//        break;
//    }
//    glutPostRedisplay();
//}


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
