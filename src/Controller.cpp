#include "Controller.h"
#include <iostream>
#include "constants.h"
#include <algorithm>

Controller::Controller(double p, double i, double d)
{
    Kp = p;
    Ki = i;
    Kd = d;
}

Controller::~Controller()
{

}

bool Controller::MoveToY(double py, double vy, double targetAltitude)
{
    long double PID = Kp*(targetAltitude - py) - Kd*vy;
    return PID > 0;
}


/*
theta - the rocket's angle in the real world relative to the horizon
*/
double Controller::MoveToAngle(double theta, double omega, double targetAngle, double gimbalAngle, double vx)
{
    // std::cout << theta-targetAngle << std::endl;
    double PID = Kp*(theta-targetAngle) + Kd*(omega) + gimbalAngle + (100)*vx;
    return PID;
}