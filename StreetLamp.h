#pragma once
#include <GL/freeglut.h>

class StreetLamp {
private:
    GLUquadric* quad;

public:
    StreetLamp();
    ~StreetLamp();

    void draw();
};