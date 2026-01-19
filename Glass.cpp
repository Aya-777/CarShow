#include "Glass.h"

Glass::Glass(Point center, double height, double width, double length) {
    this->center = center;
    this->height = height;
    this->width = width;
    this->length = length;
}

void Glass::draw(float r, float g, float b, float alpha) {
    glEnable(GL_BLEND);
    // This blend function is the "standard" for real glass
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set the color with Alpha (0.3 is usually good for glass)
    glColor4f(r, g, b, alpha);

    // We reuse the geometry logic from your Cuboid
    // Draw Front face
    glBegin(GL_QUADS);
    glVertex3d(center.x - length / 2, center.y, center.z + width / 2);
    glVertex3d(center.x + length / 2, center.y, center.z + width / 2);
    glVertex3d(center.x + length / 2, center.y + height, center.z + width / 2);
    glVertex3d(center.x - length / 2, center.y + height, center.z + width / 2);
    glEnd();

    // ... (You can add the other 5 faces here similar to Cuboid.cpp)

    glDisable(GL_BLEND);
}