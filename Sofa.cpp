
#include "Sofa.h"

#include "Cuboid.h"

#include <GL/glut.h>



Sofa::Sofa(Point c) : center(c), rotation(0.0f) {}



// move sofa

void Sofa::setPosition(Point c) { center = c; }



// rotate sofa

void Sofa::setRotation(float angle) { rotation = angle; }



// draw single sofa

void Sofa::draw() {

    glPushMatrix();



    // move to sofa position

    glTranslatef(center.x, center.y, center.z);



    // rotate around Y-axis

    glRotatef(rotation, 0, 1, 0);



    // sofa base

    glColor3ub(22, 22, 22);

    Cuboid(Point(0, 0, 0), 2, 14, 20).draw();
    //Cuboid(Point(0, 0, 0), 1, 7, 10).draw();



    // left hand

    glColor3ub(55, 55, 55);

    Cuboid(Point(-10.5, 0, 0), 10, 14, 1).draw();
    //Cuboid(Point(-5.25, 0, 0), 5, 7, 0.5).draw();



    // right hand

    glColor3ub(88, 88, 88);

    Cuboid(Point(10.5, 0, 0), 10, 14, 1).draw();
    //Cuboid(Point(5.25, 0, 0), 5, 7, 0.5).draw();



    // back

    glColor3ub(136, 0, 21);

    Cuboid(Point(0, 0, -7.5), 10, 1, 22).draw();
    //Cuboid(Point(0, 0, -3.75), 5, 0.5, 11).draw();



    // legs

    glColor3ub(55, 55, 55);

    //Cuboid(Point(5.25, -2, 3.2), 2, 0.6, 0.5).draw();
    Cuboid(Point(10.5, -4, 6.4), 4, 1.2, 1).draw();

    //Cuboid(Point(-5.25, -2, 3.2), 2, 0.6, 0.5).draw();
    Cuboid(Point(-10.5, -4, 6.4), 4, 1.2, 1).draw();

    //Cuboid(Point(5.25, -2, -3.7), 2, 0.6, 0.5).draw();
    Cuboid(Point(10.5, -4, -6.4), 4, 1.2, 1).draw();

    //Cuboid(Point(-5.25, -2, -3.7), 2, 0.6, 0.5).draw();
    Cuboid(Point(-10.5, -4, -6.4), 4, 1.2, 1).draw();



    glPopMatrix();

}



// triple sofa (same rotation)

void Sofa::drawTriple() {

    glPushMatrix();

    glTranslatef(center.x, center.y, center.z);

    glRotatef(rotation, 0, 1, 0);



    // first base

    glColor3ub(22, 22, 22);

    //Cuboid(Point(0, 0, 0), 0.5, 7, 10).draw();
    Cuboid(Point(0, 0, 0), 1, 14, 20).draw();



    // second base

    glColor3ub(22, 22, 22);

    Cuboid(Point(-17, 0, 8), 1, 30, 14).draw();
    //Cuboid(Point(-8.5, 0, 4), 0.5, 15, 7).draw();



    // right hand

    glColor3ub(88, 88, 88);

    Cuboid(Point(9.5, 1, 0), 9, 14, 1).draw();
    //Cuboid(Point(4.75, 0.5, 0), 4.5, 7, 0.5).draw();



    // first back

    glColor3ub(136, 0, 21);

    Cuboid(Point(-7.5, 1, -6.5), 9, 1, 33).draw();
    //Cuboid(Point(-3.75, 0.5, -3.25), 4.5, 0.5, 16.5).draw();

    

    // second back

    glColor3ub(136, 0, 21);

    Cuboid(Point(-23.5, 1, 8), 9, 28, 1).draw();
    //Cuboid(Point(-11.75, 0.5, 4), 4.5, 14, 0.5).draw();

    

    // left hand

    glColor3ub(55, 55, 55);

    Cuboid(Point(-17, 1, 22.5), 9, 1, 14).draw();
    //Cuboid(Point(-8.5, 0.5, 11.25), 4.5, 0.5, 7).draw();

    

    // legs

    glColor3ub(55, 55, 55);

    Cuboid(Point(9.5, -4, 6.4), 4, 1.2, 1).draw();
    //Cuboid(Point(4.75, -2, 3.2), 2, 0.6, 0.5).draw();

    Cuboid(Point(9.5, -4, -6.4), 4, 1.2, 1).draw();

    Cuboid(Point(-10.5, -4, 6.4), 4, 1.2, 1).draw();

    Cuboid(Point(-10.5, -4, -6.4), 4, 1.2, 1).draw();

    Cuboid(Point(-10.5, -4, 22.4), 4, 1.2, 1).draw();

    Cuboid(Point(-23.5, -4, 22.4), 4, 1.2, 1).draw();

    Cuboid(Point(-23.5, -4, -6.4), 4, 1.2, 1).draw();



    glPopMatrix();

}

