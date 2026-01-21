#ifndef MERCEDES_H
#define MERCEDES_H

#include "Vehicle.h"
#include <string>
#include <vector>

class Mercedes : public Vehicle 
{
private:
    unsigned int m_displayListOpaque;
    unsigned int m_displayListGlass;
    
    // Position and Orientation
    float m_x, m_y, m_z;
    float m_rotY; 
    
    // Physics variables
    float m_speed;
    float m_wheelSpin;
    float m_steerAngle;
    bool m_isMovable;
    bool m_useDebugColors;

public:
    Mercedes();
    ~Mercedes();

    bool Load(const std::string& objPath, float scale = 1.0f);

    // Interface Implementation
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
};

#endif