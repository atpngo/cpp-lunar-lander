#ifndef LANDER
#define LANDER

#include "Environment.h"
#include "SDL.h"
#include "constants.h"
#include "Gimbal.h"

class Lander
{
    public:
        Lander(float width, float height, float x0, float y0);
        ~Lander();
        void Update(Environment *pEnv);
        void SetAcceleration(const Vector a);
        const SDL_Rect *GetLanderSDLRect();
        const SDL_Rect *GetThrustSDLRect();

        // State
        float GetFuel();
        float GetAngleRad();
        float GetAngleDeg();

        const Dimension *GetDimensions();
        const Vector *GetPosition();
        const Vector *GetVelocity();
        const Vector *GetAcceleration();
        const Vector *GetCenterOfMass();

        double GetGimbalWorldAngle();
        double GetGimbalAngle();
        double GetThrustAngleRad();
        double GetThrustAngleDeg();
        
        // Setters
        void ActivateThruster();
        void DeactivateThruster();
        void TurnLeft();
        void TurnRight();

        bool IsThrusterActive();


        // Delete
        // Center points
        float GetLanderX() { return sdlLanderRect.x+sdlLanderRect.w/2; };
        float GetLanderY() { return sdlLanderRect.y+sdlLanderRect.h/2; };
        float GetThrustX() { return sdlThrustRect.x+sdlThrustRect.w/2; };
        float GetThrustY() { return sdlThrustRect.y+sdlThrustRect.h/2; };

        // Get Thrust point
        SDL_Point* GetThrustPoint() { return &sdlThrustPoint; }

        

    private:
    // should probably move this somewhere later
        SDL_Rect sdlLanderRect = {.x = 0, .y = 0, .w = 0, .h = 0};
        SDL_Rect sdlThrustRect = {.x = 0, .y = 0, .w = 0, .h = 0};
        SDL_Point sdlThrustPoint;

        bool hasNotLanded = true;
        Dimension dimensions = {.width = 0.0, .height = 0.0};
        Vector position = {.x = 0.0, .y = 0.0};
        Vector velocity = {.x = 0.0, .y = 0.0};
        Vector acceleration = {.x = 0.0, .y = 0.0};
        Vector centerOfMass;
        float angularAcceleration = 0.0;
        float angularVelocity = 0.0;
        float angularPosition = 90.0;
        float fuel = FUEL;
        float mass = 100; // kg
        Vector thrust = {.x = 0.0, .y = 0.0};
        float thrustMagnitude = 0.0;
        bool isThrusterActive;

        Gimbal *pGimbal;


};

#endif // LANDER