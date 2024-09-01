#ifndef ENVIRONMENT
#define ENVIRONMENT

#include "constants.h"

class Environment
{
    public:
        Environment(float width, float height);
        ~Environment();
        Dimension GetBoundaries();
        float GetWidth();
        float GetHeight();
        const Vector GetGlobalAcceleration();

    private:
        Dimension d;
        // const float GRAVITY = -9.807; // m/s^2  
        const Vector GRAVITY = {.x = 0.0, .y = GRAVITY_Y}; // m/s^2  

};


#endif // ENVIRONMENT