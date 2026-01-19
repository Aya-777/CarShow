#pragma once
#include "Point.h"
struct Door
{
public:
	Point center = Point(0, 0, 0);
	double OpenRate = 0.0;
	bool open = true;
	void drawDoor();
	void openDoor();
};