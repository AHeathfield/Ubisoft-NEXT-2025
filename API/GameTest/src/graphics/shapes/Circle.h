// Circle.h
#pragma once
// Might use
class Circle
{
public:
    physics::Vector3 position;
    float radius;

    Circle() : position(physics::Vector3()), radius(0) {}
    Circle(const physics::Vector3& _position, float _radius) : position(_position), radius(_radius) {}
    Circle(float _x, float _y, float _radius) : position(physics::Vector3(_x, _y, 0.0f)), radius(_radius) {}
};