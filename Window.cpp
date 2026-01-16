#include "Window.h"
#include "Cuboid.h"
#include "Glass.h"

Window::Window(Point pos, float l, float w, float h, float gapBottom, float gapTop, float gapLeft, float gapRight, bool hasGlass) {
    this->pos = pos;
    this->l = l;
    this->w = w;
    this->h = h;
    this->gapBottom = gapBottom;
    this->gapTop = gapTop;
    this->gapLeft = gapLeft;
    this->gapRight = gapRight;
    this->hasGlass = hasGlass;
}

void Window::draw(float r, float g, float b) {
    glPushMatrix();

    // --- 1. BOTTOM FRAME ---
    glColor3f(r, g, b);
    Cuboid bottom(pos, gapBottom, l, w);
    bottom.draw();

    // --- 2. TOP FRAME ---
    Point topPos(pos.x, pos.y + h - gapTop, pos.z);
    Cuboid top(topPos, gapTop, l, w);
    top.draw();

    // --- 3. LEFT FRAME ---
    Point leftPos(pos.x - w / 2 + gapLeft / 2, pos.y + gapBottom, pos.z);
    Cuboid left(leftPos, h - gapBottom - gapTop, l, gapLeft);
    left.draw();

    // --- 4. RIGHT FRAME ---
    Point rightPos(pos.x + w / 2 - gapRight / 2, pos.y + gapBottom, pos.z);
    Cuboid right(rightPos, h - gapBottom - gapTop, l, gapRight);
    right.draw();

    // --- 5. GLASS ---
    if (hasGlass) {
        float innerH = h - gapBottom - gapTop;
        float innerW = w - gapLeft - gapRight;

        // Center the glass in the remaining hole
        Point glassPos(pos.x + (gapLeft - gapRight) / 2.0f, pos.y + gapBottom, pos.z);
        Glass glassPane(glassPos, innerH, l * 0.1f, innerW);
        glassPane.draw(glassR, glassG, glassB, 0.4f);
    }

    glPopMatrix();
}