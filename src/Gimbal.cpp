#include "Gimbal.h"
#include <algorithm>
#include "constants.h"
#include <iostream>

Gimbal::Gimbal(double initialAngle)
{
    angularPosition = initialAngle;
    angularVelocity = 0.5;
    angularAcceleration = 0.0;
    minAngle = 90-GIMBAL_MAX_ANGLE_RANGE;
    maxAngle = 90+GIMBAL_MAX_ANGLE_RANGE;
}



Gimbal::~Gimbal()
{

}

void Gimbal::SetAngle(double angle)
{
    angularPosition = std::min(std::max(angle, minAngle), maxAngle);
}


void Gimbal::DecreaseAngle()
{
    angularPosition = std::max(angularPosition-angularVelocity, minAngle);
}

void Gimbal::IncreaseAngle()
{
    angularPosition = std::min(maxAngle, angularPosition+angularVelocity);
}

double Gimbal::GetAngleDeg()
{
    return angularPosition;
}

double Gimbal::GetAngleRad()
{
    return DEG_TO_RAD(angularPosition);
}

double Gimbal::GetGimbalAngle()
{
    return angularPosition-90;
}