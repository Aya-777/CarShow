
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

    Cuboid(Point(0, 0, 0), 1, 7, 10).draw();



    // left hand

    glColor3ub(55, 55, 55);

    Cuboid(Point(-5.25, 0, 0), 5, 7, 0.5).draw();



    // right hand

    glColor3ub(88, 88, 88);

    Cuboid(Point(5.25, 0, 0), 5, 7, 0.5).draw();



    // back

    glColor3ub(136, 0, 21);

    Cuboid(Point(0, 0, -3.75), 5, 0.5, 11).draw();



    // legs

    glColor3ub(55, 55, 55);

    Cuboid(Point(5.25, -2, 3.2), 2, 0.6, 0.5).draw();

    Cuboid(Point(-5.25, -2, 3.2), 2, 0.6, 0.5).draw();

    Cuboid(Point(5.25, -2, -3.7), 2, 0.6, 0.5).draw();

    Cuboid(Point(-5.25, -2, -3.7), 2, 0.6, 0.5).draw();



    glPopMatrix();

}



// triple sofa (same rotation)

void Sofa::drawTriple() {

    glPushMatrix();

    glTranslatef(center.x, center.y, center.z);

    glRotatef(rotation, 0, 1, 0);



    // first base

    glColor3ub(22, 22, 22);

    Cuboid(Point(0, 0, 0), 0.5, 7, 10).draw();



    // second base

    glColor3ub(22, 22, 22);

    Cuboid(Point(-8.5, 0, 4), 0.5, 15, 7).draw();



    // right hand

    glColor3ub(88, 88, 88);

    Cuboid(Point(4.75, 0.5, 0), 4.5, 7, 0.5).draw();



    // first back

    glColor3ub(136, 0, 21);

    Cuboid(Point(-3.75, 0.5, -3.25), 4.5, 0.5, 16.5).draw();



    // second back

    glColor3ub(136, 0, 21);

    Cuboid(Point(-11.75, 0.5, 4), 4.5, 14, 0.5).draw();



    // left hand

    glColor3ub(55, 55, 55);

    Cuboid(Point(-8.5, 0.5, 11.25), 4.5, 0.5, 7).draw();



    // legs

    glColor3ub(55, 55, 55);

    Cuboid(Point(4.75, -2, 3.2), 2, 0.6, 0.5).draw();

    Cuboid(Point(4.75, -2, -3.2), 2, 0.6, 0.5).draw();

    Cuboid(Point(-5.25, -2, 3.2), 2, 0.6, 0.5).draw();

    Cuboid(Point(-5.25, -2, -3.2), 2, 0.6, 0.5).draw();

    Cuboid(Point(-5.25, -2, 11.2), 2, 0.6, 0.5).draw();

    Cuboid(Point(-11.75, -2, 11.2), 2, 0.6, 0.5).draw();

    Cuboid(Point(-11.75, -2, -3.2), 2, 0.6, 0.5).draw();



    glPopMatrix();

}

/*
* after fixing the building:
* #include "Sofa.h" //salma
#include "Door.h" //salma
#include "Desk.h" //salma


//Sofa sofa; //salma
Sofa sofa(Point(-100, 0, 365)); // slightly in front of desk
Sofa sofa2(Point(-100, 0, 300)); // slightly in front of desk
//Sofa sofa(Point(-60, 0, 350)); // slightly in front of desk
Door door(Point(-120, 0, 305)); //salma
//Door door(Point(-60, 0, 300)); //salma
Desk desk(Point(-30, 0, 365));  // slightly above floor
//Desk desk(Point(-60, 0, 380));  // slightly above floor
door.update(); //salma
    sofa.setRotation(180);
    sofa2.setRotation(-90);

    door.draw(); //salma
    // draw sofa
    //sofa.draw(Point(0.0f, -1.5f, 0.0f)); //salma
    sofa.draw();
    sofa2.draw();
    desk.draw(); //salma
    door.update();   // ? animate door



            //salma
    case 'o':
        door.toggle();
        break;
        


    }
    //salma
    // Call this outside the switch so ANY key press refreshes the screen
    glutPostRedisplay();
    // *** //



*/

