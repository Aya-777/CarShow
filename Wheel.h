#ifndef WHEEL_H
#define WHEEL_H

#include <GL/freeglut.h>
#include "Point.h"

class Wheel {
private:
    float width;
    float radius;

public:
    float spinAngle;
    float steerAngle;
    Wheel(float width = 0.15f, float radius = 0.45f);

    void draw(Point p, bool canSteer);
};

#endif