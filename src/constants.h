#ifndef CONSTANTS
#define CONSTANTS

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>
#include <format>

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

const float FUEL = 1000;
const float MAX_THRUST = 0.12; // Newtonss
const float GRAVITY_Y = -0.08; // Newtons
// const float MAX_THRUST = 0.0; // Newtons
// const float GRAVITY_Y = 0.0; // Newtons
const float PI = 3.14159265;

const std::string SERVER_ADDRESS = "127.0.0.1";
const unsigned int SERVER_PORT = 3490;




struct Dimension
{
    float width, height;
};

inline std::string GetVectorAsString(std::vector<float> v, int precision = 6)
{
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(5);
    for (size_t i=0; i<v.size(); i++)
    {
        if (i != 0)
            ss << ",";
        ss << v[i];
    }
    return ss.str();
}


// Colors


#endif // CONSTANTS