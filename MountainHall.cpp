#include "MountainHall.h"
#include <GL/freeglut.h>

MountainHall::MountainHall() : mainCar(Point(0, 22, -45)) {
    // Constructor
}

void MountainHall::draw() {
    // --- 1. رسم أرضية الصالة ---
    glColor3f(0.4f, 0.4f, 0.45f);
    glBegin(GL_QUADS);
    glVertex3f(-150.0f, -2.9f, -115.0f); glVertex3f(150.0f, -2.9f, -115.0f); glVertex3f(150.0f, -2.9f, 25.0f); glVertex3f(-150.0f, -2.9f, 25.0f);
    glEnd();

    // --- 2. رسم الجدران ---
    glColor3f(0.8f, 0.7f, 0.6f);
    glBegin(GL_QUADS);
    glVertex3f(-150.0f, -3.0f, -114.9f); glVertex3f(150.0f, -3.0f, -114.9f); glVertex3f(150.0f, 97.0f, -114.9f); glVertex3f(-150.0f, 97.0f, -114.9f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(-150.0f, -3.0f, 24.9f); glVertex3f(150.0f, -3.0f, 24.9f); glVertex3f(150.0f, 97.0f, 24.9f); glVertex3f(-150.0f, 97.0f, 24.9f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(-149.9f, -3.0f, -115.0f); glVertex3f(-149.9f, -3.0f, -95.0f); glVertex3f(-149.9f, 97.0f, -95.0f); glVertex3f(-149.9f, 97.0f, -115.0f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(-149.9f, -3.0f, 5.0f); glVertex3f(-149.9f, -3.0f, 25.0f); glVertex3f(-149.9f, 97.0f, 25.0f); glVertex3f(-149.9f, 97.0f, 5.0f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex3f(149.9f, -3.0f, -115.0f); glVertex3f(149.9f, -3.0f, 25.0f); glVertex3f(149.9f, 97.0f, 25.0f); glVertex3f(149.9f, 97.0f, -115.0f);
    glEnd();

    GLUquadric* quadric = gluNewQuadric();

    // --- 3. رسم المنصة (بألوان مختلفة للحواف) ---
    glPushMatrix();
    glTranslatef(0, -3.0, -45);
    glRotatef(-90, 1, 0, 0);

    // الجوانب (الأسطوانة) باللون الأغمق
    glColor3f(0.25f, 0.25f, 0.28f); // <<< لون أغمق
    gluCylinder(quadric, 70, 70, 5, 64, 1);

    // الغطاء العلوي باللون الأفتح
    glColor3f(0.35f, 0.35f, 0.38f); // <<< لون أفتح
    glPushMatrix();
    glTranslatef(0, 0, 5);
    gluDisk(quadric, 0, 70, 64, 1);
    glPopMatrix();

    // (القرص السفلي لا يظهر، لذلك لا نحتاج لرسمه)
    glPopMatrix();

    // رسم السيارة
    mainCar.draw();

    gluDeleteQuadric(quadric);
}
