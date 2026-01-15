#include "Truck.h"
#include "Cuboid.h"
#include "Glass.h"
//#include "Model_3DS.h"
#include "Texture.h"


//Model_3DS armChair;
//GlTexture
//GLTexture armChairTexture;

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

void load() {
	//armChair = Model_3DS();
	//armChair.Load("Models / ArmChair / Armchair car N220417.3DS");
	//armChairTexture.
}
void Truck::update() {
    if (isMovable) {
        // "Forward" direction math (Assuming X is forward)
        // Convert degrees to radians for cos/sin
        float rad = rotationAngle * (3.14159f / 180.0f);

        // Move position based on current heading
        position.x += cos(rad) * 0.5f;
        position.z -= sin(rad) * 0.5f;

        // Roll the wheels based on movement
        wheelSpin -= 5.0f;

        // Update truck heading based on steering (The truck turns while moving)
        // If steerAngle is positive, truck turns left; negative, truck turns right.
        rotationAngle += (steerAngle * 0.1f);
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
    glRotatef(rotationAngle, 0, 1, 0);
    // --- 1. MAIN CONTAINER ---
    glColor3f(0.2f, 0.4f, 0.8f);
    float containerLengthX = length * 0.7f;
    Cuboid container(Point(-length * 0.15f, 0, 0), height, width, containerLengthX);
    container.draw();

    // --- 2. CABIN SETUP ---
    float cabL = length * 0.3f;
    float cabH = height * 0.8f;
    float cabW = width * 0.9f;
    float thickness = 0.5f;
    float cabXOffset = length * 0.35f;

    glPushMatrix();
        glTranslatef(cabXOffset, 0, 0);

        glColor3f(0.7f, 0.0f, 0.0f);
        Cuboid cabFloor(Point(0, 0, 0), thickness, cabW, cabL);
        cabFloor.draw();

        Cuboid leftWall(Point(0, 0, -cabW / 2), cabH, thickness, cabL);
        leftWall.draw();

        glPushMatrix();
            //glColor3f(0.1,0.8,0.1);
            Glass leftGlass(Point(0, cabH / 2, -cabW/2 - 0.8), cabH/5, thickness, cabL/2);
            leftGlass.draw(0.1, 0.8, 0.1, 0.5);
        glPopMatrix();

        glColor3f(0.7f, 0.0f, 0.0f);
        Cuboid rightWall(Point(0, 0, cabW / 2), cabH, thickness, cabL);
        rightWall.draw();

        glPushMatrix();
            //glColor3f(0.1, 0.8, 0.1);
            Glass rightGlass(Point(0, cabH / 2, cabW / 2 + 0.1), cabH / 5, thickness, cabL / 2);
            rightGlass.draw(0.1, 0.8, 0.1, 0.5);
        glPopMatrix();

        Cuboid roof(Point(0, cabH, 0), thickness, cabW, cabL);
        roof.draw();

        glColor3f(0.2f, 0.2f, 0.2f);
        float seatSize = cabL * 0.3f;

        Cuboid seat1(Point(-cabL / 4, thickness, -cabW * 0.25f), seatSize / 2, seatSize, seatSize);
        seat1.draw();
        Cuboid back1(Point(-cabL / 4 - seatSize / 2, thickness, -cabW * 0.25f), seatSize * 1.5, seatSize, thickness);
        back1.draw();

        Cuboid seat2(Point(-cabL / 4, thickness, cabW * 0.25f), seatSize / 2, seatSize, seatSize);
        seat2.draw();
        Cuboid back2(Point(-cabL / 4 - seatSize / 2, thickness, cabW * 0.25f), seatSize * 1.5, seatSize, thickness);
        back2.draw();


        glColor3f(0.1f, 0.6f, 0.1f);
        Cuboid tablwo(Point(cabL / 2.3, 0, 0), cabH / 3, cabW, thickness * 5);
        tablwo.draw();

        float topWallH = cabH / 5.0f;
        glColor3f(0.8f, 0.1f, 0.1f);
        Cuboid frontWall(Point(cabL / 2.0f, cabH - topWallH, 0), topWallH, cabW, thickness);
        frontWall.draw();
        float glassH = cabH - cabH / 3.0f - topWallH;

        Glass frontGlass(Point(cabL / 2.0f, cabH / 3.0f, 0), glassH, cabW, thickness);
        frontGlass.draw(0.1f, 0.8f, 1.0f, 0.8f);

    glPopMatrix();

    // --- 3. BACK DOORS ---
    glColor3f(0.1f, 0.1f, 0.1f);
    float doorWidth = width * 0.5f;

    glPushMatrix(); // Left
    glTranslatef(-length * 0.5f, 0, -width * 0.5f);
    glRotatef(-doorAngle, 0, 1, 0);
    Cuboid leftDoor(Point(0, 0, doorWidth / 2.0f), height, doorWidth, 0.1f);
    leftDoor.draw();
    glPopMatrix();

    glPushMatrix(); // Right
        glTranslatef(-length * 0.5f, 0, width * 0.5f);
        glRotatef(doorAngle, 0, 1, 0);
        Cuboid rightDoor(Point(0, 0, -doorWidth / 2.0f), height, doorWidth, 0.1f);
        rightDoor.draw();
    glPopMatrix();

    // --- 4. WHEELS ---
    wheelUnit.spinAngle = wheelSpin;
    wheelUnit.steerAngle = this->steerAngle;
    for (int i = 0; i < 6; i++) {
        wheelUnit.draw(wheelPositions[i], (i < 2));
    }

    glPopMatrix();
}