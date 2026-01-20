#include "mercedes.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <map>
#include <GL/freeglut.h>

struct Vec3 { float x, y, z; };
struct Vec2 { float u, v; };

std::map<std::string, Vec3> debugColors = {
    {"M_CarPaint_Max", {1.0f, 0.0f, 0.0f}},        // Red - Main body paint
    {"M_CarPaint", {1.0f, 0.0f, 0.0f}},            // Red - Alternate paint
    {"Gloss_Carbon", {0.1f, 0.1f, 0.1f}},          // Dark gray - Carbon fiber
    {"Carbon", {0.15f, 0.15f, 0.15f}},             // Dark gray - Carbon
    {"Glass", {0.0f, 0.8f, 1.0f}},                 // Cyan - Glass
    {"Window", {0.0f, 0.5f, 1.0f}},                // Blue - Windows
    {"Windows", {0.0f, 0.5f, 1.0f}},               // Blue - Windows plural
    {"Interior", {0.0f, 0.0f, 0.0f}},              // Brown - Interior
    {"Leather", {0.0f, 0.0f, 0.0f}},               // BLACK - Leather seats
    {"Seat", {0.0f, 0.0f, 0.0f}},                  // BLACK - Seats
    {"Steering", {0.0f, 0.0f, 0.0f}},              // BLACK - Steering wheel
    {"Dashboard", {0.0f, 0.0f, 0.0f}},             // BLACK - Dashboard
    {"Engine", {0.6f, 0.6f, 0.6f}},                // Gray - Engine parts
    {"Badge", {1.0f, 1.0f, 0.0f}},                 // Yellow - Badges/emblems                // Yellow - Badges/emblems
    {"Emblem", {1.0f, 1.0f, 0.0f}},                // Yellow - Emblems
    {"Mirror", {0.8f, 0.8f, 0.8f}},                // Light gray - Mirrors
    //{"Grille", {0.0f, 0.6f, 0.0f}},                // Green - Grille
    //{"Grilleb", {0.0f, 0.6f, 0.0f}},               // Green - Grille variant
    {"Grille_C", {0.0f, 0.4f, 0.0f}},              // Dark green - Grille chrome
    {"Chrome", {0.7f, 0.7f, 0.7f}},                // Silver - Chrome parts
    {"M_Chassis", {0.4f, 0.4f, 0.4f}},             // Gray - Chassis
    {"Brake", {1.0f, 0.0f, 0.0f}},                 // Red - Brake calipers
    {"Caliper", {1.0f, 0.0f, 0.0f}},               // Red - Brake calipers
    {"etk_calipers_ttsport", {1.0f, 0.5f, 0.0f}},  // Orange - Performance calipers
    {"Disc", {0.3f, 0.3f, 0.3f}},                  // Dark gray - Brake discs
    {"etk_brakedisc_carbon_ttsport", {0.2f, 0.2f, 0.2f}}, // Black - Carbon discs
    {"Tire", {0.1f, 0.1f, 0.1f}},                  // Black - Tires
    {"Wheel", {0.2f, 0.2f, 0.2f}},                 // Dark gray - Wheels
    {"Rim", {0.3f, 0.3f, 0.3f}},                   // Gray - Rims
    {"Light", {1.0f, 1.0f, 0.8f}},                 // Light yellow - Lights
    {"Headlight", {1.0f, 1.0f, 0.9f}},             // Off-white - Headlights
    {"Taillight", {1.0f, 0.0f, 0.0f}},             // Red - Taillights
    {"Exhaust", {0.2f, 0.2f, 0.2f}},               // Black - Exhaust
    {"License", {1.0f, 1.0f, 1.0f}},               // White - License plate
    {"Plastic", {0.3f, 0.3f, 0.3f}},               // Gray - Plastic parts
    {"Rubber", {0.1f, 0.1f, 0.1f}},                // Black - Rubber parts
    {"Metal", {0.5f, 0.5f, 0.5f}},                 // Gray - Metal parts
    {"Underbody", {0.3f, 0.3f, 0.3f}},             // Dark gray - Underbody
    {"Trim", {0.5f, 0.5f, 0.5f}},                  // Gray - Trim pieces
    {"Default", {0.8f, 0.8f, 0.8f}} ,               // Light gray - Default
    { "Light_Max", {1.0f, 1.0f, 0.7f} },          // Light yellow for lights
{"M_Swatch", {0.8f, 0.0f, 0.0f}},           // Red for swatch
{"Material.006", {0.5f, 0.5f, 0.5f}},       // Gray for generic materials
{"Material.011", {0.4f, 0.4f, 0.4f}},       // Dark gray
{"Material.003", {0.6f, 0.6f, 0.6f}},       // Light gray
{"material", {0.7f, 0.7f, 0.7f}},           // Generic material
};

