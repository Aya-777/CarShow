#ifndef TRUCK_H
#define TRUCK_H

#include "Wheel.h"
#include "Door.h"
#include "SteeringWheel.h"
#include <vector>
#include "aabb.h"
extern std::vector<Door*> globalDoors;

class Truck {
public:
    float length=70.0, height=25, width=25;
    Wheel wheelUnit;
    Point wheelPositions[6];
    const char* musicSoundPath = "debug/resources/sounds/cryingdoor.wav";

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
    std::vector<AABB> walls;


    Truck(Point position);
    void update();
    void draw(float r = 0.9f, float g = 0.9f, float b = 0.85f);
    void load();
    void playMusic(Point cameraPos);
    bool checkCollision(Point oldPos);
    AABB getAABB() const;
    void Move();
};

#endif