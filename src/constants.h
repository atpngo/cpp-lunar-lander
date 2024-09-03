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

const float FUEL = 10000000;
const float MAX_THRUST = 0.12; // Newtonss
const float GRAVITY_Y = -0.08; // Newtons
// const float MAX_THRUST = 0.0; // Newtons
// const float GRAVITY_Y = 0.0; // Newtons
const double PI = 3.14159265;
const double EULER = 2.71828182845904523536;

const std::string SERVER_ADDRESS = "127.0.0.1";
const unsigned int SERVER_PORT = 3490;

const bool AUDIO_ON = false;
const float DT = 1/60;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 900;

// Lander
const int LANDER_WIDTH = 50;
const int LANDER_HEIGHT = 50;
const int LANDER_INITIAL_X = WINDOW_WIDTH/2;
const int LANDER_INITIAL_Y = 1000; // meters 
// const int LANDER_INITIAL_Y = 0; // meters 


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

inline float Sigmoid(float x)
{
    return 1/(1+std::pow(EULER, x));
}

// Colors


#endif // CONSTANTS