// Add these to the constructor
Mercedes::Mercedes()
{
    m_displayListOpaque = 0;
    m_displayListGlass = 0;
    m_x = m_y = m_z = 0.0f;
    m_rotY = 0.0f;
    m_useDebugColors = true;  // Set to TRUE by default
    m_speed = 0.0f;
    m_wheelSpin = 0.0f;
    m_steerAngle = 0.0f;
    m_isMovable = false;
}

// Add update method
void Mercedes::Update()
{
    if (m_isMovable)
    {
        // Update position based on rotation and speed
        float rad = m_rotY * (3.14159f / 180.0f);
        m_x += cos(rad) * m_speed * 0.1f;
        m_z -= sin(rad) * m_speed * 0.1f;

        // Update wheel spin for visual effect
        m_wheelSpin -= m_speed * 5.0f;

        // Gradually reduce steering angle
        m_steerAngle *= 0.9f;

        // Reduce speed gradually (friction)
        m_speed *= 0.95f;
        if (fabs(m_speed) < 0.01f) m_speed = 0.0f;
    }
}

// Add movement methods
void Mercedes::MoveForward(float step)
{
    m_speed += step * 2.5f;
    if (m_speed > 20.0f) m_speed = 20.0f;
}

void Mercedes::MoveBackward(float step)
{
    m_speed -= step * 2.5f;
    if (m_speed < -11.5f) m_speed = -11.5f;
}

void Mercedes::RotateLeft(float angle)
{
    m_rotY += angle;
    m_steerAngle = angle * 2.0f;
}

void Mercedes::RotateRight(float angle)
{
    m_rotY -= angle;
    m_steerAngle = -angle * 2.0f;
}

void Mercedes::EnterVehicle(bool enter)
{
    m_isMovable = enter;
}

Mercedes::~Mercedes()
{
    if (m_displayListOpaque)
        glDeleteLists(m_displayListOpaque, 1);
    if (m_displayListGlass)
        glDeleteLists(m_displayListGlass, 1);
}

Point Mercedes::GetDriverSeatPosition() const
{
    float rad = m_rotY * (3.14159f / 180.0f);

    // CORRECT offsets to get (-439.914, 10.0115, 438.077)
    // when car is at (-432.036, 0.3087, 441.793) with rotation 90°
    float localX = 6.716f;    // Forward/backward offset
    float localY = 9.7028f;    // Height offset  
    float localZ = -15.178f;     // Left/right offset (positive = right side)

    // Transform to world coordinates
    float worldX = m_x + (localX * cos(rad) - localZ * sin(rad));
    float worldZ = m_z + (localX * sin(rad) + localZ * cos(rad));
    float worldY = m_y + localY;

    // Debug output to verify
    // printf("Car: (%.3f, %.3f, %.3f) rot: %.1f\n", m_x, m_y, m_z, m_rotY);
    // printf("Local: (%.3f, %.3f, %.3f)\n", localX, localY, localZ);
    // printf("Result: (%.3f, %.3f, %.3f)\n", worldX, worldY, worldZ);

    return Point(worldX, worldY, worldZ);
}

float Mercedes::GetDriverViewYaw() const
{
    return -m_rotY * (3.14159f / 180.0f);
}


