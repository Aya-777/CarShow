#ifndef ROAD_H
#define ROAD_H

#include <GL/freeglut.h>

class Road
{
private:
    float x, y, z;      // position
    float width;
    float length;
    float rotationY;    // rotation in degrees around Y-axis

public:
    Road(); // default road
    Road(float xPos, float yPos, float zPos, float w, float l, float rotY = 0.0f); // custom

    void setPosition(float xPos, float yPos, float zPos);
    void setSize(float w, float l);
    void setRotation(float rotY);

    void draw();
};

#endif

