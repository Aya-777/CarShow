// bugatti.cpp
// Simple OBJ + MTL loader using legacy OpenGL (display lists, immediate mode)
// Compatible with FreeGLUT + Visual Studio 2022

#include <GL/freeglut.h>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

// stb_image (SINGLE IMPLEMENTATION IN THIS FILE)
#define STB_IMAGE_IMPLEMENTATION
#include <GL/stb_image.h>

// ------------------ DATA STRUCTURES ------------------

struct SimpleVertex { float x, y, z; };
struct SimpleTexCoord { float u, v; };
struct SimpleNormal { float x, y, z; };

struct Material
{
    std::string name;

    float Ka[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float Kd[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float Ks[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float Ns = 32.0f;

    std::string map_Kd;
    GLuint texID = 0;
    bool hasTexture = false;
};

// ------------------ TEXTURE LOADING ------------------

static GLuint LoadTextureFromFile(const std::string& filename, bool& ok)
{
    ok = false;

    int w, h, c;
    unsigned char* data = stbi_load(filename.c_str(), &w, &h, &c, 0);
    if (!data)
    {
        std::cout << "Texture load failed: " << filename << std::endl;
        return 0;
    }

    GLenum format = (c == 4) ? GL_RGBA : GL_RGB;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    ok = true;
    return tex;
}

// ------------------ MTL PARSER ------------------

static void ParseMTL(const std::string& path, std::map<std::string, Material>& materials)
{
    std::ifstream f(path);
    if (!f.is_open())
    {
        std::cout << "Failed to open MTL: " << path << std::endl;
        return;
    }

    Material* current = nullptr;
    std::string line;

    while (std::getline(f, line))
    {
        std::istringstream iss(line);
        std::string tag;
        iss >> tag;

        if (tag == "newmtl")
        {
            std::string name;
            iss >> name;
            materials[name] = Material();
            materials[name].name = name;
            current = &materials[name];
        }
        else if (tag == "Ka" && current)
        {
            iss >> current->Ka[0] >> current->Ka[1] >> current->Ka[2];
        }
        else if (tag == "Kd" && current)
        {
            iss >> current->Kd[0] >> current->Kd[1] >> current->Kd[2];
        }
        else if (tag == "Ks" && current)
        {
            iss >> current->Ks[0] >> current->Ks[1] >> current->Ks[2];
        }
        else if (tag == "Ns" && current)
        {
            iss >> current->Ns;
        }
        else if (tag == "map_Kd" && current)
        {
            iss >> current->map_Kd;
        }
    }
}


// ------------------ NORMAL COMPUTATION ------------------

static SimpleNormal ComputeNormal(
    const SimpleVertex& a,
    const SimpleVertex& b,
    const SimpleVertex& c)
{
    float ux = b.x - a.x;
    float uy = b.y - a.y;
    float uz = b.z - a.z;

    float vx = c.x - a.x;
    float vy = c.y - a.y;
    float vz = c.z - a.z;

    SimpleNormal n;
    n.x = uy * vz - uz * vy;
    n.y = uz * vx - ux * vz;
    n.z = ux * vy - uy * vx;

    float len = std::sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
    if (len > 0.0001f)
    {
        n.x /= len;
        n.y /= len;
        n.z /= len;
    }
    return n;
}

// ------------------ OBJ LOADER ------------------

GLuint LoadOBJToDisplayList(const std::string& objPath, float scale)
{
    std::ifstream f(objPath);
    if (!f.is_open())
    {
        std::cout << "Failed to open OBJ: " << objPath << std::endl;
        return 0;
    }

    std::string baseDir = objPath.substr(0, objPath.find_last_of("/\\") + 1);

    std::vector<SimpleVertex> V;
    std::vector<SimpleTexCoord> T;
    std::vector<SimpleNormal> N;

    struct Face { std::vector<int> v, t, n; std::string mat; };
    std::vector<Face> faces;

    std::map<std::string, Material> materials;
    std::string currentMat;
    std::string line;

    while (std::getline(f, line))
    {
        std::istringstream iss(line);
        std::string tag;
        iss >> tag;

        if (tag == "v")
        {
            SimpleVertex v;
            iss >> v.x >> v.y >> v.z;
            v.x *= scale; v.y *= scale; v.z *= scale;
            V.push_back(v);
        }
        else if (tag == "vt")
        {
            SimpleTexCoord t;
            iss >> t.u >> t.v;
            T.push_back(t);
        }
        else if (tag == "vn")
        {
            SimpleNormal n;
            iss >> n.x >> n.y >> n.z;
            N.push_back(n);
        }
        else if (tag == "usemtl")
        {
            iss >> currentMat;
        }
        else if (tag == "mtllib")
        {
            std::string mtl;
            iss >> mtl;
            ParseMTL(baseDir + mtl, materials);
        }
        else if (tag == "f")
        {
            Face face;
            face.mat = currentMat;

            std::string w;
            while (iss >> w)
            {
                int vi = 0, ti = 0, ni = 0;
                sscanf_s(w.c_str(), "%d/%d/%d", &vi, &ti, &ni);
                face.v.push_back(vi - 1);
                face.t.push_back(ti - 1);
                face.n.push_back(ni - 1);
            }
            faces.push_back(face);
        }
    }

    for (auto& m : materials)
    {
        if (!m.second.map_Kd.empty())
        {
            bool ok;
            m.second.texID = LoadTextureFromFile(baseDir + m.second.map_Kd, ok);
            m.second.hasTexture = ok;
        }
    }

    GLuint list = glGenLists(1);
    glNewList(list, GL_COMPILE);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);

    for (auto& fce : faces)
    {
        auto it = materials.find(fce.mat);
        if (it != materials.end())
        {
            Material& m = it->second;

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m.Ka);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m.Kd);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m.Ks);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m.Ns);

            if (m.hasTexture)
            {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, m.texID);
            }
            else
            {
                glDisable(GL_TEXTURE_2D);
            }
        }

        for (size_t i = 1; i + 1 < fce.v.size(); ++i)
        {
            int i0 = 0, i1 = i, i2 = i + 1;

            SimpleNormal n = ComputeNormal(
                V[fce.v[i0]],
                V[fce.v[i1]],
                V[fce.v[i2]]
            );

            glBegin(GL_TRIANGLES);

            glNormal3f(n.x, n.y, n.z);

            if (fce.t[i0] >= 0)
                glTexCoord2f(T[fce.t[i0]].u, T[fce.t[i0]].v);
            glVertex3f(V[fce.v[i0]].x, V[fce.v[i0]].y, V[fce.v[i0]].z);

            if (fce.t[i1] >= 0)
                glTexCoord2f(T[fce.t[i1]].u, T[fce.t[i1]].v);
            glVertex3f(V[fce.v[i1]].x, V[fce.v[i1]].y, V[fce.v[i1]].z);

            if (fce.t[i2] >= 0)
                glTexCoord2f(T[fce.t[i2]].u, T[fce.t[i2]].v);
            glVertex3f(V[fce.v[i2]].x, V[fce.v[i2]].y, V[fce.v[i2]].z);

            glEnd();

        }
    }

    glDisable(GL_TEXTURE_2D);


    glDisable(GL_TEXTURE_2D);
    glEndList();

    return list;
}
