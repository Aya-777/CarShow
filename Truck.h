#ifndef TRUCK_H
#define TRUCK_H

#include "Wheel.h"
#include <vector>

class Truck {
private:
    float length=10.0, height=2.5, width=2.5;
    Wheel wheelUnit; // Shared wheel settings
    Point wheelPositions[6];

public:
    Point position;
    float wheelSpin;
    float steerAngle;
    bool isMovable;


    Truck(Point position);
    void update();
    void draw();
};

#endif