bool Mercedes::Load(const std::string& objPath, float scale)
{
    std::ifstream file(objPath);
    if (!file.is_open())
    {
        std::cout << "Failed to load Mercedes OBJ: " << objPath << std::endl;
        return false;
    }

    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> texcoords;

    m_displayListOpaque = glGenLists(1);
    m_displayListGlass = glGenLists(1);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    bool isGlass = false;
    std::string currentMaterial;

    /* ============================
       PASS 1 — OPAQUE GEOMETRY (NO GLASS)
       ============================ */
    file.clear();
    file.seekg(0);

    glNewList(m_displayListOpaque, GL_COMPILE);
    glBegin(GL_TRIANGLES);

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v")
        {
            Vec3 v;
            ss >> v.x >> v.y >> v.z;
            v.x *= scale; v.y *= scale; v.z *= scale;
            vertices.push_back(v);
        }
        else if (type == "vn")
        {
            Vec3 n;
            ss >> n.x >> n.y >> n.z;
            normals.push_back(n);
        }
        else if (type == "vt")
        {
            Vec2 t;
            ss >> t.u >> t.v;
            texcoords.push_back(t);
        }
        else if (type == "usemtl")
        {
            std::string mat;
            ss >> mat;
            currentMaterial = mat;

            // Check if this is glass material - skip it in opaque pass
            isGlass = (mat == "Glass" || mat == "Window" || mat == "Windows");
            if (isGlass) continue;

            glDisable(GL_BLEND);
            glDepthMask(GL_TRUE);

            // DEBUG MODE: Use debug colors for opaque materials
            if (m_useDebugColors)
            {
                std::cout << "Debug mode opaque: " << mat << std::endl;

                // Try exact match first
                bool found = false;
                auto it = debugColors.find(mat);
                if (it != debugColors.end())
                {
                    Vec3 color = it->second;
                    GLfloat a[] = { color.x * 0.2f, color.y * 0.2f, color.z * 0.2f, 1.0f };
                    GLfloat d[] = { color.x, color.y, color.z, 1.0f };
                    GLfloat s[] = { 0.5f, 0.5f, 0.5f, 1.0f };
                    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a);
                    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
                    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s);
                    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 32);
                    found = true;
                }

                if (!found)
                {
                    // Try partial match
                    for (const auto& pair : debugColors)
                    {
                        if (mat.find(pair.first) != std::string::npos)
                        {
                            Vec3 color = pair.second;
                            GLfloat a[] = { color.x * 0.2f, color.y * 0.2f, color.z * 0.2f, 1.0f };
                            GLfloat d[] = { color.x, color.y, color.z, 1.0f };
                            GLfloat s[] = { 0.5f, 0.5f, 0.5f, 1.0f };
                            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a);
                            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
                            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s);
                            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 32);
                            found = true;
                            break;
                        }
                    }
                }

                if (!found)
                {
                    // Default material
                    Vec3 color = debugColors["Default"];
                    GLfloat a[] = { color.x * 0.2f, color.y * 0.2f, color.z * 0.2f, 1.0f };
                    GLfloat d[] = { color.x, color.y, color.z, 1.0f };
                    GLfloat s[] = { 0.4f, 0.4f, 0.4f, 1.0f };
                    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a);
                    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
                    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s);
                    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 32);
                }
            }
            // NORMAL MODE: Use original materials
            else
            {
                if (mat == "M_CarPaint_Max" || mat == "M_CarPaint")
                {
                    GLfloat a[] = { 0.05f,0.01f,0.01f,1 };
                    GLfloat d[] = { 0.20f,0.03f,0.03f,1 };
                    GLfloat s[] = { 0.95f,0.95f,0.95f,1 };
                    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a);
                    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
                    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s);
                    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
                }
                else
                {
                    GLfloat a[] = { 0.2f,0.2f,0.2f,1 };
                    GLfloat d[] = { 0.6f,0.6f,0.6f,1 };
                    GLfloat s[] = { 0.4f,0.4f,0.4f,1 };
                    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a);
                    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
                    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s);
                    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 32);
                }
            }
        }
        else if (type == "f" && !isGlass)
        {
            for (int i = 0; i < 3; i++)
            {
                std::string vert;
                ss >> vert;
                int v, t, n;
                sscanf_s(vert.c_str(), "%d/%d/%d", &v, &t, &n);

                if (n > 0) glNormal3f(normals[n - 1].x, normals[n - 1].y, normals[n - 1].z);
                if (t > 0) glTexCoord2f(texcoords[t - 1].u, texcoords[t - 1].v);
                glVertex3f(vertices[v - 1].x, vertices[v - 1].y, vertices[v - 1].z);
            }
        }
    }

    glEnd();
    glEndList();

    /* ============================
    PASS 2 — GLASS ONLY
    ============================ */
    file.clear();
    file.seekg(0);
    isGlass = false;

    glNewList(m_displayListGlass, GL_COMPILE);
    // Enable blending for glass
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    glBegin(GL_TRIANGLES);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "usemtl")
        {
            std::string mat;
            ss >> mat;

            // Only process glass materials in this pass
            isGlass = (mat == "Glass" || mat == "Window" || mat == "Windows");

            if (isGlass)
            {
                // DEBUG MODE: Use debug blue color for glass
                if (m_useDebugColors)
                {
                    std::cout << "Debug mode glass: " << mat << std::endl;

                    // Get color from debugColors map - try exact match first
                    Vec3 color;
                    auto it = debugColors.find(mat);
                    if (it != debugColors.end())
                        color = it->second;
                    else
                        color = debugColors["Glass"]; // Fallback

                    // Use FULL intensity colors for debug mode - NO MULTIPLICATION!
                    // For glass, we want it BRIGHT and visible
                    GLfloat a[] = { color.x * 0.3f, color.y * 0.3f, color.z * 0.3f, 0.25f };  // Ambient
                    GLfloat d[] = { color.x, color.y, color.z, 0.25f };                       // Diffuse - FULL COLOR
                    GLfloat s[] = { 0.95f, 0.95f, 0.95f, 1.0f };                              // High specular for glass
                    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a);
                    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
                    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s);
                    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);

                    std::cout << "DEBUG Glass material set - Color: R=" << color.x
                        << " G=" << color.y << " B=" << color.z
                        << " Alpha: 0.25" << std::endl;
                }
                // NORMAL MODE: Use original glass material
                else
                {
                    GLfloat a[] = { 0.05f, 0.06f, 0.07f, 0.35f };
                    GLfloat d[] = { 0.20f, 0.22f, 0.25f, 0.35f };
                    GLfloat s[] = { 1.0f, 1.0f, 1.0f, 1.0f };
                    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a);
                    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
                    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s);
                    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
                }
            }
        }
        else if (type == "f" && isGlass)
        {
            for (int i = 0; i < 3; i++)
            {
                std::string vert;
                ss >> vert;
                int v, t, n;
                sscanf_s(vert.c_str(), "%d/%d/%d", &v, &t, &n);

                if (n > 0) glNormal3f(normals[n - 1].x, normals[n - 1].y, normals[n - 1].z);
                if (t > 0) glTexCoord2f(texcoords[t - 1].u, texcoords[t - 1].v);
                glVertex3f(vertices[v - 1].x, vertices[v - 1].y, vertices[v - 1].z);
            }
        }
    }

    glEnd();
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glEndList();

    file.close();
    std::cout << "Mercedes model loaded with debug colors: " << (m_useDebugColors ? "ENABLED" : "DISABLED") << std::endl;
    return true;
}


