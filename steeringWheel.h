#pragma once
#include <string>
#include <vector>
#include <GL/freeglut.h>

class SteeringWheel
{
public:
	SteeringWheel();
	~SteeringWheel();

	bool Load(const std::string& objPath, float scale = 1.0f);
	void Draw();

	void SetPosition(float x, float y, float z);
	void SetRotationY(float angle);
	void SetRotationZ(float angle);

private:
	GLuint m_displayList;

	float m_x, m_y, m_z;
	float m_rotY;
	float m_rotZ;
};

