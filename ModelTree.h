#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glut.h>

struct Point3D { float x, y, z; };
struct Point2D { float u, v; };

struct VertexIdx {
    int vIndex;
    int tIndex;
};

struct SubMesh {
    std::vector<std::vector<VertexIdx>> faces;
};

class SmartTreeModel {
    std::vector<Point3D> vertices;
    std::vector<Point2D> texCoords;
    std::vector<SubMesh> meshes;

public:
    void loadOBJ(const char* filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            printf("❌ ERROR: File NOT Found: %s\n", filename);
            return;
        }

        printf("📂 Opening File: %s ...\n", filename);

        meshes.push_back({});

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string prefix;
            ss >> prefix;

            if (prefix == "v") {
                Point3D p; ss >> p.x >> p.y >> p.z;
                vertices.push_back(p);
            }
            else if (prefix == "vt") {
                Point2D t; ss >> t.u >> t.v;
                texCoords.push_back(t);
            }
            else if (prefix == "usemtl" || prefix == "g") {

                if (!meshes.back().faces.empty()) {
                    meshes.push_back({});
                    printf("🔹 New Part Detected (Total: %d)\n", meshes.size());
                }
            }
            else if (prefix == "f") {
                std::vector<VertexIdx> face;
                std::string segment;
                while (ss >> segment) {
                    VertexIdx vIdx;
                    std::stringstream segmentSS(segment);
                    std::string temp;

                    std::getline(segmentSS, temp, '/');
                    vIdx.vIndex = std::stoi(temp) - 1;

                    if (std::getline(segmentSS, temp, '/')) {
                        if (!temp.empty()) vIdx.tIndex = std::stoi(temp) - 1;
                        else vIdx.tIndex = -1;
                    }
                    face.push_back(vIdx);
                }
                meshes.back().faces.push_back(face);
            }
        }
        printf("✅ Loaded! Total Parts: %d\n", meshes.size());
    }

    void draw(float scale, GLuint part1_Tex, GLuint part2_Tex) {
        glEnable(GL_TEXTURE_2D);
        glColor3f(1, 1, 1);

        for (size_t i = 0; i < meshes.size(); i++) {

            if (i == 0) glBindTexture(GL_TEXTURE_2D, part1_Tex);
            else glBindTexture(GL_TEXTURE_2D, part2_Tex);

            for (auto& face : meshes[i].faces) {
                glBegin(GL_POLYGON);
                for (auto& idx : face) {
                    if (idx.tIndex >= 0 && idx.tIndex < texCoords.size())
                        glTexCoord2f(texCoords[idx.tIndex].u, texCoords[idx.tIndex].v);

                    if (idx.vIndex < vertices.size())
                        glVertex3f(vertices[idx.vIndex].x * scale, vertices[idx.vIndex].y * scale, vertices[idx.vIndex].z * scale);
                }
                glEnd();
            }
        }
        glDisable(GL_TEXTURE_2D);
    }
};