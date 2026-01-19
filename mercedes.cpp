#include "mercedes.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

struct Vec3 { float x, y, z; };
struct Vec2 { float u, v; };

Mercedes::Mercedes()
{
    m_displayList = 0;
    m_x = m_y = m_z = 0.0f;
    m_rotY = 0.0f;
}

Mercedes::~Mercedes()
{
    if (m_displayList)
        glDeleteLists(m_displayList, 1);
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

    m_displayList = glGenLists(1);
    glNewList(m_displayList, GL_COMPILE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    float diffuse[4] = { 0.8f, 0.0f, 0.0f, 1.0f };
    float ambient[4] = { 0.2f, 0.0f, 0.0f, 1.0f };
    float specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float shininess = 64.0f;

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
        else if (type == "usemtl")
{
    std::string mat;
    ss >> mat;

    if (mat == "Body" || mat == "CarPaint")
    {
        float bodyDiffuse[4]  = { 0.8f, 0.0f, 0.0f, 1.0f };
        float bodySpecular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bodyDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bodySpecular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 96.0f);
    }
    else if (mat == "Glass" || mat == "Windows")
    {
        float glassDiffuse[4] = { 0.1f, 0.1f, 0.1f, 0.4f };

        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glassDiffuse);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0f);
    }
    else if (mat == "Wheels" || mat == "Tires")
    {
        float wheelDiffuse[4] = { 0.05f, 0.05f, 0.05f, 1.0f };

        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wheelDiffuse);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 5.0f);
    }
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
                    glNormal3f(
                        normals[n - 1].x,
                        normals[n - 1].y,
                        normals[n - 1].z
                    );

                if (t > 0)
                    glTexCoord2f(
                        texcoords[t - 1].u,
                        texcoords[t - 1].v
                    );

                glVertex3f(
                    vertices[v - 1].x,
                    vertices[v - 1].y,
                    vertices[v - 1].z
                );
            }
        }
    }

    glEnd();
    glEndList();

    file.close();
    return true;
}

void Mercedes::Draw()
{
    if (!m_displayList)
        return;

    glPushMatrix();

    glTranslatef(m_x, m_y, m_z);
    glRotatef(m_rotY, 0.0f, 1.0f, 0.0f);

    glCallList(m_displayList);

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
