#pragma once
class Point
{
public:
	Point(double x, double y, double z);
	Point();
	double x, y, z;
	Point operator+(const Point& other) const {
		return Point(x + other.x, y + other.y, z + other.z);
	}
};