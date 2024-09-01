#ifndef LANDER
#define LANDER

#include <vector>
#include <map>
#include "Environment.h"
#include "SDL.h"
#include "constants.h"

class Lander
{
    public:
        Lander(float width, float height, float x0, float y0);
        ~Lander();
        void Update(std::map<int,bool> KEYS, Environment *pEnv);
        const SDL_Rect *GetLanderSDLRect();
        const SDL_Rect *GetThrustSDLRect();
        float GetFuel();
        void SetAcceleration(const Vector a);
        float GetAngleRad();
        float GetAngleDeg();

        // Delete
        float GetLanderX() { return sdlLanderRect.x+sdlLanderRect.w/2; };
        float GetLanderY() { return sdlLanderRect.y+sdlLanderRect.h/2; };
        float GetThrustX() { return sdlThrustRect.x+sdlThrustRect.w/2; };
        float GetThrustY() { return sdlThrustRect.y+sdlThrustRect.h/2; };
        

    private:
        bool hasNotLanded = true;
        SDL_Rect sdlLanderRect = {.x = 0, .y = 0, .w = 0, .h = 0};
        SDL_Rect sdlThrustRect = {.x = 0, .y = 0, .w = 0, .h = 0};
        SDL_Point sdlPoint = {.x = 0, .y = 0};
        Dimension dimensions = {.width = 0.0, .height = 0.0};
        Vector position = {.x = 0.0, .y = 0.0};
        Vector velocity = {.x = 0.0, .y = 0.0};
        Vector acceleration = {.x = 0.0, .y = 0.0};
        float fuel = FUEL;
        float mass = 100; // kg
        Vector thrust = {.x = 0.0, .y = 0.0};
        float angle = 90.0; // degrees


};

#endif // LANDER