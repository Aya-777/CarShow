#include "Bureau.h"
#include <GL/glut.h>

Bureau::Bureau(Point center)
    : body(center, 10, 25, 10) // h, w
{
}

void Bureau::draw()
{
    body.draw();

    // draw items on top
    drawItems();
}

void Bureau::drawItems()
{
    // desk top position
    Point top = Point(body.center.x, body.center.y + 25 / 2.0f, body.center.z); // y + half height

    // --- Papers ---
    glColor3ub(255, 255, 255); // white paper
    Cuboid(Point(top.x - 3, 10, top.z), 0.1f, 6, 4).draw(); // small paper

    Cuboid(Point(top.x + 3, 10, top.z - 2), 0.1f, 5, 3).draw(); // another paper

  
       // --- Computer ---

    // Base (new)
    float baseHeight =0.5f;
    float baseWidth = 2.0f;
    float baseDepth = 1.0f;
    glColor3ub(0, 0, 0); // dark gray base
    Cuboid(Point(body.center.x,10, body.center.z + 5),
        baseHeight, baseWidth,baseDepth).draw();

    // Stand
    float standWidth = 0.5f;
    float standHeight = 0.5f;
    float standDepth = 0.f;
    glColor3ub(0, 0, 0); // gray stand
    Cuboid(Point(body.center.x, 10.5, body.center.z + 5),
        standHeight, standWidth,  standDepth).draw();

    // Monitor
    float monitorWidth = 4.0f;
    float monitorHeight = 3.0f;
    float monitorDepth = 0.2f;
    glColor3ub(0, 0, 0); // black monitor
    Cuboid(Point(body.center.x,11, body.center.z + 5),
        monitorWidth, monitorHeight, monitorDepth).draw();

    // --- Keyboard ---
    float keyboardWidth = 6.0f;
    float keyboardHeight = 0.3f;
    float keyboardDepth = 2.0f;
    glColor3ub(100, 100, 100); // gray keyboard
    Cuboid(Point(body.center.x + 3, 10, body.center.z + 5),
        keyboardHeight, keyboardWidth,  keyboardDepth).draw();

}
