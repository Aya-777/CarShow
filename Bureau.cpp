#include "Bureau.h"
#include <GL/glut.h>

Bureau::Bureau(Point center)
    //: body(center, 5, 20, 20) // h, w
    : body(center, 15, 50, 20) // h, w
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
    //float deskTopY = body.center.y + (body.height / 2.0f);
    Point top = Point(body.center.x, body.center.y, body.center.z); // y + half height

    // --- Papers ---
    glColor3ub(255, 255, 255); // white paper
    Cuboid(Point(top.x - 3, 14, top.z - 2), 0.1f, 6, 5).draw(); // small paper
    Cuboid(Point(top.x - 4, 14, top.z - 4), 0.1f, 6, 6).draw(); // small paper
    Cuboid(Point(top.x + 3, 14, top.z - 3), 0.1f, 5, 3).draw(); // another paper

  
       // --- Computer ---

    // Base (new)
    float baseHeight =1.0f;
    float baseWidth = 4.0f;
    float baseDepth = 2.0f;
    glColor3ub(0, 0, 0); // dark gray base
    Cuboid(Point(body.center.x,14, body.center.z + 5),
        baseHeight, baseWidth,baseDepth).draw();

    // Stand
    float standWidth = 0.5f;
    float standHeight = 1.0f;
    float standDepth = 0.f;
    glColor3ub(0, 0, 0); // gray stand
    Cuboid(Point(body.center.x, 14.5, body.center.z + 5),
        standHeight, standWidth,  standDepth).draw();

    // Monitor
    float monitorWidth = 7.0f;
    float monitorHeight = 10.0f;
    float monitorDepth = 0.4f;
    glColor3ub(0, 0, 0); // black monitor
    Cuboid(Point(body.center.x,15, body.center.z + 5),
        monitorWidth, monitorHeight, monitorDepth).draw();

    // --- Keyboard ---
    float keyboardWidth = 12.0f;
    float keyboardHeight = 1.0f;
    float keyboardDepth = 2.0f;
    glColor3ub(100, 100, 100); // gray keyboard
    Cuboid(Point(body.center.x + 3, 14, body.center.z + 5),
        keyboardHeight, keyboardWidth,  keyboardDepth).draw();

}
