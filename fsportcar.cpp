#include "FSportCar.h"
#include <iostream>

// IMPORTANT: this function already exists in your project
// (from bugatti.cpp / obj loader)
GLuint LoadOBJToDisplayList(const std::string& objPath, float scale);

FSportCar::FSportCar()
{
    m_displayList = 0;
    m_posX = m_posY = m_posZ = 0.0f;
    m_rotY = 0.0f;
    m_scale = 1.0f;
}

bool FSportCar::Load(const std::string& objPath, float scale)
{
    m_scale = scale;
    m_displayList = LoadOBJToDisplayList(objPath, scale);

    if (m_displayList == 0)
    {
        std::cout << "Failed to load car model: " << objPath << std::endl;
        return false;
    }

    return true;
}

void FSportCar::SetPosition(float x, float y, float z)
{
    m_posX = x;
    m_posY = y;
    m_posZ = z;
}

void FSportCar::SetRotationY(float angleDeg)
{
    m_rotY = angleDeg;
}

void FSportCar::Draw() const
{
    if (m_displayList == 0)
        return;

    glPushMatrix();

    glTranslatef(m_posX, m_posY, m_posZ);
    glRotatef(m_rotY, 0.0f, 1.0f, 0.0f);

    glCallList(m_displayList);

    glPopMatrix();
}
