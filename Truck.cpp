#include "Truck.h"

Truck::Truck(Point position) : wheelUnit(0.3f, 0.7f) {
	this->position = position;
    wheelSpin = 0.0f;
    steerAngle = 0.0f;
    isMovable = false;

    // Calculate wheel positions based on dimensions
    float zOffset = width / 2.0f + 0.2f; // Slightly outside the body
    float groundY = -height / 2.0f;

    // Front Wheels
    wheelPositions[0] = Point(length * 0.4f, groundY, zOffset);
    wheelPositions[1] = Point(length * 0.4f, groundY, -zOffset);

    // Rear Wheels (Grouped at the back)
    wheelPositions[2] = Point(-length * 0.3f, groundY, zOffset);
    wheelPositions[3] = Point(-length * 0.3f, groundY, -zOffset);
    wheelPositions[4] = Point(-length * 0.45f, groundY, zOffset);
    wheelPositions[5] = Point(-length * 0.45f, groundY, -zOffset);
}

void Truck::update() {
    if (isMovable) {
        position.x += 0.005f;
        wheelSpin -= 0.005f;
        if (position.x > 20.0f) position.x = -20.0f;
    }
}

void Truck::draw() {
    glPushMatrix();
    // Move the whole truck to its world position
    glTranslatef(position.x, position.y, position.z);

    // 1. MAIN CHASSIS (The long body)
    glColor3f(0.2f, 0.4f, 0.8f); // Blue
    glPushMatrix();
    glScalef(length, height, width);
    glutSolidCube(1.0);
    glPopMatrix();

    // 2. CABIN (Placed at the front-top)
    glColor3f(0.1f, 0.1f, 0.1f); // Dark Cab
    glPushMatrix();
    // Move to front edge and sit on top of chassis
    glTranslatef(length * 0.35f, height * 0.6f, 0.0f);
    glScalef(length * 0.3f, height, width * 0.95f);
    glutSolidCube(1.0);
    glPopMatrix();

    // 3. WHEELS
    // Apply the current rotation states to the wheel object before drawing
    wheelUnit.spinAngle = wheelSpin;
    wheelUnit.steerAngle = steerAngle;

    for (int i = 0; i < 6; i++) {
        // Wheels 0 and 1 are the front wheels (they steer)
        wheelUnit.draw(wheelPositions[i], (i < 2));
    }
    glPopMatrix();
}