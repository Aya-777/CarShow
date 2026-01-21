#include "MountainHall.h"
#include <GL/freeglut.h>

// Constructor: Initialize both cars
MountainHall::MountainHall()
    : mainCar ( Point(0, 0, 0), false),      // The closed car
    convertibleCar(Point(0, 0, 0), true) // The convertible car
{
}

void MountainHall::draw() {
    GLUquadric* quadric = gluNewQuadric();

    // The correct height for both cars
    float car_Y = 25.0f;

    // --- POSITIONS: SIDE-BY-SIDE ---

    // Both cars will be at the same "depth" inside the hall
    float common_X = 200.0f;

    // We will place them at different Z positions to make them appear "next to each other"
    float car1_Z = 80.0f; // Car 1 (closed) on the right
    float car2_Z = -80.0f; // Car 2 (convertible) on the left


    // --- 1. DRAW THE FIRST CAR (Closed) ---
    mainCar.setPosition(Point(common_X, car_Y, car1_Z));
    mainCar.draw();


    // --- 2. DRAW THE SECOND CAR (Convertible) ---
    convertibleCar.setPosition(Point(common_X, car_Y, car2_Z));
    convertibleCar.draw();


    // --- 3. CLEANUP ---
    gluDeleteQuadric(quadric);
}
