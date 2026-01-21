#include "Truck.h"
#include "Cuboid.h"
#include "Glass.h"
#include "Texture.h"
#include "Window.h"
#include <mmsystem.h>
#include <iostream>
#pragma comment(lib, "winmm.lib")
using namespace std;
extern std::vector<Door*> globalDoors;


Truck::Truck(Point position) : wheelUnit(this->height * 0.08f, this->height * 0.2f) {
    this->position = position;

    wheelSpin = 0.0f;
    steerAngle = 0.0f;
    isMovable = false;

    globalDoors.push_back(&this->driverDoor);
    globalDoors.push_back(&this->passengerDoor);
    globalDoors.push_back(&this->backDoors);

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

void Truck::load() {
    bool success = driverSteeringWheel.Load("resources/models/steeringWheel/steering_wheel.obj", 15.0f);

    if (success) {
        driverSteeringWheel.SetPosition(-5.0f, -13.0f, -4.0f);
        driverSteeringWheel.SetRotationY(300.0f);
        driverSteeringWheel.SetRotationZ(-15.0f);
        driverSteeringWheel.Draw();
    }
    else {
        printf("Truck failed to load Steering Wheel OBJ!\n");
    }
}
void Truck::update() {

    float rad = rotationAngle * (3.14159f / 180.0f);

    // --- DRIVER DOOR POSITION ---
    float drvLocalX = length * 0.35f;
    float drvLocalZ = -width * 0.5f;

    // Standard Rotation Formula (No flipping!)
    driverDoor.center.x = position.x + (drvLocalX * cos(rad) - drvLocalZ * sin(rad));
    driverDoor.center.y = position.y + (height * 0.5f);
    driverDoor.center.z = position.z + (drvLocalX * sin(rad) + drvLocalZ * cos(rad));

    // --- PASSENGER DOOR POSITION ---
    float psgLocalX = length * 0.35f;
    float psgLocalZ = width * 0.5f; // Positive Z for right side
    passengerDoor.center.x = position.x + (psgLocalX * cos(rad) - psgLocalZ * sin(rad));
    passengerDoor.center.y = position.y + (height * 0.5f);
    passengerDoor.center.z = position.z + (psgLocalX * sin(rad) + psgLocalZ * cos(rad));

    // --- PASSENGER DOOR ANIMATION ---
    if (passengerDoor.open) {
        if (passengerDoor.OpenRate < 80.0f) passengerDoor.OpenRate += 0.2f;
    }
    else {
        if (passengerDoor.OpenRate > 0.0f) passengerDoor.OpenRate -= 0.2f;
    }
    // --- BACK DOORS POSITION ---
    float backLocalX = -length * 0.5f;
    float backLocalZ = 0.0f;

    backDoors.center.x = position.x + (backLocalX * cos(rad) - backLocalZ * sin(rad));
    backDoors.center.y = position.y + (height * 0.5f);
    backDoors.center.z = position.z + (backLocalX * sin(rad) + backLocalZ * cos(rad));


    if (isMovable) {

        // Move position based on current heading
        position.x += cos(rad) * 0.8f;
        position.z -= sin(rad) * 0.8f;

        // Roll the wheels based on movement
        wheelSpin -= 5.0f;
        rotationAngle += (steerAngle * 0.1f);
    }
    if (driverDoor.open) {
		if (driverDoor.OpenRate < 80.0f) driverDoor.OpenRate += 0.2f;
    }
    else {
        if (driverDoor.OpenRate > 0.0f) driverDoor.OpenRate -= 0.2f;
    }

    if (backDoors.open) {
        if (backDoors.OpenRate < 90.0f) backDoors.OpenRate += 0.2f;
    }
    else {
        if (backDoors.OpenRate > 0.0f) backDoors.OpenRate -= 0.2f;
    }

    
}
void drawLightCircle(float radius, int segments, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    // The center point of the circle
    glVertex3f(0.0f, 0.0f, 0.0f);

    for (int i = 0; i <= segments; i++) {
        float angle = i * 2.0f * 3.14159f / segments;
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;
        glVertex3f(x, y, 0.0f);
    }
    glEnd();

    //Add a small white "glow" dot in the center
    glColor3f(1.0f, 0.9f, 0.9f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.01f);
    for (int i = 0; i <= segments; i++) {
        float angle = i * 2.0f * 3.14159f / segments;
        glVertex3f(cos(angle) * radius * 0.3f, sin(angle) * radius * 0.3f, 0.01f);
    }
    glEnd();
}
void Truck::playMusic(Point cameraPos) {
    cout << "in play sound" << endl;
    // 1. Calculate distance between camera and truck
    float dx = position.x - cameraPos.x;
    float dy = position.y - cameraPos.y;
    float dz = position.z - cameraPos.z;
    float distance = sqrt(dx * dx + dy * dy + dz * dz);
    cout << "to play music: " << distance << endl;
    // 2. Only play if the camera is close enough (500 units)
    if (distance < 500.0f) {
        // Play sound (SND_ASYNC prevents the game from freezing)
        PlaySoundA(this->musicSoundPath, NULL, SND_FILENAME | SND_ASYNC);

        // 3. Visual Flash Effect
        // We draw extra bright white circles over the lights for one frame
        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glRotatef(rotationAngle, 0, 1, 0);

        // Front position offset (same as your front lights)
        glTranslatef(length * 0.5f + 0.1f, -0.5f, 0.0f);
        glRotatef(-90, 0, 1, 0);

        // Draw bright white "flash" circles
        drawLightCircle(1.3f, 20, 1.0f, 1.0f, 1.0f); // Slightly larger than normal
        glPopMatrix();
    }
}


void Truck::draw(float r, float g, float b) {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotationAngle, 0, 1, 0);
    // --- 1. MAIN CONTAINER ---
    glColor3f(r - 0.1, g - 0.1, b - 0.1);
    float containerLengthX = length * 0.7f;
    Cuboid container(Point(-length * 0.15f, 0, 0), height, width, containerLengthX);
    container.draw();
    Window leftFramec(Point(-length * 0.15f, 0, width/2), 1, containerLengthX + 1, height, 0.75, 0.75, 0.75, 0.75, false);
    leftFramec.draw(0.2, 0.2, 0.2);
    Window rightFramec(Point(-length * 0.15f, 0, -width / 2), 1, containerLengthX + 1, height, 0.75, 0.75, 0.75, 0.75, false);
    rightFramec.draw(0.2, 0.2, 0.2);
    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        Window topFramec(Point(-length/6.8, -width/2, -height), 1, containerLengthX + 1, height, 0.75, 0.75, 0.75, 0.75, false);
        topFramec.draw(0.2, 0.2, 0.2);
    glPopMatrix();


    glColor3f(0.2, 0.2, 0.2);
    Cuboid floorb(Point(0, -1, 0), 1, width, length+1);
    floorb.draw();
    Cuboid ending(Point(-length/1.9, -1, 0), height/6, width, length/20);
    ending.draw();

    // --- 2. CABIN SETUP ---
    float cabL = length * 0.3f;
    float cabH = height * 0.8f;
    float cabW = width * 0.9f;
    float thickness = 0.5f;
    float cabXOffset = length * 0.35f;

    glPushMatrix();
        glTranslatef(cabXOffset, 0, 0);

        glColor3f(r, g, b);
        Cuboid cabFloor(Point(0, 0, 0), thickness, cabW, cabL);
        cabFloor.draw();

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

        glPushMatrix();
            glTranslatef(cabL / 2.3, 20, 0);
            glRotatef(rotationAngle, 0, 1, 0);
            driverSteeringWheel.Draw();
        glPopMatrix();


        glColor3f(0.2f, 0.2f, 0.2f);
        Cuboid tablwo(Point(cabL / 2.3, 0, 0), cabH / 3, cabW, thickness * 5);
        tablwo.draw();
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        Window topFrame(Point(0, -cabW / 2-0.75, -cabH-0.5), 1, cabL+1, cabW+1.5, 0.75, 0.75, 0.75, 0.75, false);
        topFrame.draw(0.2, 0.2, 0.2);
        glPopMatrix();

        glPushMatrix();
        Window leftWall(Point(0, 0, -cabW / 2), thickness, cabL, cabH, cabH / 3, cabH / 6, cabL / 6, cabL / 6, false);
        leftWall.draw(r, g, b);
        Window leftFrame(Point(0, 0, -cabW / 2-0.5), thickness, cabL+1, cabH, 0, cabH/18, cabL/18, cabL/18, false);
        leftFrame.draw(0.2, 0.2, 0.2);
        // driver door
        glPushMatrix();
        float doorLen = cabL - cabL / 3;
        glTranslatef(doorLen / 2, cabH / 3, -cabW / 2);

        glRotatef(-driverDoor.OpenRate, 0, 1, 0);

        glTranslatef(-doorLen / 2, 0, 0);
        glPushMatrix();
        glTranslatef(doorLen / 3.5, cabH / 4, -doorLen / 5);
        glRotatef(50+90, 0, 1, 0);
        Window leftMirror(Point(0,0,0), thickness, doorLen / 5, cabH / 8, 0.1, 0.1, 0.5, 0.1, true);
        leftMirror.draw(0.2, 0.2, 0.2);
        Window leftMirrorb(Point(0, 0, 0.5), thickness, doorLen / 5, cabH / 8, 2, 2, 2, 2, true);
        leftMirrorb.draw(0.2, 0.2, 0.2);
        glPopMatrix();
        Window driverDoorWindow(Point(0, 0, 0), thickness, doorLen, cabH - cabH / 2,cabH / 6, cabH / 20, cabL / 6, cabL / 20, true);
        driverDoorWindow.draw(r-0.1,g-0.1,b-0.1);
        glPopMatrix();
        glPopMatrix();


        glPushMatrix();
        Window rightWall(Point(0, 0, cabW / 2), thickness, cabL, cabH, cabH / 3, cabH / 6, cabL / 6, cabL / 6, false);
        rightWall.draw(r,g,b);
        Window rightFrame(Point(0, 0, cabW / 2 + 0.5), thickness, cabL+1, cabH, 0, cabH / 18, cabL / 18, cabL / 18, false);
        rightFrame.draw(0.2, 0.2, 0.2);

        // --- PASSENGER DOOR (RIGHT SIDE) ---
        glPushMatrix();
        glTranslatef(doorLen / 2, cabH / 3, cabW / 2);
        glRotatef(passengerDoor.OpenRate, 0, 1, 0);
        glTranslatef(-doorLen / 2, 0, 0);
        glPushMatrix();
        glTranslatef(doorLen / 4, cabH / 4, doorLen / 5);
        glRotatef(50, 0, 1, 0);
        Window rightMirror(Point(0, 0, 0), thickness, doorLen / 5, cabH / 8, 0.1, 0.1, 0.5, 0.1, true);
        rightMirror.draw(0.2, 0.2, 0.2);
        Window rightMirrorb(Point(0, 0, 0.5), thickness, doorLen / 5, cabH / 8, 2, 2, 2, 2, true);
        rightMirrorb.draw(0.2, 0.2, 0.2);
        glPopMatrix();

        Window passengerDoorWindow(Point(0, 0, 0), thickness, doorLen, cabH - cabH / 2, cabH / 6, cabH / 20, cabL / 6, cabL / 20, true);
        passengerDoorWindow.draw(r - 0.1, g - 0.1, b - 0.1);
        glPopMatrix();

        glPopMatrix();

        glPushMatrix();
        glRotatef(90, 0, 90, 0);
        Window frontWall(Point(0, 0, cabL / 2), thickness, cabW, cabH, cabH/3, cabH / 6, cabL / 6, cabL / 6, true);
        frontWall.draw(r,g,b);
        Cuboid nmra(Point(0, 1, cabL / 2), height / 8, 1, width * 0.5);
        nmra.draw();
        Window frontFrame(Point(0, 0, cabL/2+ 0.5), thickness, cabL+2, cabH, 0, cabH / 20, cabL / 20, cabL / 20, false);
        frontFrame.draw(0.2, 0.2, 0.2);
        glPopMatrix();

    glPopMatrix();

    // --- 3. BACK DOORS ---
    glColor3f(0.2f, 0.2f, 0.2f);
    float doorWidth = width * 0.5f-0.6;

    glPushMatrix(); // Left
    glTranslatef(-length * 0.5f, 0, -width * 0.5f);
    glRotatef(-backDoors.OpenRate, 0, 1, 0);
    Cuboid leftDoor(Point(0, height / 7, doorWidth / 2.0f+0.4), height-height/5, doorWidth, 0.1f);
    leftDoor.draw();
    glPopMatrix();

    glPushMatrix(); // Right
        glTranslatef(-length * 0.5f, 0, width * 0.5f);
        glRotatef(backDoors.OpenRate, 0, 1, 0);
        Cuboid rightDoor(Point(0, height / 7, -doorWidth / 2.0f-0.4), height - height / 5, doorWidth, 0.1f);
        rightDoor.draw();
    glPopMatrix();

    // --- 4. WHEELS ---
    wheelUnit.spinAngle = wheelSpin;
    wheelUnit.steerAngle = this->steerAngle;
    for (int i = 0; i < 6; i++) {
        wheelUnit.draw(wheelPositions[i], (i < 2));
    }

    // --- REAR CIRCLE LIGHTS --- back
    glPushMatrix();
    glTranslatef(-length / 1.88f, -0.5f, 0.0f);
    glRotatef(90, 0, 1, 0);

    // Left Red Light
    glPushMatrix();
    glTranslatef(-width / 3.0f, 1.5, -1.5);
    drawLightCircle(1.2f, 20, 1.0f, 0.0f, 0.0f);
    glPopMatrix();

    // Right Red Light
    glPushMatrix();
    glTranslatef(width / 3.0f, 1.5, -1.5f);
    drawLightCircle(1.2f, 20, 1.0f, 0.0f, 0.0f);
    glPopMatrix();
    glPopMatrix();


    // --- REAR CIRCLE LIGHTS --- front
    glPushMatrix();
    glTranslatef(-length / 1.88f, -0.5f, 0.0f);
    glRotatef(90, 0, 1, 0);

    // Left Red Light
    glPushMatrix();
    glTranslatef(-width / 3.0f, 3, length+3);
    drawLightCircle(1.0f, 20, 1.0f, 0.0f, 0.0f);
    glPopMatrix();

    // Right Red Light
    glPushMatrix();
    glTranslatef(width / 3.0f, 3, length + 3);
    drawLightCircle(1, 20, 1.0f, 0.0f, 0.0f);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();

}
