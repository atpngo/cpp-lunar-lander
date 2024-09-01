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

void Lander::Update(std::map<int,bool> KEYS, Environment *pEnv)
{
    // Handle thrust input (up arrow)
    if (KEYS[SDLK_UP] && fuel > 0) {
        float thrustX = MAX_THRUST * std::cos(GetAngleRad());
        float thrustY = MAX_THRUST * std::sin(GetAngleRad());
        thrust = {.x = thrustX, .y = thrustY};
        fuel -= 1;
        if (fuel == 0)
            std::cout << "no mas fuel" << std::endl;
    }
    else
    {
        thrust = {.x = 0.0, .y = 0.0};
    }

    // Handle rotation (left/right arrows)
    if (KEYS[SDLK_LEFT]) 
    {
        angle -= 1;
    }
    if (KEYS[SDLK_RIGHT])
    {
        angle += 1;
    }
    angle  = std::fmod(angle, 360.0);

    // kinematics tingz
    acceleration = pEnv->GetGlobalAcceleration() + thrust;
    velocity += acceleration;
    position -= velocity;
    // GRAVITY  
    if (position.y + dimensions.height >= pEnv->GetHeight())
    {
        // we r on the ground
        if (hasNotLanded)
        {
            hasNotLanded = false;
            std::cout << "You landed!" << std::endl;
            std::cout << "Velocity = " << velocity << std::endl;
            std::cout << "Acceleration = " << velocity << std::endl;
            std::cout << "Angle = " << angle-90 << " degrees" << std::endl;
        }
        position.y = pEnv->GetHeight() - dimensions.height;
        velocity.y = 0;
        velocity.x = 0;
        angle = 90.0;
    }
    else
    {
        hasNotLanded = true;
    }

    // std::cout << "Acceleration: " << acceleration << std::endl;

    // Internally update SDL Representation
    sdlLanderRect.x = position.x;
    sdlLanderRect.y = position.y;
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

