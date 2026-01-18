#ifndef PARKINGROAD_H
#define PARKINGROAD_H

#include <GL/freeglut.h>

class ParkingRoad
{
private:
    float x, y, z;      // position
    float width;        // width of the parking lane
    float length;       // length of the parking lane
    float rotationY;    // rotation around Y-axis in degrees
    float lineWidth;    // width of the white parking lines
    float lineSpacing;  // spacing between parking lines

public:
    ParkingRoad(); // default
    ParkingRoad(float xPos, float yPos, float zPos, float w, float l, float rotY = 0.0f,
        float lineW = 2.0f, float spacing = 20.0f);

    void setPosition(float xPos, float yPos, float zPos);
    void setSize(float w, float l);
    void setRotation(float rotY);
    void setLineWidth(float lw);
    void setLineSpacing(float spacing);

    void draw();
};

#endif
