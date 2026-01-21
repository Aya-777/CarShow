#pragma once
#include "Point.h"

//
// MountainCar Class
// Can now render both a closed and a convertible (open-top) version.
//
class MountainCar {
public:
    // Constructor now accepts a 'convertible' flag. Defaults to false (closed).
    MountainCar(Point position = Point(0, 0, 0), bool convertible = false);

    void draw();
    void setPosition(Point newPosition);

private:
    Point pos;
    bool isConvertible; // Flag to check if the car should be drawn without a roof.
};
