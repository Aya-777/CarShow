#pragma once
#include "MountainCar.h"

//
// MountainHall Class (Your Section)
// This class is responsible for drawing your specific section of the showroom.
// It creates and manages the main car and the platform it sits on.
//
class MountainHall {
public:
    // Constructor
    MountainHall();
    // Main draw function for the hall
    void draw();
private:
    // The hall "owns" an instance of the MountainCar
    MountainCar mainCar;
};
