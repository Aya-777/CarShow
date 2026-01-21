#include "MercedesTruck.h"
#include <iostream>

MercedesTruck::MercedesTruck(Point position) : Truck(position) {
    // Initialize any specific Mercedes-related features here
}

void MercedesTruck::load() {
    bool success = driverSteeringWheel.Load("resources/models/mercedes/steering_wheel.obj", 15.0f);
    if (!success) {
        std::cout << "Failed to load Mercedes steering wheel!" << std::endl;
    }
    driverSteeringWheel.SetPosition(-5.0f, -13.0f, -4.0f);
    driverSteeringWheel.SetRotationY(300.0f);
    driverSteeringWheel.SetRotationZ(-15.0f);
}

void MercedesTruck::Update() {
    // Call the parent Truck's update function
    Truck::Update();
    // Additional Mercedes-specific update logic here
}

void MercedesTruck::Draw() {
    // Call the parent Truck's draw method, you can also change Mercedes specific details here
    Truck::Draw(0.8f, 0.8f, 0.7f);
}

void MercedesTruck::EnterVehicle(bool enter) {
    Truck::EnterVehicle(enter);
    if (enter) {
        std::cout << "Entered Mercedes Truck" << std::endl;
    }
    else {
        std::cout << "Exited Mercedes Truck" << std::endl;
    }
}

void MercedesTruck::MoveForward(float step) {
    Truck::MoveForward(step);
}

void MercedesTruck::MoveBackward(float step) {
    Truck::MoveBackward(step);
}

void MercedesTruck::RotateLeft(float angle) {
    Truck::RotateLeft(angle);
}

void MercedesTruck::RotateRight(float angle) {
    Truck::RotateRight(angle);
}

Point MercedesTruck::GetDriverSeatPosition() const {
    return Truck::GetDriverSeatPosition();
}

float MercedesTruck::GetDriverViewYaw() const {
    return Truck::GetDriverViewYaw();
}
