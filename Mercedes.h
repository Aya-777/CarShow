#ifndef MERCEDES_H
#define MERCEDES_H

#include "Vehicle.h"  // Add this
#include <string>

class Mercedes : public Vehicle  // Add inheritance
{
private:
    unsigned int m_displayListOpaque;
    unsigned int m_displayListGlass;
    float m_x, m_y, m_z;
    float m_rotY;
    bool m_useDebugColors;

    // Add movement variables
    float m_speed;
    float m_wheelSpin;
    float m_steerAngle;
    bool m_isMovable;

public:
    Mercedes();
    ~Mercedes();

    bool Load(const std::string& objPath, float scale = 1.0f);

    // Implement Vehicle interface
    void Draw() override;
    void Update() override;
    void EnterVehicle(bool enter) override;
    bool CanBeEntered() const override { return true; }

    Point GetPosition() const override { return Point(m_x, m_y, m_z); }
    float GetRotationY() const override { return m_rotY; }
    std::string GetName() const override { return "Mercedes"; }

    void MoveForward(float step) override;
    void MoveBackward(float step) override;
    void RotateLeft(float angle) override;
    void RotateRight(float angle) override;

    Point GetDriverSeatPosition() const override;
    float GetDriverViewYaw() const override;

    void SetPosition(float x, float y, float z);
    void SetRotationY(float angle);
    void SetDebugColors(bool enable);
};

#endif