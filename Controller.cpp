#include "Controller.h"
#include "Truck.h"  // For truck-specific operations
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Initialize static members
Camera* Controller::cameraRef = nullptr;
bool* Controller::isInsideViewRef = nullptr;
std::vector<Vehicle*> Controller::vehicles;
Vehicle* Controller::currentVehicle = nullptr;
bool Controller::mouseCaptured = false;
int Controller::lastMouseX = 0;
int Controller::lastMouseY = 0;
float Controller::mouseSensitivity = 0.0025f;

// External variable from main.cpp
extern bool g_darkMode;

void Controller::init(Camera& cam, bool& viewFlag) {
    cameraRef = &cam;
    isInsideViewRef = &viewFlag;
}

void Controller::addVehicle(Vehicle* vehicle) {
    vehicles.push_back(vehicle);
}

Vehicle* getClosestVehicle() {
    if (Controller::vehicles.empty()) return nullptr;

    // Get camera position
    float camX, camY, camZ;
    Controller::cameraRef->GetPos(camX, camY, camZ);
    Point cameraPos(camX, camY, camZ);

    Vehicle* closest = nullptr;
    float minDistance = 30.0f; // Reduced from 15.0f to make it easier to enter

    for (Vehicle* vehicle : Controller::vehicles) {
        if (!vehicle->CanBeEntered()) continue;

        // Use driver seat position for distance check (more accurate)
        Point driverSeat = vehicle->GetDriverSeatPosition();
        float distance = sqrt(
            pow(driverSeat.x - cameraPos.x, 2) +
            pow(driverSeat.y - cameraPos.y, 2) +
            pow(driverSeat.z - cameraPos.z, 2)
        );

        // Also check distance to vehicle center as fallback
        Point vehicleCenter = vehicle->GetPosition();
        float centerDistance = sqrt(
            pow(vehicleCenter.x - cameraPos.x, 2) +
            pow(vehicleCenter.y - cameraPos.y, 2) +
            pow(vehicleCenter.z - cameraPos.z, 2)
        );

        // Use the smaller of the two distances
        distance = (distance < centerDistance) ? distance : centerDistance;

        std::cout << "Checking " << vehicle->GetName()
            << ": distance = " << distance
            << ", position = (" << vehicleCenter.x << ", "
            << vehicleCenter.y << ", " << vehicleCenter.z << ")" << std::endl;

        if (distance < minDistance) {
            minDistance = distance;
            closest = vehicle;
        }
    }

    if (closest) {
        std::cout << "Closest vehicle: " << closest->GetName()
            << " at distance " << minDistance << std::endl;
    }

    return closest;
}
void toggleVehicleEntry() {
    if (Controller::currentVehicle) {
        // Exit current vehicle
        Controller::currentVehicle->EnterVehicle(false);
        Controller::currentVehicle = nullptr;
        *Controller::isInsideViewRef = false;

        // Move camera slightly away from vehicle when exiting
        float camX, camY, camZ;
        Controller::cameraRef->GetPos(camX, camY, camZ);
        Controller::cameraRef->SetPos(camX, camY + 5.0f, camZ - 5.0f);

        std::cout << "Exited vehicle" << std::endl;
    }
    else {
        // Enter closest vehicle
        Vehicle* closest = getClosestVehicle();
        if (closest) {
            Controller::currentVehicle = closest;
            Controller::currentVehicle->EnterVehicle(true);
            *Controller::isInsideViewRef = true;

            // Set camera to driver position
            Point driverPos = closest->GetDriverSeatPosition();
            Controller::cameraRef->SetPos(driverPos.x, driverPos.y, driverPos.z);
            Controller::cameraRef->SetYaw(closest->GetDriverViewYaw());

            std::cout << "Entered " << closest->GetName() << std::endl;
        }
        else {
            std::cout << "No vehicle nearby to enter. Need to be within 30 units." << std::endl;
        }
    }
}

void Controller::keyboard(unsigned char key, int x, int y) {
    if (!cameraRef) return;

    float step = 4.0f;
    float angle = 5.0f;

    switch (key) {
    case ' ': // Space key - toggle vehicle entry
        toggleVehicleEntry();
        break;

        // Vehicle controls (only work when inside a vehicle)
    case '1': // Forward
        if (currentVehicle)
            currentVehicle->MoveForward(step);
        break;

    case '2': // Backward
        if (currentVehicle)
            currentVehicle->MoveBackward(step);
        break;

    case '3': // Rotate left
        if (currentVehicle)
            currentVehicle->RotateLeft(angle);
        break;

    case '4': // Rotate right
        if (currentVehicle)
            currentVehicle->RotateRight(angle);
        break;

        // Other controls
    case 'a':
        cameraRef->RotateYaw(-0.02f);
        break;

    case 'd':
        cameraRef->RotateYaw(0.02f);
        break;

    case 'w':
        cameraRef->Fly(2.0f);
        break;

    case 's':
        cameraRef->Fly(-2.0f);
        break;

    case 'o':
    case 'O': // Open truck back doors
        // Find the truck in vehicles and toggle its back doors
        for (Vehicle* vehicle : vehicles) {
            if (vehicle->GetName() == "Truck") {
                Truck* truck = dynamic_cast<Truck*>(vehicle);
                if (truck) {
                    truck->backDoors.open = !truck->backDoors.open;
                }
                break;
            }
        }
        break;

    case 'p': // Open truck driver door
        for (Vehicle* vehicle : vehicles) {
            if (vehicle->GetName() == "Truck") {
                Truck* truck = dynamic_cast<Truck*>(vehicle);
                if (truck) {
                    truck->driverDoor.open = !truck->driverDoor.open;
                }
                break;
            }
        }
        break;

    case 'm':
    case 'M':
        g_darkMode = !g_darkMode;
        std::cout << (g_darkMode ? "Dark Mode ON" : "Dark Mode OFF") << std::endl;
        break;

    case 'n':
        cameraRef->openNearestDoor();
        break;
    }
    glutPostRedisplay();
}

void Controller::specialKeys(int key, int x, int y) {
    if (!cameraRef) return;

    switch (key) {
    case GLUT_KEY_UP:
        cameraRef->Move(20.0);
        break;
    case GLUT_KEY_DOWN:
        cameraRef->Move(-10.0);
        break;
    case GLUT_KEY_LEFT:
        cameraRef->Strafe(10.0);
        break;
    case GLUT_KEY_RIGHT:
        cameraRef->Strafe(-10.0);
        break;
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