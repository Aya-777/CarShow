#pragma once
#include <vector>
#include <string>
#include <GL/glut.h>

struct Vec3 {
    float x, y, z;
};

class OBJModel {
private:
    std::vector<Vec3> vertices;
    std::vector<int> indices;

public:
    bool load(const std::string& path);
    void draw();
};
