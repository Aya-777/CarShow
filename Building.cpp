#include "Building.h"
#include "Cuboid.h"
#include "Point.h"
#include "Door.h"
#include "Window.h"
#include <GL/glut.h>


void Building::draw() {

	Cuboid wall1(Point(-215, 2, -279), 150, 255, 15); // front wide
	Cuboid wall12(Point(-215, 2, 278), 150, 455, 15); // front door (side left)
	Cuboid wall13(Point(-215, 89, -52), 60, 205, 15); // front door (side right)
	Cuboid wall2(Point(350, 2, 50), 150, 914, 15); // back wide
	Cuboid wall3(Point(-500, 2, 127), 150, 460 , 10); // right short (side left)
	Cuboid wall32(Point(-500, 2, -180), 150, 60, 10); // right short (side right)
	Cuboid wall33(Point(-500, 50, -127), 100, 47, 10); // left short (front)
	Cuboid wall4(Point(400, 2, 70), 150, 565, 15); // left short
	Cuboid roof(Point(50, -358, -152), 580, 10, 915); // roof
	Cuboid ground(Point(50, -358, 0), 580, 1, 915); // ground
	Cuboid insideWall1(Point(237, 2, -50), 150, 10, 250); // insideWall1
	Cuboid insideWall2(Point(237, 2, 140), 150, 10, 200); // insideWall2
	Cuboid insideWall3(Point(237, 2, 320), 150, 10, 200); // insideWall3
	//Cuboid administrationBuilding(Point(-140, 2, 570), 100, 150, 150); // administration building
	Cuboid bwall1(Point(-505, 0, -180), 100, 60, 10); // left short (side right)
	Cuboid bwall12(Point(-505, 0, 0), 100, 200, 10); // left short (side left)
	Cuboid bwall13(Point(-505, 50, -125), 50, 50, 10); // left short (front)
	Cuboid bwall2(Point(-715, 0, -53), 100, 320, 15); // right short
	Cuboid bwall3(Point(100, 0, 610), 100, 200, 15); // back wide
	Cuboid bwall4(Point(-205, 0, 610), 100, 200, 15); // front wide
	Cuboid broof(Point(610, -102, -102), 308, 1, 225); // roof
	Cuboid bground(Point(600, -95, 0), 308, 1, 230); // ground

	float repeatX1 = 400 / 150.0;
	float repeatY = 150 / 150;
	float repeatX2 = 900 / 150.0;

	// outer walls
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	wall1.drawWithTexture(wallTex,repeatX1,repeatY);
	wall12.drawWithTexture(wallTex, repeatX1, repeatY);
	wall13.drawWithTexture(wallTex, repeatX1, repeatY);
	wall2.drawWithTexture(wallTex, repeatX1, repeatY);
	glRotatef(90, 0, 1, 0);
	wall3.drawWithTexture(wallTex, repeatX2-2, repeatY);
	wall32.drawWithTexture(wallTex, 1, 2);
	wall33.drawWithTexture(wallTex, 1, 1);
	wall4.drawWithTexture(wallTex, repeatX2-2, repeatY);
	glPopMatrix();

	// roof
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	roof.drawWithTexture(wallTex,repeatX1,repeatY);
	glPopMatrix();

	//ground
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	ground.drawWithTexture(groundTex, 7, 40);
	glPopMatrix();


	// inside walls
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	insideWall1.drawWithTexture(wallTex2, repeatX2, repeatY);
	insideWall2.drawWithTexture(wallTex2, repeatX2, repeatY);
	insideWall3.drawWithTexture(wallTex2, repeatX2, repeatY);
	glPopMatrix();

	// **************************** administration building ***************************
	glPushMatrix();
	glColor3f(0.7, 0.7, 0.7);
	bwall3.drawWithTexture(wallTex, repeatX1, repeatY);
	bwall4.drawWithTexture(wallTex, repeatX1, repeatY);
	glRotatef(90, 0, 1, 0);
	//administrationBuilding.drawWithTexture(wallTex, repeatX1, repeatY);
	bwall1.drawWithTexture(wallTex, 1, 2);
	bwall12.drawWithTexture(wallTex, repeatX1, repeatY);
	bwall13.drawWithTexture(wallTex, 1, 1);
	bwall2.drawWithTexture(wallTex, repeatX1, repeatY);
	glPopMatrix();


	// admin ground
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	bground.drawWithTexture(groundTex, 7, 40);
	broof.drawWithTexture(wallTex, repeatX1, repeatY);
	glPopMatrix();


	// Door
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	leftdoor.openWindow();
	rightdoor.openWindow();
	leftdoor.drawMovingWindow(0.7, 0.7, 0.7,true);
	rightdoor.drawMovingWindow(0.7, 0.7, 0.7, false);
	glPopMatrix();
}

void Building::toggleDoor()
{
	leftdoor.isOpen = !leftdoor.isOpen;
	rightdoor.isOpen = !rightdoor.isOpen;
}

Building::Building()
	: leftdoor(Point(0, -2, -215), 10, 99, 88, 0, 0, 0, 0, 1), 
	rightdoor(Point(100, -2, -215), 10, 98, 88, 0, 0, 0, 0, 1)
{

}

Building::Building(double x2, double y2, double z2, double w, double h, double l,Window leftdoor, Window rightdoor)
: leftdoor(leftdoor),
  rightdoor(rightdoor){
	width = w;
	height = h;
	length = l;
	x = x2;
	y = y2;
	z = z2;
}