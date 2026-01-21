#include "FamilyCar.h"
#include "Wheel.h"
#include "Point.h"
#include "Cuboid.h"
#include <GL/glut.h>
#include <math.h>

void drawWheelWithRim2(GLUquadric* quadric) {
    glColor3f(0.05f, 0.05f, 0.05f);
    glPushMatrix();
    glPushMatrix();
    glRotatef(180, 0, 1, 0); gluDisk(quadric, 0, 12, 20, 1);
    glPopMatrix();
    gluCylinder(quadric, 12, 12, 4, 20, 1);
    glPushMatrix();
    glTranslatef(0, 0, 4); gluDisk(quadric, 0, 12, 20, 1);
    glPopMatrix();
    glPopMatrix();
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(0, 0, 4.1); gluDisk(quadric, 0, 8, 20, 1);
    glPopMatrix();
}

FamilyCar::FamilyCar(Point position, bool convertible) {
    this->pos = position;
    this->isConvertible = convertible;
}

void FamilyCar::setPosition(Point newPosition) {
    this->pos = newPosition;
}

void FamilyCar::draw()
{
    GLUquadric* quadric = gluNewQuadric();
    float whiteEmission[] = { 1.0, 1.0, 1.0, 1.0 };
    float redEmission[] = { 1.0, 0.0, 0.0, 1.0 };
    float noEmission[] = { 0.0, 0.0, 0.0, 1.0 };

    glPushMatrix();
    glTranslatef(this->pos.x, this->pos.y, this->pos.z);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);

    if (isConvertible) {
        glColor3f(0.5f, 0.0f, 0.0f);
    }
    else {
        //glColor3f(0.7f, 0.7f, 0.7f); // Silver
        glColor3f(0.0f, 0.1f, 0.4f);
    }
	// main body
    glPushMatrix();
    glScalef(38, 18, 100);
    glutSolidCube(1.0);
    glPopMatrix();

    // roof
    glPushMatrix();
    glTranslatef(0, 15, -10); glScalef(36, 14, 55); glutSolidCube(1);
    glPopMatrix();

    // front windshield
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.2f, 0.3f, 0.4f, 0.6f);
    glBegin(GL_QUADS);
    glVertex3f(-18.0f, 22.0f, 22.0f);
    glVertex3f(18.0f, 22.0f, 22.0f);
    glVertex3f(19.0f, 9.0f, 35.0f);
    glVertex3f(-19.0f, 9.0f, 35.0f);
    glEnd();
    glDisable(GL_BLEND);

	// wheels
    glPushMatrix();
    glTranslatef(20, -10, 30); glRotatef(90, 0, 1, 0); drawWheelWithRim2(quadric);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-20, -10, 30); glRotatef(-90, 0, 1, 0); drawWheelWithRim2(quadric);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(20, -10, -30); glRotatef(90, 0, 1, 0); drawWheelWithRim2(quadric);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-20, -10, -30); glRotatef(-90, 0, 1, 0); drawWheelWithRim2(quadric);
    glPopMatrix();

    // front bumper
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
    glTranslatef(0, -5, 50); glScalef(40, 6, 4); 
    glutSolidCube(1);
    glPopMatrix();

    // Grille
    glColor3f(0.05f, 0.05f, 0.05f);
    glPushMatrix();
    glTranslatef(0, 2, 50.1); glScalef(15, 8, 1);
    glutSolidCube(1);
    glPopMatrix();

    // --- LIGHTS (Adjusted spacing) ---
    glEnable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_EMISSION, whiteEmission);
    glPushMatrix();
    glTranslatef(13, 3, 50.2); glScalef(7, 4, 1); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-13, 3, 50.2); glScalef(7, 4, 1); glutSolidCube(1);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_EMISSION, redEmission);
    glPushMatrix();
    glTranslatef(14, 3, -50.2); glScalef(8, 3, 1); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-14, 3, -50.2); glScalef(8, 3, 1); glutSolidCube(1);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
    glDisable(GL_LIGHTING);

    // --- SIDE WINDOWS ---
        glColor3f(0.1f, 0.1f, 0.1f);
        glPushMatrix();
        glTranslatef(18.1, 15, -20); glScalef(1, 10, 30); glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(18.1, 15, 10); glScalef(1, 10, 20); glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-18.1, 15, -20); glScalef(1, 10, 30); glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-18.1, 15, 10); glScalef(1, 10, 20); glutSolidCube(1);
        glPopMatrix();

    glPopMatrix();
    gluDeleteQuadric(quadric);
}
