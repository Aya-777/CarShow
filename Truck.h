#ifndef TRUCK_H
#define TRUCK_H

#include "Wheel.h"
#include "Door.h"
#include <vector>
extern std::vector<Door*> globalDoors;

class Truck {
public:
    float length=70.0, height=25, width=25;
    Wheel wheelUnit;
    Point wheelPositions[6];

public:
    Point position;
    Door backDoors;
	Door driverDoor;
    float wheelSpin;
    float steerAngle;
    bool isMovable;
    float rotationAngle;
    float speed;


    Truck(Point position);
    void update();
    void draw();
    //void load();
};

#endif