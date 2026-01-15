#ifndef GLASS_H
#define GLASS_H

#include "Point.h"
#include <GL/glut.h>

class Glass {
public:
    Glass(Point center, double height, double width, double length);
    void draw(float r, float g, float b, float alpha);

private:
    Point center;
    double height, width, length;
};

#endif