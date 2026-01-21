#ifndef TRUCK_H
#define TRUCK_H

#include "Wheel.h"
#include "Door.h"
#include "SteeringWheel.h"
#include "Vehicle.h"
#include <string>
#include <vector>
extern std::vector<Door*> globalDoors;

class Truck : public Vehicle { 
public:
    float length = 70.0, height = 25, width = 25;
    Wheel wheelUnit;
    Point wheelPositions[6];
    const char* musicSoundPath = "debug/resources/sounds/cryingdoor.wav";
    bool isMusicPlaying = false;

public:
    Point position;
    Door backDoors;
    Door driverDoor;
    Door passengerDoor;
    float wheelSpin;
    float steerAngle;
    bool isMovable;
    float rotationAngle;
    float speed;
    SteeringWheel driverSteeringWheel;

    Truck(Point position);

    // Implement Vehicle interface methods
    void Draw() override;
    void Update() override;
    void EnterVehicle(bool enter) override;
    bool CanBeEntered() const override { return true; }

    Point GetPosition() const override { return position; }
    float GetRotationY() const override { return rotationAngle; }
    std::string GetName() const override { return "Truck"; }

    void MoveForward(float step) override;
    void MoveBackward(float step) override;
    void RotateLeft(float angle) override;
    void RotateRight(float angle) override;

    Point GetDriverSeatPosition() const override;
    float GetDriverViewYaw() const override;

    // Original methods
    void draw(float r = 0.9f, float g = 0.9f, float b = 0.85f); // Renamed from draw to Draw
    void load();
    void playMusic(Point cameraPos);
    void checkMusicDistance(Point cameraPos);

};

#endif