#include "Building.h"
#include "Cuboid.h"
#include "Point.h"
#include "Door.h"
#include "Window.h"
#include <GL/glut.h>
#include <iostream>

void Building::draw()
{
	float repeatX1 = 400 / 150.0f;
	float repeatY = 1.0f;
	float repeatX2 = 900 / 150.0f;


	// outer walls
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	wall1.drawWithTexture(wallTex, repeatX1, repeatY);
	wall12.drawWithTexture(wallTex, repeatX1, repeatY);
	wall13.drawWithTexture(wallTex, repeatX1, repeatY);
	wall2.drawWithTexture(wallTex, repeatX1, repeatY);
	wall3.drawWithTexture(wallTex, repeatX2 - 2, repeatY);
	wall32.drawWithTexture(wallTex, 1, 2);
	wall33.drawWithTexture(wallTex, 1, 1);
	wall4.drawWithTexture(wallTex, repeatX2 - 2, repeatY);
	glPopMatrix();

	// roof
	glPushMatrix();
	roof.drawWithTexture(wallTex, repeatX1, repeatY);
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
	bwall1.drawWithTexture(wallTex, 1, 2);
	bwall12.drawWithTexture(wallTex, repeatX1, repeatY);
	bwall13.drawWithTexture(wallTex, 1, 1);
	bwall2.drawWithTexture(wallTex, repeatX1, repeatY);
	glPopMatrix();


	// admin ground & roof
	glPushMatrix();
	broof.drawWithTexture(wallTex, repeatX1, repeatY);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	bground.drawWithTexture(groundTex, 7, 40);
	glPopMatrix();


	// doors
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	leftdoor.openWindow();
	rightdoor.openWindow();
	leftdoor.drawMovingWindow(0.7, 0.7, 0.7, true);
	rightdoor.drawMovingWindow(0.7, 0.7, 0.7, false);
	glPopMatrix();
}

void Building::toggleDoor()
{
	leftdoor.isOpen = !leftdoor.isOpen;
	rightdoor.isOpen = !rightdoor.isOpen;
}

Building::Building()
	: wall1(Point(-215, 2, -279), 150, 255, 15),
	wall12(Point(-215, 2, 278), 150, 455, 15),
	wall13(Point(-215, 89, -52), 60, 205, 15),
	wall2(Point(350, 2, 50), 150, 914, 15),
	wall3(Point(130, 2, 502), 150, 10, 460), // swap width/depth // right short (side left)
	wall32(Point(-177, 2, 502), 150, 10, 64), // right short (side right)
	wall33(Point(-122, 50, 502), 100, 12, 44), // right short (front)
	wall4(Point(70, 2, -400), 150, 10, 580), // left short
	roof(Point(65, 150, 50), 10, 916, 580), // roof
	ground(Point(50, -358, 0), 580, 1, 915), // ground
	insideWall1(Point(237, 2, -50), 150, 10, 250), // insideWall1
	insideWall2(Point(237, 2, 140), 150, 10, 200), // insideWall2
	insideWall3(Point(237, 2, 320), 150, 10, 200), // insideWall3
	/* ****************administration building******************* */
	bwall1(Point(-173, 0, 505), 100, 10, 55), // left short (side left) 
	bwall12(Point(0, 0, 505), 100, 10, 200), // left short (side right)
	bwall13(Point(-123, 50, 505), 50, 10, 46), // left short (front)
	bwall2(Point(-53, 0, 715), 100, 15, 320), // right short
	bwall3(Point(100, 0, 610), 100, 200, 15), // back wide
	bwall4(Point(-205, 0, 610), 100, 200, 15), // front wide
	broof(Point(-50, 100, 610), 1, 225, 308), // roof
	bground(Point(600, -95, 0), 308, 1, 230), // ground
	leftdoor(Point(0, -2, -215), 10, 99, 88, 0, 0, 0, 0, 1),
	rightdoor(Point(100, -2, -215), 10, 98, 88, 0, 0, 0, 0, 1)
{
	initWalls();
}


const std::vector<AABB>& Building::getWalls() const {
	return walls;
}

void Building::initWalls()
{
	wallCuboids = {
		wall1, wall12, wall13, wall2, wall3, wall32, wall33, wall4,
		insideWall1, insideWall2, insideWall3,
		bwall1, bwall12, bwall13, bwall2, bwall3, bwall4,
		roof, broof
	};

	for (const Cuboid& c : wallCuboids)
		walls.push_back(c.getAABB());

	std::cout << "building walls initialized: " << walls.size() << std::endl;
}
