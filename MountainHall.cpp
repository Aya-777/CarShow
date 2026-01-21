#include "MountainHall.h"
#include <GL/freeglut.h>

// -----------------------------------------------------------------------------
// CONSTRUCTOR
// - The car's initial position is a placeholder; it will be set dynamically
//   in the draw() function to ensure it's always centered.
// -----------------------------------------------------------------------------
MountainHall::MountainHall() : mainCar(Point(0, 0, 0)) , secondCar(Point(0,100,0)) {
}

// -----------------------------------------------------------------------------
// DRAW FUNCTION
// - Draws the circular platform and the car on top of it.
// -----------------------------------------------------------------------------
void MountainHall::draw() {
    // --- 1. SETUP ---
    GLUquadric* quadric = gluNewQuadric();

    // --- 2. CALCULATE CENTER POSITION ---
    // These coordinates place the display in the center of the 2nd showroom hall.
    // X = 50 moves it "back" into the hall, away from the entrance.
    float hallCenterX = 230.0f;
    // Z = 45 is the horizontal center of the 2nd hall space.
    float hallCenterZ = 45.0f;

    //// --- 3. DRAW THE PLATFORM ---
    //glPushMatrix();
    //glTranslatef(hallCenterX, -2.0, hallCenterZ);
    //glRotatef(-90, 1, 0, 0);

    //glColor3f(0.25f, 0.25f, 0.28f); // Darker color for the sides
    //gluCylinder(quadric, 75, 75, 5, 64, 1);

    //glColor3f(0.35f, 0.35f, 0.38f); // Lighter color for the top surface
    //glPushMatrix();
    //glTranslatef(0, 0, 5);
    //gluDisk(quadric, 0, 75, 64, 1);
    //glPopMatrix();
    //glPopMatrix();

    // --- 4. DRAW THE CAR ---
    // Set the car's position to be exactly on top of the platform
    // Y = 33.0 is the calculated height to make the wheels touch the surface.
    mainCar.setPosition(Point(hallCenterX, 20.0, hallCenterZ));
    mainCar.draw();

    // --- 5. CLEANUP ---
    gluDeleteQuadric(quadric);
}
