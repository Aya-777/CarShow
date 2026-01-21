#pragma once
#include <GL/freeglut.h>

class Chair
{
public:
    float x, y, z;
    float rotation; // ????? ??????

    Chair(float x, float y, float z);

    void draw();
    void rotate(float angle);
};
