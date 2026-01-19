#include "Building.h"
#include "Cuboid.h"
#include "Point.h"
#include "Door.h"
#include <GL/glut.h>

void Building::draw() {

	//glDisable(GL_LIGHTING);
	glPushMatrix();
	Cuboid wall1(Point(-215, -2, -279), 150, 255, 15); // front wide
	Cuboid wall12(Point(-215, -2, 278), 150, 455, 15); // front door side left)
	Cuboid wall13(Point(-215, 89, -52), 60, 205, 15); // front door side right
	Cuboid wall2(Point(200, -2, 50), 150, 914, 15); // back wide
	Cuboid wall3(Point(-500, -2, 0), 150, 415 , 15); // right short
	Cuboid wall4(Point(400, -2, 0), 150, 415, 15); // left 
	Cuboid roof(Point(50, -200, -152), 422, 10, 915); // roof
	Cuboid insideWall1(Point(87, -2, -50), 150, 10, 250); // insideWall1
	Cuboid insideWall2(Point(87, -2, 140), 150, 10, 200); // insideWall2
	Cuboid insideWall3(Point(87, -2, 320), 150, 10, 200); // insideWall3
	Cuboid administrationBuilding(Point(-140, -2, 548), 100, 150, 150); // administration building
	
	float repeatX1 = 400 / 150.0;
	float repeatY = 150 / 150;
	float repeatX2 = 900 / 150.0;

	// outer walls
	glColor3f(1.0f, 1.0f, 1.0f);
	wall1.drawWithTexture(wallTex,repeatX1,repeatY);
	wall12.drawWithTexture(wallTex, repeatX1, repeatY);
	wall13.drawWithTexture(wallTex, repeatX1, repeatY);
	wall2.drawWithTexture(wallTex, repeatX1, repeatY);
	glRotatef(90, 0, 1, 0);
	wall3.drawWithTexture(wallTex, repeatX2, repeatY);
	wall4.drawWithTexture(wallTex, repeatX2, repeatY);
	glPopMatrix();

	// roof
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	roof.drawWithTexture(wallTex,repeatX1,repeatY);
	glPopMatrix();

	// inside walls
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	insideWall1.draw();	
	insideWall2.draw();
	insideWall3.draw();
	glPopMatrix();

	// administration building
	glPushMatrix();
	glColor3f(0.7, 0.7, 0.7);
	administrationBuilding.drawWithTexture(wallTex, repeatX1, repeatY);
	glPopMatrix();

	// Door
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(-224.0f, -2.0f, 51.0);
	door.openDoor();
	door.drawDoor();
	glPopMatrix();
}

void Building::toggleDoor()
{
	door.open = !door.open;
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