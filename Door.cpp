#include "Door.h"
#include <GL/glut.h>
#include <iostream>

void Door::drawDoor()
{
    const float DOOR_WIDTH = 202.0f;
    const float DOOR_HEIGHT = 92.0f;

    glPushMatrix();

    // Rotate around hinge (Y axis)
    glRotated(90.0 * OpenRate , 0, 1, 0);


    if (!this->open) {

    glBegin(GL_QUADS);
    // Bottom-left (hinge)
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(5.0f, 0.0f, 0.0f);

        // Bottom-right
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(DOOR_WIDTH, 0.0f, 0.0f);

        // Top-right
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(DOOR_WIDTH, DOOR_HEIGHT, 0.0f);

        // Top-left (hinge)
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(5.0f, DOOR_HEIGHT, 0.0f);
    glEnd();

    }
    else {

        glBegin(GL_QUADS);
        // Bottom-left (hinge)
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);

        // Bottom-right
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(DOOR_WIDTH, 0.0f, 0.0f);

        // Top-right
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(DOOR_WIDTH, DOOR_HEIGHT, 0.0f);

        // Top-left (hinge)
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.0f, DOOR_HEIGHT, 0.0f);
        glEnd();
    }


    glPopMatrix();
}


void Door::openDoor()
{
	if (this->open && this->OpenRate < 1.0)
		this->OpenRate += 0.01;  // opening
	else if (!this->open && this->OpenRate > 0.0)
		this->OpenRate -= 0.01;  // closing
}


//Door::Door()
//{
//    hinge = Point(0, 0, 0);
//    angle = 0.0f;
//    open = false;
//}
//
//Door::Door(Point hingePos)
//{
//    hinge = hingePos;
//    angle = 0.0f;
//    open = false;
//}
//
//void Door::toggle()
//{
//    open = !open;
//}
//
//void Door::update()
//{
//    float target = open ? -90.0f : 0.0f;
//
//    // Smooth easing
//    angle += (target - angle) * 0.05f;
//
//    if (fabs(angle - target) < 0.1f)
//        angle = target;
//}
//
//void Door::draw()
//{
//    glPushMatrix();
//
//    // Move to hinge
//    glTranslatef(hinge.x, hinge.y, hinge.z);
//
//    // Rotate around hinge
//    glRotatef(angle, 0, 1, 0);
//
//    // Draw door (hinge on left)
//    glColor3f(0.55f, 0.27f, 0.07f);
//
//    glBegin(GL_QUADS);
//
//    // Front face
//    glVertex3f(0, 0, 0);
//    glVertex3f(30, 0, 0);
//    glVertex3f(30, 50, 0);
//    glVertex3f(0, 50, 0);
//
//    // Back face
//    glVertex3f(0, 0, -2);
//    glVertex3f(30, 0, -2);
//    glVertex3f(30, 50, -2);
//    glVertex3f(0, 50, -2);
//
//    // Left side (hinge)
//    glVertex3f(0, 0, 0);
//    glVertex3f(0, 50, 0);
//    glVertex3f(0, 50, -2);
//    glVertex3f(0, 0, -2);
//
//    // Right side
//    glVertex3f(30, 0, 0);
//    glVertex3f(30, 50, 0);
//    glVertex3f(30, 50, -2);
//    glVertex3f(30, 0, -2);
//
//    glEnd();
//
//    glPopMatrix();
//}
