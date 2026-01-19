#pragma once
#include <GL/freeglut.h>

class Sidewalk {
public:
    void draw(float width, float height, float depth, GLuint textureID) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glColor3f(1.0f, 1.0f, 1.0f); 

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2, height, -depth / 2);
        glTexCoord2f(5.0f, 0.0f); glVertex3f(width / 2, height, -depth / 2);
        glTexCoord2f(5.0f, 1.0f); glVertex3f(width / 2, height, depth / 2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-width / 2, height, depth / 2);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(-width / 2, 0, depth / 2);
        glTexCoord2f(5.0f, 0.0f); glVertex3f(width / 2, 0, depth / 2);
        glTexCoord2f(5.0f, 0.1f); glVertex3f(width / 2, height, depth / 2);
        glTexCoord2f(0.0f, 0.1f); glVertex3f(-width / 2, height, depth / 2);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
};
