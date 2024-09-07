#include "Gimbal.h"
#include <algorithm>
#include "constants.h"
#include <iostream>

Gimbal::Gimbal(double initialAngle)
{
    angularPosition = initialAngle;
    angularVelocity = 1.0;
    angularAcceleration = 0.0;
    minAngle = 90-GIMBAL_MAX_ANGLE_RANGE;
    maxAngle = 90+GIMBAL_MAX_ANGLE_RANGE;
}

// TODO: the gimbal exerts torque on the rocket itself....
// rocket needs to have its own angular pos, vel, acc


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

double Gimbal::GetAngle()
{
    return angularPosition;
}