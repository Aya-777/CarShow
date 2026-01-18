#pragma once
#ifndef MERCEDES_H
#define MERCEDES_H

#include <string>
#include <GL/freeglut.h>

class Mercedes
{
public:
    Mercedes();
    ~Mercedes();

    bool Load(const std::string& objPath, float scale);
    void Draw();

    void SetPosition(float x, float y, float z);
    void SetRotationY(float angle);

private:
    GLuint m_displayList;

    float m_x, m_y, m_z;
    float m_rotY;
};

#endif
