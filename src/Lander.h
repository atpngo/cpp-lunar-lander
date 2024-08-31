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
        const SDL_Rect *GetSDLRect();
        

    private:
        SDL_Rect sdlRect = {.x = 0, .y = 0, .w = 0, .h = 0};
        Dimension dimensions = {.width = 0.0, .height = 0.0};
        Vector position = {.x = 0.0, .y = 0.0};
        Vector velocity = {.x = 0.0, .y = 0.0};
        Vector acceleration = {.x = 0.0, .y = 0.0};
        


};

#endif // LANDER