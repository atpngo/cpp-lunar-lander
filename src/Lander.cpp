#include "Lander.h"
#include <SDL.h>
#include <iostream>
#include <cmath>

Lander::Lander(float width, float height, float x0, float y0)
{
    dimensions.width = width;
    dimensions.height = height;
    position.x = x0;
    position.y = y0;
}


Lander::~Lander()
{

}

void Lander::Update(Environment *pEnv)
{

    // kinematics tingz
    acceleration = pEnv->GetGlobalAcceleration() + thrust;
    velocity += acceleration;
    position += velocity;
    if (position.y - dimensions.height <= 0)
    {

        if (hasNotLanded)
        {
            hasNotLanded = false;
            std::cout << "You landed!" << std::endl;
            std::cout << "Velocity = " << velocity << std::endl;
            std::cout << "Acceleration = " << velocity << std::endl;
            std::cout << "Angle = " << angle-90 << " degrees" << std::endl;
        }
        // todo: perhaps create some type of "distance sensor" to abstract environment
        // todo: model actual physics collision w/ the ground (impulse, momentum and stuff)
        position.y = dimensions.height;
        velocity.y = 0;
        velocity.x = 0;
        angle = 90.0;
    }
    else
    {
        hasNotLanded = true;
    }   


    // TODO: probably should move this logic into Game.cpp
    // Internally update SDL Representation
    // from (0,0) being top left to bottom right
    sdlLanderRect.x = -1*position.x + pEnv->GetWidth();
    sdlLanderRect.y = -1*position.y + pEnv->GetHeight();
    sdlLanderRect.w = dimensions.width;
    sdlLanderRect.h = dimensions.height;

    // Update thrust SDL
    sdlThrustRect.w = dimensions.width;
    sdlThrustRect.h = dimensions.height;
    sdlThrustRect.x = sdlLanderRect.x + sdlLanderRect.w;
    sdlThrustRect.y = sdlLanderRect.y;
    
    float s = std::sin(GetAngleRad());
    float c = std::cos(GetAngleRad());

    float px = sdlLanderRect.x;
    float py = sdlLanderRect.y;
    sdlThrustRect.x -= px;
    sdlThrustRect.y -= py;
    // // Rotate
    float xNew = sdlThrustRect.x * c - sdlThrustRect.y * s;
    float yNew = sdlThrustRect.x * s + sdlThrustRect.y * c;
    sdlThrustRect.x = xNew + px;
    sdlThrustRect.y = yNew + py;
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
    return fuel;
}


void Lander::SetAcceleration(const Vector a)
{
    acceleration = a;
}

float Lander::GetAngleRad()
{
    return angle*PI/180.0;
}

float Lander::GetAngleDeg()
{
    return angle;
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

    float thrustX = MAX_THRUST * std::cos(GetAngleRad());
    float thrustY = MAX_THRUST * std::sin(GetAngleRad());
    thrust = {.x = thrustX, .y = thrustY};
    fuel -= 1;
}

void Lander::DeactivateThruster()
{
    thrust = {.x = 0.0, .y = 0.0};
}

void Lander::TurnLeft()
{
    angle -= 1;
    angle = std::fmod(angle, 360.0);
}
void Lander::TurnRight()
{
    angle += 1;
    angle = std::fmod(angle, 360.0);
}

