#pragma once
#ifndef FAMILYCAR_H
#define FAMILYCAR_H

#include <GL/glut.h>

class FamilyCar {
public:
	GLint window;
	GLint window2;
	GLint Xsize = 1000;
	GLint Ysize = 800;
	float i, theta;
	GLint nml = 0, day = 1;
	GLfloat xt = 0.0, yt = 0.0, zt = 0.0, xw = 0.0;
	GLfloat xs = 1.0, ys = 1.0, zs = 1.0;
	GLfloat xangle = 0.0, yangle = 0.0, zangle = 0.0, angle = 0.0;

	GLfloat r = 0, g = 0, b = 1;
	GLint light = 1;
	int count = 1, flg = 1;

	FamilyCar();          // Constructor
	void draw();          // The function that holds all the glBegin/glEnd calls
	//void move();          // Update position logic
};

#endif