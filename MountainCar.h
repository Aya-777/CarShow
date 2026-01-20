#pragma once
#include "Point.h"

//
// MountainCar Class
// This class defines the structure and behavior of the main G-Wagon style car.
// It handles its own drawing, details, and position.
//
class MountainCar {
public:
    // Constructor: Initializes the car at a specific position.
    MountainCar(Point position);

    // draw: The main function that renders all parts of the car.
    void draw();

    // setPosition: A public "setter" function to safely update the car's private position.
    void setPosition(Point newPosition);

private:
    // The car's current position in the 3D world.
    Point pos;
};
