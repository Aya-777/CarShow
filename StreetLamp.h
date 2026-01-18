#pragma once
#include <GL/freeglut.h>

class StreetLamp {
private:
    GLUquadric* quad;

public:
    StreetLamp() {
        quad = gluNewQuadric();
    }

    void draw() {
        glPushMatrix();
        glColor3f(0.1f, 0.1f, 0.1f); 
        glPushMatrix();
        glRotatef(-90, 1, 0, 0);
        gluCylinder(quad, 1.5, 1.0, 50.0, 12, 12);
        glPopMatrix();

        
        glPushMatrix();
        glTranslatef(0.0f, 50.0f, 0.0f);
        glRotatef(90, 0, 1, 0);
        gluCylinder(quad, 0.8, 0.5, 10.0, 8, 8);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(10.0f, 50.0f, 0.0f); 
        GLfloat emit[] = { 1.0f, 1.0f, 0.5f, 1.0f };
        glMaterialfv(GL_FRONT, GL_EMISSION, emit);
        glColor3f(1.0f, 1.0f, 0.7f);
        glutSolidSphere(3.0, 12, 12);

        GLfloat no_emit[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_EMISSION, no_emit);
        glPopMatrix();
        glPopMatrix();
    }
};