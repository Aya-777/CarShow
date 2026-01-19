#pragma once
#include "Point.h"
struct Door
{
public:
	Point center = Point(0, 0, 0);
	double OpenRate = 0.0;
	bool open = false;
};

/*salma
#pragma once
#include "Point.h"

class Door
{
public:
    Point hinge;     // hinge position
    float angle;     // current rotation angle
    bool open;       // REQUIRED by Camera (true = open, false = closed)

    Door();
    Door(Point hingePos);

    void toggle();
    void update();
    void draw();
	void drawDoor();
	void openDoor();
};
*/
