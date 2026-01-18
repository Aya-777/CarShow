#include "SteeringWheel.h"
#include <fstream>
#include <sstream>
#include <iostream>

struct Vec3 { float x, y, z; };
struct Vec2 { float u, v; };

SteeringWheel::SteeringWheel()
{
    m_displayList = 0;
    m_x = m_y = m_z = 0.0f;
    m_rotY = 0.0f;
    m_rotZ = 0.0f;
}

SteeringWheel::~SteeringWheel()
{
    if (m_displayList)
        glDeleteLists(m_displayList, 1);
}

bool SteeringWheel::Load(const std::string& objPath, float scale)
{
    std::ifstream file(objPath);
    if (!file.is_open())
    {
        std::cout << "Failed to load steering wheel OBJ\n";
        return false;
    }

    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> texcoords;

    m_displayList = glGenLists(1);
    glNewList(m_displayList, GL_COMPILE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    // Set default material for the steering wheel (dark black)
    float diffuse[4] = { 0.05f, 0.05f, 0.05f, 1.0f }; // dark black
    float ambient[4] = { 0.02f, 0.02f, 0.02f, 1.0f };
    float specular[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
    float shininess = 15.0f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

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
            v.x *= scale;
            v.y *= scale;
            v.z *= scale;
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
        else if (type == "f")
        {
            for (int i = 0; i < 3; i++)
            {
                std::string vert;
                ss >> vert;

                int v = 0, t = 0, n = 0;
                sscanf_s(vert.c_str(), "%d/%d/%d", &v, &t, &n);

                if (n > 0)
                    glNormal3f(normals[n - 1].x, normals[n - 1].y, normals[n - 1].z);

                if (t > 0)
                    glTexCoord2f(texcoords[t - 1].u, texcoords[t - 1].v);

                glVertex3f(vertices[v - 1].x, vertices[v - 1].y, vertices[v - 1].z);
            }
        }
    }

    glEnd();
    glEndList();

    file.close();
    return true;
}

void SteeringWheel::Draw()
{
    if (!m_displayList) return;

    glPushMatrix();

    glTranslatef(m_x, m_y, m_z);
    glRotatef(m_rotY, 0, 1, 0);
    glRotatef(m_rotZ, 0, 0, 1);

    glCallList(m_displayList);

    glPopMatrix();
}

void SteeringWheel::SetPosition(float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

void SteeringWheel::SetRotationY(float angle)
{
    m_rotY = angle;
}

void SteeringWheel::SetRotationZ(float angle)
{
    m_rotZ = angle;
}