#pragma once
#ifndef BUILDING_H
#define BUILDING_H
#include "Cuboid.h"
#include "Door.h"
#include "Window.h"

#include <GL/glut.h>

class Building {
public:
	Building();
	Building(double x, double y, double z, double w, double h, double l,Window door);
	void draw();
	void toggleDoor();
	double width, height, length, x, y, z;
	GLuint wallTex, wallTex2;
	Window door;
private:
};

#endif