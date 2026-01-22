#include "FSportCar.h"
#include <iostream>

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
    std::cout << "Trueeeeeee" << std::endl;

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
    if (m_displayList == 0) return;

    glPushMatrix();

    // Save current states (lighting, enable bits, colors)
    glPushAttrib(GL_ENABLE_BIT | GL_LIGHTING_BIT | GL_CURRENT_BIT);

    // --- CRITICAL CHANGES ---
    glDisable(GL_LIGHTING);       // This removes all shadows and light reflections
    glDisable(GL_COLOR_MATERIAL); // Uses the colors from your .mtl file directly
    glDisable(GL_TEXTURE_2D);     // Ensures no residual textures affect the color

    // Transformations
    glTranslatef(m_posX, m_posY, m_posZ);
    glRotatef(m_rotY, 0.0f, 1.0f, 0.0f);

    // Draw the model with flat colors
    glCallList(m_displayList);

    // Restore the settings for the rest of the scene
    glPopAttrib();
    glPopMatrix();
}
