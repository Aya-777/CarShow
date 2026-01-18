#pragma once
#include <GL/freeglut.h>

class Plaza {
public:
    void draw(float xStart, float zStart, float xEnd, float zEnd, GLuint textureID, float repeatCount);
};