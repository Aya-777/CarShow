#pragma once
#include "Point.h"

class AdminDoor
{
public:
    Point hinge;     // hinge position
    float angle;     // current rotation angle
    bool open;       // REQUIRED by Camera (true = open, false = closed)

    AdminDoor();
    AdminDoor(Point hingePos);

    void toggle();
    void update();
    void draw();
};
