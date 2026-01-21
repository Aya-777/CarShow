
#include "Chair.h"

Chair::Chair(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    rotation = 0.0f;
}

void Chair::rotate(float angle)
{
    rotation += angle;
}

void Chair::draw()
{
    glPushMatrix();
    glTranslatef(x, y, z);

    // ================= BASE =================
    glColor3f(0.25f, 0.25f, 0.25f);
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, 0.3f, 0);

    glutSolidCylinder(6, 0.6, 60, 60);
    glPopMatrix();

    // ================= POLE =================
        glPushMatrix();
    glTranslatef(0, 0.3f, 0);

    // Make the cylinder horizontal
    glRotatef(-90, 1, 0, 0);

    glutSolidCylinder(1.0, 5, 40, 40);
    glPopMatrix();

    // ===== ROTATING PART (Seat + Backrest) =====
    glPushMatrix();
    glTranslatef(0, 1.2f + 4.5f, 0);   // move to top of pole
    glRotatef(rotation, 0, 1, 0);      // rotate around pole center

    // -------- SEAT --------
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
    glScalef(5, 0.6f, 5);
    glutSolidCube(2);
    glPopMatrix();

    // -------- BACKREST --------
    glPushMatrix();
    glTranslatef(0, 3.2f, -4.4f);
    glScalef(5, 4, 0.6f);
    glutSolidCube(2);
    glPopMatrix();

    glPopMatrix(); // rotating part

    glPopMatrix(); // whole chair
}
