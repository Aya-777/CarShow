#pragma once
#include "Point.h"

struct AABB {
    Point min;
    Point max;

    bool intersects(const AABB& o);
};
