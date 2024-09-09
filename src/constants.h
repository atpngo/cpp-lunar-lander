#ifndef CONSTANTS
#define CONSTANTS

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>
#include <format>
#include <algorithm>

// Classes
struct Vector
{
    double x, y;

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
const int LANDER_INITIAL_Y = 600; // meters 
// const int LANDER_INITIAL_Y = 0; // meters 
const float FUEL = 200000; // liters of fuel
// TODO: IDEAL ROCKET EQUATION STUFF
const double LANDER_DRY_MASS = 22200; // kilograms
const double FUEL_DENSITY = 0.81; // kg/L >
const double LANDER_WET_MASS = FUEL*FUEL_DENSITY; // 

// GIMBAL
const double GIMBAL_MAX_ANGLE_RANGE = 10.5; // +/- DEGREES

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

inline double Sigmoid(double x)
{
    return 1/(1+std::pow(EULER, x));
}

inline double DEG_TO_RAD(double deg)
{
    return deg*PI/180;
}

inline double RAD_TO_DEG(double rad)
{
    return rad*180/PI;
}

inline double GetMagnitude(const Vector* v)
{
    return std::hypot(v->x, v->y);
}

/*
ve - exhaust velocity (m/s)
m0 - initial mass (kg)
mf - final mass (kg)
*/
inline double IdealRocketEquation(double ve, double m0, double mf)
{
    return 0.0;
}

/*
angle is in RADIANS
rotate (x, y) about (originX, originY)
*/
inline std::pair<double, double> RotatePoint(double x, double y, double angle, double originX, double originY)
{
    std::pair<double, double> new_points;
    double s = std::sin(angle);
    double c = std::cos(angle);
    x -= originX;
    y -= originY;
    double x_new = x*c - y*s;
    double y_new = x*s + y*c;
    x = x_new + originX;
    y = y_new + originY;

    new_points.first = x;
    new_points.second = y;

    return new_points;
}

inline double clamp(double number, double min, double max)
{
    if (number < min)
        return min;
    if (number > max)
        return max;
    return number;
}


inline double GetAngleBetweenPoints(double x1, double y1, double x2, double y2)
{
    // x1 and y1 is our origin
    return -1*RAD_TO_DEG(std::atan2( (y2-y1), (x2-x1) )) + 180;
}

#endif // CONSTANTS