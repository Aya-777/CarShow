#include "Truck.h"
#include "Cuboid.h"

Truck::Truck(Point position) : wheelUnit(this->height * 0.08f, this->height * 0.2f) {
    this->position = position;

	doorAngle = 0.0f;
    doorsOpen = false;
    wheelSpin = 0.0f;
    steerAngle = 0.0f;
    isMovable = false;

    // Calculate wheel
    float zOffset = width / 2.0f;
    float groundY = 0;

    // Front Wheels
    wheelPositions[0] = Point(length * 0.35f, groundY, zOffset);
    wheelPositions[1] = Point(length * 0.35f, groundY, -zOffset);

    // back Wheels
    wheelPositions[2] = Point(-length * 0.15f, groundY, zOffset);
    wheelPositions[3] = Point(-length * 0.15f, groundY, -zOffset);
    wheelPositions[4] = Point(-length * 0.35f, groundY, zOffset);
    wheelPositions[5] = Point(-length * 0.35f, groundY, -zOffset);
}

void Truck::update() {
    if (isMovable) {
        position.x += 0.5f;
        wheelSpin -= 1.0f;
        if (position.x > 1000.0f) position.x = -1000.0f;
    }

    if (doorsOpen) {
        if (doorAngle < 90.0f) doorAngle += 0.2f;
    }
    else {
        if (doorAngle > 0.0f) doorAngle -= 0.2f;
    }
}

void Truck::draw() {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);

    // 1. MAIN CONTAINER
    glColor3f(0.2f, 0.4f, 0.8f);
    float containerLengthX = length * 0.7f;
    Cuboid container(Point(-length * 0.15f, 0, 0), height, width, containerLengthX);
    container.draw();

    glColor3f(0.8f, 0.1f, 0.1f);
    float cabLengthX = length * 0.3f;
    Cuboid cabin(Point(length * 0.35f, 0, 0), height * 0.8f, width * 0.9f, cabLengthX);
    cabin.draw();

    // 3. BACK DOORS
    glColor3f(0.1f, 0.1f, 0.1f); // Black
    float doorWidth = width * 0.5f;

    // --- LEFT DOOR ---
    glPushMatrix();
        glTranslatef(-length * 0.5f, 0, -width * 0.5f);
        glRotatef(-doorAngle, 0, 1, 0);
        Cuboid leftDoor(Point(0, 0, doorWidth / 2.0f), height, doorWidth, 0.1f);
        leftDoor.draw();
    glPopMatrix();

    // --- RIGHT DOOR ---
    glPushMatrix();
        glTranslatef(-length * 0.5f, 0, width * 0.5f);
        glRotatef(doorAngle, 0, 1, 0);
        Cuboid rightDoor(Point(0, 0, -doorWidth / 2.0f), height, doorWidth, 0.1f);
        rightDoor.draw();
    glPopMatrix();

    // WHEELS
    wheelUnit.spinAngle = wheelSpin;
    for (int i = 0; i < 6; i++) {
        wheelUnit.draw(wheelPositions[i], (i < 2));
    }

    glPopMatrix();
}