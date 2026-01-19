#include "Road.h"

// Default road (used if you want one main road)
Road::Road()
{
    x = -700.0f;
    y = -3.0f;
    z = -2000.0f;

    width = 200.0f;
    length = 4000.0f;

    rotationY = 0.0f; // default no rotation
}

// Custom road (THIS allows multiple roads)
Road::Road(float xPos, float yPos, float zPos, float w, float l, float rotY)
{
    x = xPos;
    y = yPos;
    z = zPos;

    width = w;
    length = l;

    rotationY = rotY; // allows rotation
}

void Road::setPosition(float xPos, float yPos, float zPos)
{
    x = xPos;
    y = yPos;
    z = zPos;
}

void Road::setSize(float w, float l)
{
    width = w;
    length = l;
}

void Road::setRotation(float rotY)
{
    rotationY = rotY;
}

void Road::draw()
{
    glPushMatrix();

    glTranslatef(x, y, z);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f); // rotation around Y
    glTranslatef(0.0f, 0.01f, 0.0f);        // avoid z-fighting

    // Asphalt
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-width / 2, 0.0f, 0.0f);
    glVertex3f(width / 2, 0.0f, 0.0f);
    glVertex3f(width / 2, 0.0f, length);
    glVertex3f(-width / 2, 0.0f, length);
    glEnd();

    // Center dashed line
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);
    for (float i = 0; i < length; i += 40.0f)
    {
        glVertex3f(0.0f, 0.02f, i);
        glVertex3f(0.0f, 0.02f, i + 20.0f);
    }
    glEnd();

    glPopMatrix();
}
