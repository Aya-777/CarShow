#pragma once
#include "Point.h"

class Sofa
{
private:
    Point center;    // sofa position
    float rotation;  // rotation angle in degrees around Y-axis

public:
    Sofa(Point c);

    void setPosition(Point c);     // move sofa
    void setRotation(float angle); // rotate sofa

    void draw();       // single sofa
    void drawTriple(); // optional triple sofa
};

