#include "Lander.h"
#include <SDL.h>


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
    if (position.y + dimensions.height < pEnv->GetHeight())
    {
        position.y += 1;
    }

    if (position.y > 0)
    {
        if (KEYS[SDLK_UP]) {
            position.y -= 2;
        }
    }

    sdlRect.x = position.x;
    sdlRect.y = position.y;
    sdlRect.w = dimensions.width;
    sdlRect.h = dimensions.height;
}

const SDL_Rect* Lander::GetSDLRect()
{
    return &sdlRect;
}   
