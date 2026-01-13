#ifndef TRUCK_H
#define TRUCK_H

#include "Wheel.h"
#include <vector>

class Truck {
private:
    float length=70.0, height=25, width=25;
    Wheel wheelUnit; // Shared wheel settings
    Point wheelPositions[6];

public:
    Point position;
    float doorAngle;
    bool doorsOpen;
    float wheelSpin;
    float steerAngle;
    bool isMovable;


    Truck(Point position);
    void update();
    void draw();
};

#endif