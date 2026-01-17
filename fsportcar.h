#pragma once
#include <string>
#include <GL/freeglut.h>

class FSportCar
{
private:
    GLuint m_displayList;
    float  m_posX, m_posY, m_posZ;
    float  m_rotY;
    float  m_scale;

public:
    FSportCar();

    bool Load(const std::string& objPath, float scale);

    void SetPosition(float x, float y, float z);
    void SetRotationY(float angleDeg);

    void Draw() const;
};
