#include "Truck.h"
#include "Cuboid.h"
#include "Glass.h"
#include "Texture.h"
#include "Window.h"
extern std::vector<Door*> globalDoors;


Truck::Truck(Point position) : wheelUnit(this->height * 0.08f, this->height * 0.2f) {
    this->position = position;

    wheelSpin = 0.0f;
    steerAngle = 0.0f;
    isMovable = false;

    globalDoors.push_back(&this->driverDoor);
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
    bool success = driverSteeringWheel.Load("debug/resources/models/steeringWheel/steering_wheel.obj", 15.0f);

    if (success) {
        driverSteeringWheel.SetPosition(0.5f, 2.5f, 1.2f);
        driverSteeringWheel.SetRotationY(180.0f);
        driverSteeringWheel.SetRotationZ(-15.0f);
    }
    else {
        printf("Truck failed to load Steering Wheel OBJ!\n");
    }
}
void Truck::update() {

    float rad = rotationAngle * (3.14159f / 180.0f);

    // --- DRIVER DOOR POSITION ---
    // In your draw(), the cabin is at cabXOffset (Forward X) 
    // and the door is at -cabW/2 (Z side)
    float drvLocalX = length * 0.35f;
    float drvLocalZ = -width * 0.5f;

    // Standard Rotation Formula (No flipping!)
    driverDoor.center.x = position.x + (drvLocalX * cos(rad) - drvLocalZ * sin(rad));
    driverDoor.center.y = position.y + (height * 0.5f);
    driverDoor.center.z = position.z + (drvLocalX * sin(rad) + drvLocalZ * cos(rad));

    // --- BACK DOORS POSITION ---
    float backLocalX = -length * 0.5f;
    float backLocalZ = 0.0f;

    backDoors.center.x = position.x + (backLocalX * cos(rad) - backLocalZ * sin(rad));
    backDoors.center.y = position.y + (height * 0.5f);
    backDoors.center.z = position.z + (backLocalX * sin(rad) + backLocalZ * cos(rad));


    if (isMovable) {

        // Move position based on current heading
        position.x += cos(rad) * 0.5f;
        position.z -= sin(rad) * 0.5f;

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

        Window driverDoorWindow(Point(0, 0, 0), thickness, doorLen, cabH - cabH / 2,cabH / 6, cabH / 20, cabL / 6, cabL / 20, true);
        driverDoorWindow.draw(r-0.1,g-0.1,b-0.1);
        glPopMatrix();
        glPopMatrix();


        glPushMatrix();
        Window rightWall(Point(0, 0, cabW / 2), thickness, cabL, cabH, cabH / 3, cabH / 6, cabL / 6, cabL / 6, false);
        rightWall.draw(r,g,b);
        Window rightFrame(Point(0, 0, cabW / 2 + 0.5), thickness, cabL+1, cabH, 0, cabH / 18, cabL / 18, cabL / 18, false);
        rightFrame.draw(0.2, 0.2, 0.2);
        Window door2(Point(0, cabH / 3, cabW / 2), thickness, cabL - cabL / 3, cabH - cabH / 2, cabH / 6, cabH / 20, cabL / 6, cabL / 20, true);
        door2.draw(r - 0.1, g - 0.1, b - 0.1);
        glPopMatrix();

        glPushMatrix();
        glRotatef(90, 0, 90, 0);
        Window frontWall(Point(0, 0, cabL / 2), thickness, cabW, cabH, cabH/3, cabH / 6, cabL / 6, cabL / 6, true);
        frontWall.draw(r,g,b);
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

    glPopMatrix();

}