void Mercedes::Draw()
{
    if (!m_displayListOpaque || !m_displayListGlass)
        return;

    glPushMatrix();

    glDisable(GL_COLOR_MATERIAL);
    glTranslatef(m_x, m_y, m_z);
    glRotatef(m_rotY, 0, 1, 0);

    // DEBUG: Draw a simple blue quad to test
    if (m_useDebugColors)
    {
        glDisable(GL_LIGHTING);  // Disable lighting for test
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBegin(GL_QUADS);
        glColor4f(0.0f, 0.8f, 1.0f, 0.5f);  // Bright cyan-blue
        glVertex3f(-2.0f, 0.0f, -2.0f);
        glVertex3f(2.0f, 0.0f, -2.0f);
        glVertex3f(2.0f, 2.0f, -2.0f);
        glVertex3f(-2.0f, 2.0f, -2.0f);
        glEnd();

        glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);
    }

    // OPAQUE FIRST
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    glCallList(m_displayListOpaque);

    // GLASS LAST
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    glCallList(m_displayListGlass);

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    glEnable(GL_COLOR_MATERIAL);
    glPopMatrix();
}


void Mercedes::SetPosition(float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

void Mercedes::SetRotationY(float angle)
{
    m_rotY = angle;
}

// Add this function to toggle debug colors
void Mercedes::SetDebugColors(bool enabled)
{
    m_useDebugColors = enabled;
    std::cout << "Debug colors: " << (enabled ? "ENABLED" : "DISABLED") << std::endl;
}