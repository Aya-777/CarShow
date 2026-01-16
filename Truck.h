#ifndef TRUCK_H
#define TRUCK_H

#include "Wheel.h"
#include <vector>

class Truck {
public:
    float length=70.0, height=25, width=25;
    Wheel wheelUnit;
    Point wheelPositions[6];

public:
    Point position;
    Point drveSeat;
    float doorAngle;
    bool doorsOpen;
    float wheelSpin;
    float steerAngle;
    bool isMovable;
    float rotationAngle;
    float speed;
    bool driverDoorOpen = false;   // Is the door toggled open?
    float driverDoorAngle = 0.0f;  // Current angle for animation

    Truck(Point position);
    void update();
    void draw();
    //void load();
};

#endif