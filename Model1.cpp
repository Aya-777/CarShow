#include "Model1.h"
#include <fstream>
#include <sstream>

bool OBJModel::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        return false;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v") {
            Vec3 v;
            ss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        }
        else if (type == "f") {
            int a, b, c;
            ss >> a >> b >> c;
            indices.push_back(a - 1);
            indices.push_back(b - 1);
            indices.push_back(c - 1);
        }
    }

    return true;
}

void OBJModel::draw() {
    glBegin(GL_TRIANGLES);
    for (int idx : indices) {
        Vec3 v = vertices[idx];
        glVertex3f(v.x, v.y, v.z);
    }
    glEnd();
}
