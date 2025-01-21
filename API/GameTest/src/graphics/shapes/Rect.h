// Rectangle.h
#pragma once

class Rect
{
public:
    physics::Vector3 position;
    float w, h; // Maybe do floats

    Rect() : position(physics::Vector3()), w(0), h(0) {}
    Rect(const physics::Vector3& _position, float _w, float _h) : position(_position), w(_w), h(_h) {}
    Rect(float _x, float _y, float _w, float _h) : position(physics::Vector3(_x, _y, 0.0f)), w(_w), h(_h) {}
};