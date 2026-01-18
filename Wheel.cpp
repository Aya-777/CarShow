#include "Wheel.h"

Wheel::Wheel(float width, float radius) {
    this->width = width;
    this->radius = radius;
    this->spinAngle = 0.0f;
    this->steerAngle = 0.0f;
}

void Wheel::draw(Point p, bool canSteer) {
    glPushMatrix();
    glTranslatef(p.x, p.y, p.z);

    // 2. Apply Rotations
    if (canSteer) glRotatef(steerAngle, 0, 1, 0); // Steering
    glRotatef(spinAngle, 0, 0, 1);               // Rolling

    // --- الدولاب ---
    glColor3f(0.05f, 0.05f, 0.05f);
    glutSolidTorus(width, radius, 30, 30);

    // --- الجنط ---
    glColor3f(0.6f, 0.6f, 0.6f); // فضي
    glPushMatrix();
    glScalef(1.0f, 1.0f, 0.2f);
    glutSolidSphere(radius - (width * 0.5f), 20, 20);
    glPopMatrix();

    // --- DRAW SOME DETAIL ---
    glColor3f(0.3f, 0.3f, 0.3f);
    for (int i = 0; i < 360; i += 60) {
        glPushMatrix();
        glRotatef((float)i, 0, 0, 1);
        glTranslatef(radius * 0.4f, 0, 0.1f);
        glutSolidSphere(radius/5, 10, 10);
        glPopMatrix();
    }

    glPopMatrix();
}