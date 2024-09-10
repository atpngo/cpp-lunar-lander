#include "Lander.h"
#include <SDL.h>
#include <iostream>
#include <cmath>
#include "constants.h"

Lander::Lander(float width, float height, float x0, float y0)
{
    dimensions.width = width;
    dimensions.height = height;
    position.x = x0;
    position.y = y0;
    centerOfMass.x = dimensions.width/2;
    centerOfMass.y = dimensions.height/2;

    sdlThrustPoint.x = position.x + dimensions.width/2;
    sdlThrustPoint.y = position.y + dimensions.height;
    pGimbal = new Gimbal(90.0);
}


Lander::~Lander()
{
    delete pGimbal;
}

const Vector* Lander::GetCenterOfMass()
{
    return &centerOfMass;
}

void Lander::Update(Environment *pEnv)
{

    
    // for now, assume no mass (LMAO)
    // torque = inertia * angular accel
    // we will simplify this and just say torque = angular accel (LOL)
    // torque = FRsin(theta)
    // thrust vector
    float thrustAngle = GetThrustAngleRad();
    float thrustX = -1*thrustMagnitude * std::cos( thrustAngle );
    float thrustY = thrustMagnitude * std::sin( thrustAngle );
    thrust = {.x = thrustX, .y = thrustY};
    double F = thrustMagnitude;
    double R = dimensions.width/2;
    angularAcceleration = F * R * std::sin(DEG_TO_RAD(pGimbal->GetGimbalAngle()));
    angularAcceleration /= 200;
    angularVelocity += angularAcceleration;
    angularPosition += angularVelocity;
    // kinematics tingz
    acceleration = pEnv->GetGlobalAcceleration() + thrust;
    
    velocity += acceleration;
    position += velocity;
    if (position.y <= 0)
    {

        if (hasNotLanded)
        {
            hasNotLanded = false;
            std::cout << "You landed!" << std::endl;
            std::cout << "Velocity = " << velocity << std::endl;
            std::cout << "Acceleration = " << velocity << std::endl;
            std::cout << "Angle = " << pGimbal->GetAngleDeg()-90 << " degrees" << std::endl;
        }

        position.y = 0;
        velocity.y = 0;
        velocity.x = 0;
        angularAcceleration = 0.0;
        angularVelocity = 0.0;
        angularPosition = 90.0;
        pGimbal->SetAngle(90.0);
    }
    else
    {
        hasNotLanded = true;
    }   


    // TODO: probably should move this logic into Game.cpp
    // Internally update SDL Representation
    // from (0,0) being top left to bottom right
    // sdlLanderRect.x = -1*position.x + pEnv->GetWidth() - dimensions.width/2;
    sdlLanderRect.x = position.x;
    sdlLanderRect.y = -1*position.y + pEnv->GetHeight() - dimensions.height;
    sdlLanderRect.w = dimensions.width;
    sdlLanderRect.h = dimensions.height;

    sdlThrustPoint.x = sdlLanderRect.x;
    sdlThrustPoint.y = sdlLanderRect.y;
    // Rotate
    float theta = GetAngleRad();
    float s = std::sin(theta);
    float c = std::sin(theta);
    float px = sdlLanderRect.x;
    float py = sdlLanderRect.y;
    sdlThrustPoint.x -= px;
    sdlThrustPoint.y -= py;
    float xNew = sdlThrustPoint.x * c - sdlThrustPoint.y * s;
    float yNew = sdlThrustPoint.x * s + sdlThrustPoint.y * c;
    sdlThrustPoint.x = xNew + px;
    sdlThrustPoint.y = yNew + py;



    // Update thrust SDL
    sdlThrustRect.w = dimensions.width;
    sdlThrustRect.h = dimensions.height;
    sdlThrustRect.x = sdlLanderRect.x + sdlLanderRect.w;
    sdlThrustRect.y = sdlLanderRect.y;
    
    theta = GetThrustAngleRad();
    std::pair<double, double> rotatedPoints = RotatePoint(sdlThrustRect.x, sdlThrustRect.y, theta, sdlLanderRect.x, sdlLanderRect.y);
    sdlThrustRect.x = rotatedPoints.first;
    sdlThrustRect.y = rotatedPoints.second;
}

const SDL_Rect* Lander::GetLanderSDLRect()
{
    return &sdlLanderRect;
}   

const SDL_Rect* Lander::GetThrustSDLRect()
{
    return &sdlThrustRect;
}

float Lander::GetFuel()
{
    return (fuel/FUEL)*100;
}


void Lander::SetAcceleration(const Vector a)
{
    acceleration = a;
}

float Lander::GetAngleRad()
{
    return RAD_TO_DEG(angularPosition);
}

float Lander::GetAngleDeg()
{
    return angularPosition;
}

const Vector* Lander::GetPosition()
{
    return &position;
}

const Vector* Lander::GetVelocity()
{
    return &velocity;
}

const Vector* Lander::GetAcceleration()
{
    return &acceleration;
}

const Dimension* Lander::GetDimensions()
{
    return &dimensions;
}

void Lander::ActivateThruster()
{
    if (fuel <= 0)
    {
        std::cout << "no mas fuel" << std::endl;
        return;
    }
    thrustMagnitude = MAX_THRUST;

    
    fuel -= 1;
    isThrusterActive = true;
}

void Lander::DeactivateThruster()
{
    thrustMagnitude = 0.0;
    thrust = {.x = 0.0, .y = 0.0};
    isThrusterActive = false;
}

void Lander::TurnLeft()
{
    pGimbal->DecreaseAngle();
}
void Lander::TurnRight()
{
    pGimbal->IncreaseAngle();
}

bool Lander::IsThrusterActive()
{
    return isThrusterActive;
}


double Lander::GetGimbalWorldAngle()
{
    return pGimbal->GetAngleDeg();
}

double Lander::GetGimbalAngle()
{
    return pGimbal->GetGimbalAngle();
}

double Lander::GetThrustAngleRad()
{
    return DEG_TO_RAD(GetThrustAngleDeg());
}

double Lander::GetThrustAngleDeg()
{
    return GetAngleDeg() + pGimbal->GetGimbalAngle();
}

double Lander::GetAngularVelocity()
{
    return angularVelocity;
}
