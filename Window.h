#pragma once
#include "Point.h"
#include <GL/glut.h>

class Window {
public:
    Point pos;
    float l, w, h; // l = thickness, w = width, h = height
    float gapBottom, gapTop, gapLeft, gapRight;
    bool hasGlass;
    float glassR = 0.5f, glassG = 0.8f, glassB = 0.9f, glassAlpha = 0.5f;
    double OpenRate = 0.0;
    bool isOpen = false;

    Window(Point pos, float l, float w, float h, float gapBottom, float gapTop, float gapLeft, float gapRight, bool hasGlass);
    void draw(float r, float g, float b);
    void drawMovingWindow(float r, float g, float b);
    void openWindow();
};