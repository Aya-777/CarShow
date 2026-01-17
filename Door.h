#pragma once
#include "Point.h"

class Door
{
public:
    Point hinge;     // hinge position
    float angle;     // current rotation angle
    bool open;       // REQUIRED by Camera (true = open, false = closed)

    Door();
    Door(Point hingePos);

    void toggle();
    void update();
    void draw();
};