#include "Building.h"
#include "Cuboid.h"
#include "Point.h"
#include <GL/glut.h>


void Building::draw() {
	Cuboid building(Point(0, 0, 0), 100, 650, 300);
	glColor3f(0.8, 0.8, 0.8);
	Cuboid wall1(Point(45, 0, -120), 100, 10, 210);
	Cuboid wall2(Point(45, 0, 30), 100, 10, 150);
	Cuboid wall3(Point(45, 0, 160), 100, 10, 150);
	wall1.draw();	
	wall2.draw();
	wall3.draw();
	glColor4f(0.2f, 0.3f, 0.8f, 0.5f); // 50% transparent white
	building.draw();

	Cuboid administrationBuilding(Point(-75,0,365), 100, 80, 150);
	administrationBuilding.draw();

	

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