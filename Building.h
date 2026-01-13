#pragma once
#ifndef BUILDING_H
#define BUILDING_H
#include "Cuboid.h"

#include <GL/glut.h>

class Building {
public:
	Building();
	Building(double x, double y, double z, double w, double h, double l);
	void draw();
	double width, height, length, x, y, z;
private: 
	/*Cuboid building;
	Cuboid wall1;*/
};

#endif