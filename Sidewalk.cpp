#include "Sidewalk.h"

void Sidewalk::draw(float width, float height, float depth, GLuint textureID) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glColor3f(1.0f, 1.0f, 1.0f);

    float repeatX = width / 100.0f;
    float repeatZ = depth / 100.0f;
    float repeatH = height / 20.0f;

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);       glVertex3f(-width / 2, height, -depth / 2);
    glTexCoord2f(repeatX, 0.0f);    glVertex3f(width / 2, height, -depth / 2);
    glTexCoord2f(repeatX, repeatZ); glVertex3f(width / 2, height, depth / 2);
    glTexCoord2f(0.0f, repeatZ);    glVertex3f(-width / 2, height, depth / 2);

    glTexCoord2f(0.0f, 0.0f);       glVertex3f(-width / 2, 0, depth / 2);
    glTexCoord2f(repeatX, 0.0f);    glVertex3f(width / 2, 0, depth / 2);
    glTexCoord2f(repeatX, repeatH); glVertex3f(width / 2, height, depth / 2);
    glTexCoord2f(0.0f, repeatH);    glVertex3f(-width / 2, height, depth / 2);

    glTexCoord2f(0.0f, 0.0f);       glVertex3f(-width / 2, 0, -depth / 2);
    glTexCoord2f(repeatX, 0.0f);    glVertex3f(width / 2, 0, -depth / 2);
    glTexCoord2f(repeatX, repeatH); glVertex3f(width / 2, height, -depth / 2);
    glTexCoord2f(0.0f, repeatH);    glVertex3f(-width / 2, height, -depth / 2);

    glTexCoord2f(0.0f, 0.0f);       glVertex3f(width / 2, 0, -depth / 2);
    glTexCoord2f(repeatZ, 0.0f);    glVertex3f(width / 2, 0, depth / 2);
    glTexCoord2f(repeatZ, repeatH); glVertex3f(width / 2, height, depth / 2);
    glTexCoord2f(0.0f, repeatH);    glVertex3f(width / 2, height, -depth / 2);

    glTexCoord2f(0.0f, 0.0f);       glVertex3f(-width / 2, 0, -depth / 2);
    glTexCoord2f(repeatZ, 0.0f);    glVertex3f(-width / 2, 0, depth / 2);
    glTexCoord2f(repeatZ, repeatH); glVertex3f(-width / 2, height, depth / 2);
    glTexCoord2f(0.0f, repeatH);    glVertex3f(-width / 2, height, -depth / 2);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}