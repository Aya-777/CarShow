#pragma once
#include "Cuboid.h"
#include "Point.h"

class Bureau
{
private:
    Cuboid body;

public:
    Bureau(Point center);
    void draw();
    void drawItems();
};
