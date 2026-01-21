#pragma once
#include <cmath>
class Point
{
public:
	Point(double x, double y, double z);
	Point();
	double x, y, z;
	Point operator+(const Point& other) const {
		return Point(x + other.x, y + other.y, z + other.z);
	}
	float dist(const Point& other) const {
		float dx = x - other.x;
		float dy = y - other.y;
		float dz = z - other.z;
		return sqrt(dx * dx + dy * dy + dz * dz);
	}
};