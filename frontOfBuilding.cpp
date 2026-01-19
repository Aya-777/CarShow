#include "frontOfBuilding.h"

void Plaza::draw(float xStart, float zStart, float xEnd, float zEnd, GLuint textureID, float repeatCount) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor3f(1.0f, 1.0f, 1.0f); 

    glPushMatrix();

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(xStart, -2.96f, zStart);

    glTexCoord2f(repeatCount, 0.0f);
    glVertex3f(xEnd, -2.96f, zStart);

    glTexCoord2f(repeatCount, repeatCount);
    glVertex3f(xEnd, -2.96f, zEnd);

    glTexCoord2f(0.0f, repeatCount);
    glVertex3f(xStart, -2.96f, zEnd);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}