#include "Building.h"
#include "Cuboid.h"
#include "Point.h"
#include <GL/glut.h>

void Building::draw() {

	//glDisable(GL_LIGHTING);
	glPushMatrix();
	Cuboid wall1(Point(-215, 0, 50), 150, 914, 15); // front wide
	Cuboid wall2(Point(200, 0, 50), 150, 914, 15); // back wide
	Cuboid wall3(Point(-500, 0, 0), 150, 415 , 15); // right short
	Cuboid wall4(Point(400, 0, 0), 150, 415, 15); // left 
	
	float repeatX1 = 400 / 150.0;
	float repeatY1 = 150 / 150;

	float repeatX2 = 900 / 150.0;
	float repeatY2 = 150 / 150;

	glColor3f(1.0f, 1.0f, 1.0f);
	wall1.drawWithTexture(wallTex,repeatX1,repeatY1);
	wall2.drawWithTexture(wallTex, repeatX1, repeatY1);
	glRotatef(90, 0, 1, 0);
	wall3.drawWithTexture(wallTex, repeatX2, repeatY2);
	wall4.drawWithTexture(wallTex, repeatX2, repeatY2);
	glPopMatrix();

	// roof
	glPushMatrix();
	Cuboid roof(Point(50, -200, -155), 422, 10, 915);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	roof.drawWithTexture(wallTex,repeatX1,repeatY1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	Cuboid insideWall1(Point(87, 0, -50), 150, 10, 250);
	Cuboid insideWall2(Point(87, 0, 140), 150, 10, 200);
	Cuboid insideWall3(Point(87, 0, 320), 150, 10, 200);
	insideWall1.draw();	
	insideWall2.draw();
	insideWall3.draw();
	glPopMatrix();


	//building.draw();

	//Cuboid administrationBuilding(Point(-75,0,365), 100, 80, 150);
	//administrationBuilding.draw();
	//glEnable(GL_LIGHTING);
}

Building::Building(){}

Building::Building(double x2, double y2, double z2, double w, double h, double l) {
	width = w;
	height = h;
	length = l;
	x = x2;
	y = y2;
	z = z2;
}