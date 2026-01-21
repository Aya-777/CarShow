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



