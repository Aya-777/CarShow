//#include "Door.h"
//#include <GL/glut.h>
//#include <cmath>
//
//Door::Door()
//{
//    hinge = Point(0, 0, 0);
//    angle = 0.0f;
//    open = false;
//}
//
//Door::Door(Point hingePos)
//{
//    hinge = hingePos;
//    angle = 0.0f;
//    open = false;
//}
//
//void Door::toggle()
//{
//    open = !open;
//}
//
//void Door::update()
//{
//    float target = open ? -90.0f : 0.0f;
//
//    // Smooth easing
//    angle += (target - angle) * 0.05f;
//
//    if (fabs(angle - target) < 0.1f)
//        angle = target;
//}
//
//void Door::draw()
//{
//    glPushMatrix();
//
//    // Move to hinge
//    glTranslatef(hinge.x, hinge.y, hinge.z);
//
//    // Rotate around hinge
//    glRotatef(angle, 0, 1, 0);
//
//    // Draw door (hinge on left)
//    glColor3f(0.55f, 0.27f, 0.07f);
//
//    glBegin(GL_QUADS);
//
//    // Front face
//    glVertex3f(0, 0, 0);
//    glVertex3f(30, 0, 0);
//    glVertex3f(30, 50, 0);
//    glVertex3f(0, 50, 0);
//
//    // Back face
//    glVertex3f(0, 0, -2);
//    glVertex3f(30, 0, -2);
//    glVertex3f(30, 50, -2);
//    glVertex3f(0, 50, -2);
//
//    // Left side (hinge)
//    glVertex3f(0, 0, 0);
//    glVertex3f(0, 50, 0);
//    glVertex3f(0, 50, -2);
//    glVertex3f(0, 0, -2);
//
//    // Right side
//    glVertex3f(30, 0, 0);
//    glVertex3f(30, 50, 0);
//    glVertex3f(30, 50, -2);
//    glVertex3f(30, 0, -2);
//
//    glEnd();
//
//    glPopMatrix();
//}