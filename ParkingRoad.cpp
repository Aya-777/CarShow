#include "ParkingRoad.h"

// Default constructor
ParkingRoad::ParkingRoad()
{
    x = 0.0f;
    y = -3.0f;
    z = 0.0f;
    width = 100.0f;
    length = 200.0f;
    rotationY = 0.0f;
    lineWidth = 2.0f;
    lineSpacing = 20.0f;
}

// Custom constructor
ParkingRoad::ParkingRoad(float xPos, float yPos, float zPos, float w, float l, float rotY,
    float lineW, float spacing)
{
    x = xPos;
    y = yPos;
    z = zPos;
    width = w;
    length = l;
    rotationY = rotY;
    lineWidth = lineW;
    lineSpacing = spacing;
}

void ParkingRoad::setPosition(float xPos, float yPos, float zPos) { x = xPos; y = yPos; z = zPos; }
void ParkingRoad::setSize(float w, float l) { width = w; length = l; }
void ParkingRoad::setRotation(float rotY) { rotationY = rotY; }
void ParkingRoad::setLineWidth(float lw) { lineWidth = lw; }
void ParkingRoad::setLineSpacing(float spacing) { lineSpacing = spacing; }

void ParkingRoad::draw()
{
    glPushMatrix();

    glTranslatef(x, y, z);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.01f, 0.0f); // avoid z-fighting

    // Asphalt color
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-width / 2, 0.0f, 0.0f);
    glVertex3f(width / 2, 0.0f, 0.0f);
    glVertex3f(width / 2, 0.0f, length);
    glVertex3f(-width / 2, 0.0f, length);
    glEnd();

    // White parking lines (perpendicular to lane)
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(lineWidth);

    glBegin(GL_LINES);
    for (float i = lineSpacing; i < length; i += lineSpacing)
    {
        glVertex3f(-width / 2 + 5.0f, 0.02f, i);
        glVertex3f(width / 2 - 5.0f, 0.02f, i);
    }
    glEnd();

    glPopMatrix();
}
