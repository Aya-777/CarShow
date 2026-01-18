//#pragma once
//#include "Point.h"
//class Sofa
//{
//	//new
//private:
//	Point center; // sofa position
//	//***//
//public:
//	Sofa(Point c);       // constructor with position new
//	void setPosition(Point c);  // move sofa new 
//	//void draw(Point center);
//	void draw();
//	//void drawTriple(Point center);
//	void drawTriple();    // optional triple sofa
//};
//

#pragma once
#include "Point.h"

class Sofa
{
private:
    Point center;    // sofa position
    float rotation;  // rotation angle in degrees around Y-axis

public:
    Sofa(Point c);

    void setPosition(Point c);     // move sofa
    void setRotation(float angle); // rotate sofa

    void draw();       // single sofa
    void drawTriple(); // optional triple sofa
};

