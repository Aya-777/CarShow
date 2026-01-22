//#pragma once
//#ifndef BUILDING_H
//#define BUILDING_H
//#include "Cuboid.h"
//#include "Door.h"
//#include "Window.h"
//#include <iostream>
//#include <vector>
//#include "aabb.h"
//
//#include <GL/glut.h>
//
//class Building {
//public:
//	Building();
//	Building(double x, double y, double z, double w, double h, double l,Window leftdoor, Window rightdoor);
//	void draw();
//	void toggleDoor();
//	double width, height, length, x, y, z;
//	GLuint wallTex, wallTex2, groundTex;
//	Window leftdoor, rightdoor;
//	std::vector<AABB> walls;
//	const std::vector<AABB>& getWalls() const;
//	void buildingInit();
//
//private:
//};
//
//#endif

#pragma once
#ifndef BUILDING_H
#define BUILDING_H

#include <vector>
#include "Cuboid.h"
#include "Window.h"
#include "aabb.h"

class Building {
public:
    Building();

    void draw();
    void toggleDoor();

    const std::vector<AABB>& getWalls() const;

    GLuint wallTex, wallTex2, groundTex;


	Cuboid wall1 // front wide
		, wall12 // front door (side left)
		, wall13 // front door (side right)
		, wall2 // back wide
		, wall3 // right short (side left)
		, wall32 // right short (side right)
		, wall33 // left short (front)
		, wall4 // left short
		, roof // roof
		, ground // ground
		, insideWall1 // insideWall1
		, insideWall2 // insideWall2
		, insideWall3 // insideWall3
		, bwall1 // left short (side right)
		, bwall12 // left short (side left)
		, bwall13 // left short (front)
		, bwall2 // right short
		, bwall3 // back wide
		, bwall4 // front wide
		, broof // roof
		, bground; // ground

public:
    std::vector<Cuboid> wallCuboids;

    // COLLISION BOXES
    std::vector<AABB> walls;

    // Doors
    Window leftdoor;
    Window rightdoor;

    void initWalls(); 
};

#endif
