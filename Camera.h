#ifndef __CAMERA_H__
#define __CAMERA_H__
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#include <iostream>
#include <vector>
#include "Door.h"
#include "Point.h"

struct Wall {
	Point min;//?????? ??????? ?????? ???????? 
	Point max;//?????? ??????? ?????? ??????? 
};

class Camera
{
	public:
		Camera() { Init(); }
		~Camera() {}

		void Init();
		void Refresh();
		Point GetPos();
		void SetPos(float x, float y, float z);
		void GetPos(float& x, float& y, float& z);
		void GetDirectionVector(float& x, float& y, float& z);
		void SetYaw(float angle);
		void SetPitch(float angle);
		bool CheckCollision(const Point& newPos);
		bool CheckDoorCollision(const Point& newPos);
		void openNearestDoor();
		// Navigation
		void Move(float incr);
		void Strafe(float incr);
		void Fly(float incr);
		void RotateYaw(float angle);
		void RotatePitch(float angle);

		std::vector<Door*> Doors;
		std::vector<Door*> ElevetorDoors;
		std::vector<Wall> doorWalls{
			{Point(151.668,11.6564,-32.3706),Point(157.606,35.3446,-19.1159)},//??? ?????? 
		};

		std::vector<Wall> walls = {

			// mall 
			//{Point(-7.20473,2.10463,-326.21),Point(218.896,13.067,2.14833)},//?????? ??? ??? ????? ????? 
			//{Point(150.905,62.1459,-190.26),Point(156.874,81.5486,-183.352)},//????? ??? ??? ???? ??? ????????? 
			// Furniture Store

			// Super Market
			};
		//Elevator elevator;

	private:
		float m_x, m_y, m_z;   // Position
		float m_lx, m_ly, m_lz; // Direction vector of where we are looking at
		float m_yaw, m_pitch; // Various rotation angles
		float m_strafe_lx, m_strafe_lz; // Always 90 degree to direction vector
};

#endif