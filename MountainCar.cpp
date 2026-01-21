#include "MountainCar.h"
#include <GL/freeglut.h>

// HELPER FUNCTION to draw a complete wheel
void drawWheelWithRim(GLUquadric* quadric) {
    glColor3f(0.05f, 0.05f, 0.05f);
    glPushMatrix();
    glPushMatrix();
    glRotatef(180, 0, 1, 0); gluDisk(quadric, 0, 12, 20, 1);
    glPopMatrix();
    gluCylinder(quadric, 12, 12, 8, 20, 1);
    glPushMatrix();
    glTranslatef(0, 0, 8); gluDisk(quadric, 0, 12, 20, 1);
    glPopMatrix();
    glPopMatrix();
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(0, 0, 8.1); gluDisk(quadric, 0, 8, 20, 1);
    glPopMatrix();
}

// CONSTRUCTOR
MountainCar::MountainCar(Point position) {
    this->pos = position;
}

// SETTER FUNCTION
void MountainCar::setPosition(Point newPosition) {
    this->pos = newPosition;
}

// MAIN DRAW FUNCTION
void MountainCar::draw() {
    // --- 1. SETUP ---
    GLUquadric* quadric = gluNewQuadric();
    float whiteEmission[] = { 1.0, 1.0, 1.0, 1.0 };
    float redEmission[] = { 1.0, 0.0, 0.0, 1.0 };
    float yellowEmission[] = { 1.0, 1.0, 0.0, 1.0 };
    float noEmission[] = { 0.0, 0.0, 0.0, 1.0 };
    float glass_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float glass_shininess[] = { 128.0 };
    float default_specular[] = { 0.0, 0.0, 0.0, 1.0 };
    float default_shininess[] = { 0.0 };

    // --- 2. CORE TRANSFORMATIONS ---
    glPushMatrix();
    glTranslatef(this->pos.x, this->pos.y, this->pos.z);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(1.2, 1.2, 1.2);

    // --- 3. MAIN BODY ---
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
    glScalef(50, 20, 90); glutSolidCube(1);
    glPopMatrix();
    glColor3f(0.15f, 0.15f, 0.15f);
    glPushMatrix();
    glTranslatef(0, 18, -10); glScalef(48, 16, 60); glutSolidCube(1);
    glPopMatrix();

    // --- 4. WHEELS ---
    glPushMatrix();
    glTranslatef(25, -8, 35); glRotatef(90, 0, 1, 0); drawWheelWithRim(quadric);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-25, -8, 35); glRotatef(-90, 0, 1, 0); drawWheelWithRim(quadric);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25, -8, -35); glRotatef(90, 0, 1, 0); drawWheelWithRim(quadric);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-25, -8, -35); glRotatef(-90, 0, 1, 0); drawWheelWithRim(quadric);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 5, -50.0f); drawWheelWithRim(quadric);
    glPopMatrix();

    // --- 5. FRONT BUMPER ---
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(0, -12, 46); glScalef(52, 4, 4); glutSolidCube(1);
    glPopMatrix();

    // --- 6. FRONT WINDSHIELD ---
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.6f, 0.8f, 1.0f, 0.4f);
    glBegin(GL_QUADS);
    glVertex3f(-23.0f, 25.0f, 20.1f);
    glVertex3f(23.0f, 25.0f, 20.1f);
    glVertex3f(23.0f, 11.0f, 22.1f);
    glVertex3f(-23.0f, 11.0f, 22.1f);
    glEnd();
    glDisable(GL_BLEND);

    // --- 7. LIGHTS ---
    glEnable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_EMISSION, whiteEmission);
    glPushMatrix();
    glTranslatef(20, 0, 45.1); glScalef(6, 4, 1); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-20, 0, 45.1); glScalef(6, 4, 1); glutSolidCube(1);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, redEmission);
    glPushMatrix();
    glTranslatef(22, 0, -45.1); glScalef(4, 3, 1); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-22, 0, -45.1); glScalef(4, 3, 1); glutSolidCube(1);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
    glDisable(GL_LIGHTING);

    // --- 8. SIDE WINDOWS ---
    glEnable(GL_LIGHTING);
    glColor3f(0.0f, 0.0f, 0.0f);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, glass_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, glass_shininess);
    glPushMatrix();
    glTranslatef(24.1, 18, 5); glScalef(1, 12, 25); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(24.1, 18, -25); glScalef(1, 12, 20); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-24.1, 18, 5); glScalef(1, 12, 25); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-24.1, 18, -25); glScalef(1, 12, 20); glutSolidCube(1);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, default_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, default_shininess);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    // --- 9. DOOR DETAILS ---
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(25.1, 8, 10); glScalef(1, 1.5, 5); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25.1, 8, -20); glScalef(1, 1.5, 5); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-25.1, 8, 10); glScalef(1, 1.5, 5); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-25.1, 8, -20); glScalef(1, 1.5, 5); glutSolidCube(1);
    glPopMatrix();
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex3f(25.1, 26, -8); glVertex3f(25.1, -10, -8);
    glVertex3f(-25.1, 26, -8); glVertex3f(-25.1, -10, -8);
    glEnd();

    // --- 10. FINAL DETAILS ---
    glColor3f(0.15f, 0.15f, 0.15f);
    glPushMatrix();
    glTranslatef(26, 15, 15); glScalef(4, 8, 4); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-26, 15, 15); glScalef(4, 8, 4); glutSolidCube(1);
    glPopMatrix();
    glColor3f(0.05f, 0.05f, 0.05f);
    glPushMatrix();
    glTranslatef(0, 0, 45.2); glScalef(40, 12, 1); glutSolidCube(1);
    glPopMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(20, 26.5, -10); glScalef(2, 1, 58); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-20, 26.5, -10); glScalef(2, 1, 58); glutSolidCube(1);
    glPopMatrix();

    glEnable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_EMISSION, yellowEmission);
    glPushMatrix();
    glTranslatef(15, -12, 48.5f);
    glutSolidSphere(2.5, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-15, -12, 48.5f);
    glutSolidSphere(2.5, 20, 20);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
    glDisable(GL_LIGHTING);

    // --- 11. CLEANUP ---
    glPopMatrix();
    gluDeleteQuadric(quadric);
}
