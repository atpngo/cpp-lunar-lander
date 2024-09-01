#ifndef GAME
#define GAME
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include "Lander.h"
#include "Environment.h"
#include <map>

class Game 
{
    public:
        Game(std::string title, int width, int height);
        ~Game();

        void Init();
        void HandleEvents();
        void Update();
        void Render();
        void CleanUp();
        bool IsRunning();
        void Run();


    private:
        std::map<int,bool> KEYS;
        void HandleMouseDrag(SDL_Event e);
        SDL_Window *pWindow;
        SDL_Renderer *pRenderer;
        TTF_Font *pFont;

        SDL_Event event;
        SDL_bool isRunning = SDL_TRUE;
        SDL_Color white = {255, 255, 255};

        int windowWidth;
        int windowHeight;

        SDL_Rect headerTextRect;
        SDL_Texture *pHeaderText;
        // sample texture
        SDL_Texture *pImage;
        // sample music
        Mix_Music *pMusic;

        // Lander texture
        SDL_Texture *pLanderTexture;
        SDL_Texture *pThrustTexture;

        // POG MY DOG
        Environment *pEnv;
        Lander *pLander;

        // Frame rate
        float currTick;
        float prevTick;
        float deltaTime;

};

#endif // GAME