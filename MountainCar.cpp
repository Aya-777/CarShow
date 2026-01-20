#include "MountainCar.h"
#include <GL/freeglut.h>

// -----------------------------------------------------------------------------
// HELPER FUNCTION: drawWheelWithRim
// - Draws a complete, solid wheel with a tire and a silver rim.
// - This function is reused 5 times to avoid repeating code.
// -----------------------------------------------------------------------------
void drawWheelWithRim(GLUquadric* quadric) {
    // 1. Draw the outer tire in dark black
    glColor3f(0.05f, 0.05f, 0.05f);
    glPushMatrix();
    // Back cap of the cylinder to make it solid
    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    gluDisk(quadric, 0, 12, 20, 1);
    glPopMatrix();
    // The main body of the tire
    gluCylinder(quadric, 12, 12, 8, 20, 1);
    // Front cap of the cylinder
    glPushMatrix();
    glTranslatef(0, 0, 8);
    gluDisk(quadric, 0, 12, 20, 1);
    glPopMatrix();
    glPopMatrix();

    // 2. Draw the silver metallic rim in the center
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(0, 0, 8.1); // Move it slightly forward to prevent Z-fighting
    gluDisk(quadric, 0, 8, 20, 1); // Draw with a smaller radius
    glPopMatrix();
}

// -----------------------------------------------------------------------------
// CONSTRUCTOR
// -----------------------------------------------------------------------------
MountainCar::MountainCar(Point position) {
    this->pos = position;
}

// -----------------------------------------------------------------------------
// SETTER FUNCTION for position
// -----------------------------------------------------------------------------
void MountainCar::setPosition(Point newPosition) {
    this->pos = newPosition;
}

// -----------------------------------------------------------------------------
// DRAW FUNCTION
// - This is the main function that renders the entire car.
// -----------------------------------------------------------------------------
void MountainCar::draw() {
    // --- 1. SETUP: Define tools and materials once at the beginning ---
    GLUquadric* quadric = gluNewQuadric();
    float whiteEmission[] = { 1.0, 1.0, 1.0, 1.0 };
    float redEmission[] = { 1.0, 0.0, 0.0, 1.0 };
    float yellowEmission[] = { 1.0, 1.0, 0.0, 1.0 };
    float noEmission[] = { 0.0, 0.0, 0.0, 1.0 };
    float glass_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float glass_shininess[] = { 128.0 };
    float default_specular[] = { 0.0, 0.0, 0.0, 1.0 };
    float default_shininess[] = { 0.0 };

    // --- 2. CORE TRANSFORMATIONS: Apply to the entire car ---
    glPushMatrix(); // Start the car's transformation group
    // First, move the car to its designated position in the hall
    glTranslatef(this->pos.x, this->pos.y, this->pos.z);
    // Second, rotate the car to face the entrance
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    // Third, scale the entire car to match the new building size
    glScalef(1.5, 1.5, 1.5);

    // --- 3. MAIN BODY (CHASSIS & CABIN) ---
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
    // Spare wheel at the back
    glPushMatrix();
    glTranslatef(0, 5, -50.0f); drawWheelWithRim(quadric);
    glPopMatrix();

    // --- 5. FRONT BUMPER ---
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(0, -12, 46); glScalef(52, 4, 4); glutSolidCube(1);
    glPopMatrix();

    // --- 6. FRONT WINDSHIELD (with a full frame) ---
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

    // --- 7. HEADLIGHTS & TAILLIGHTS (using Emission) ---
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

    // --- 8. SIDE WINDOWS (using Specular Material for reflection) ---
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

    // --- 9. DOOR HANDLES & SEPARATION LINES ---
    glColor3f(0.0f, 0.0f, 0.0f);
    // Handles
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
    // Lines
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex3f(25.1, 26, -8); glVertex3f(25.1, -10, -8);
    glVertex3f(-25.1, 26, -8); glVertex3f(-25.1, -10, -8);
    glEnd();

    // --- 10. FINAL DETAILS (Mirrors, Grille, Roof Rails, Fog Lights) ---
    // Mirrors
    glColor3f(0.15f, 0.15f, 0.15f);
    glPushMatrix();
    glTranslatef(26, 15, 15); glScalef(4, 8, 4); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-26, 15, 15); glScalef(4, 8, 4); glutSolidCube(1);
    glPopMatrix();
    // Grille
    glColor3f(0.05f, 0.05f, 0.05f);
    glPushMatrix();
    glTranslatef(0, 0, 45.2); glScalef(40, 12, 1); glutSolidCube(1);
    glPopMatrix();
    // Roof Rails
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(20, 26.5, -10); glScalef(2, 1, 58); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-20, 26.5, -10); glScalef(2, 1, 58); glutSolidCube(1);
    glPopMatrix();
    // Fog Lights
    glEnable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_EMISSION, yellowEmission);
    glPushMatrix();
    glTranslatef(15, -12, 48.5f); glutSolidSphere(2.5, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-15, -12, 48.5f); glutSolidSphere(2.5, 20, 20);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
    glDisable(GL_LIGHTING);

    // --- 11. CLEANUP ---
    glPopMatrix(); // End the car's transformation group
    gluDeleteQuadric(quadric); // Delete the drawing tool
}
