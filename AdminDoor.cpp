#include "AdminDoor.h"
#include <GL/glut.h>
#include <cmath>

AdminDoor::AdminDoor()
{
    hinge = Point(0, 0, 0);
    angle = 0.0f;
    open = false;
}

AdminDoor::AdminDoor(Point hingePos)
{
    hinge = hingePos;
    angle = 0.0f;
    open = false;
}

void AdminDoor::toggle()
{
    open = !open;
}

void AdminDoor::update()
{
    float target = open ? -90.0f : 0.0f;

    // Smooth easing
    angle += (target - angle) * 0.05f;

    if (fabs(angle - target) < 0.1f)
        angle = target;
}

void AdminDoor::draw()
{
    float DOOR_WIDTH = 50.0f;
    float DOOR_HEIGHT = 50.0f;
    float DOOR_THICK = 3.0f;

    glPushMatrix();

    // Move to hinge position
    glTranslatef(hinge.x, hinge.y, hinge.z);

    // Rotate around hinge (LEFT side)
    glRotatef(angle, 0, 1, 0);

    glColor3ub(77, 82, 79);

    glBegin(GL_QUADS);

    // ===== FRONT =====
    glVertex3f(0, 0, 0);
    glVertex3f(DOOR_WIDTH, 0, 0);
    glVertex3f(DOOR_WIDTH, DOOR_HEIGHT, 0);
    glVertex3f(0, DOOR_HEIGHT, 0);

    // ===== BACK =====
    glVertex3f(0, 0, -DOOR_THICK);
    glVertex3f(DOOR_WIDTH, 0, -DOOR_THICK);
    glVertex3f(DOOR_WIDTH, DOOR_HEIGHT, -DOOR_THICK);
    glVertex3f(0, DOOR_HEIGHT, -DOOR_THICK);

    // ===== LEFT (HINGE) =====
    glVertex3f(0, 0, 0);
    glVertex3f(0, DOOR_HEIGHT, 0);
    glVertex3f(0, DOOR_HEIGHT, -DOOR_THICK);
    glVertex3f(0, 0, -DOOR_THICK);

    // ===== RIGHT =====
    glVertex3f(DOOR_WIDTH, 0, 0);
    glVertex3f(DOOR_WIDTH, DOOR_HEIGHT, 0);
    glVertex3f(DOOR_WIDTH, DOOR_HEIGHT, -DOOR_THICK);
    glVertex3f(DOOR_WIDTH, 0, -DOOR_THICK);

    glEnd();

    glPopMatrix();
}
