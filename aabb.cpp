#include "aabb.h"
#include "Window.h"

bool AABB::intersects(const AABB& o)
{
    return (min.x <= o.max.x && max.x >= o.min.x) &&
        (min.y <= o.max.y && max.y >= o.min.y) &&
        (min.z <= o.max.z && max.z >= o.min.z);
}
