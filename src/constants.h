#ifndef CONSTANTS
#define CONSTANTS

#include <iostream>
#include <cmath>
// Classes
struct Vector
{
    float x, y;

    Vector operator+(const Vector &rhs) const {
        return Vector{x+rhs.x, y+rhs.y};
    }

    struct Vector& operator+=(const Vector &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vector operator-(const Vector &rhs) const {
        return Vector{x-rhs.x, y-rhs.y};
    }

    struct Vector& operator-=(const Vector &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    struct Vector& operator=(const Vector &rhs) {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
        os << "Vector(x=" << vec.x << ", y=" << vec.y  << ")";
        return os;
    }

    float GetMagnitude()
    {
        return std::sqrt(x*x + y*y);
    }

};

const float FUEL = 1000000;
const float MAX_THRUST = 0.12; // Newtons
const float GRAVITY_Y = -0.08; // Newtons
// const float MAX_THRUST = 0.0; // Newtons
// const float GRAVITY_Y = 0.0; // Newtons
const float PI = 3.14159265;




struct Dimension
{
    float width, height;
};


// Colors


#endif // CONSTANTS