#pragma once
#ifndef VEHICLE_H
#define VEHICLE_H

#include "Point.h"
#include <string>
#include <cmath> 

class Vehicle
{
public:
    virtual ~Vehicle() {}

    // Pure virtual methods that all vehicles must implement
    virtual void Draw() = 0;
    virtual void Update() = 0;
    virtual void EnterVehicle(bool enter) = 0;
    virtual bool CanBeEntered() const = 0;

    virtual Point GetPosition() const = 0;
    virtual float GetRotationY() const = 0;
    virtual std::string GetName() const = 0;

    // Common movement methods
    virtual void MoveForward(float step) = 0;
    virtual void MoveBackward(float step) = 0;
    virtual void RotateLeft(float angle) = 0;
    virtual void RotateRight(float angle) = 0;

    // For camera positioning
    virtual Point GetDriverSeatPosition() const = 0;
    virtual float GetDriverViewYaw() const = 0;

    // Check distance to point
    virtual float DistanceTo(const Point& point) const
    {
        Point pos = GetPosition();
        float dx = pos.x - point.x;
        float dy = pos.y - point.y;
        float dz = pos.z - point.z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }
};

#endif