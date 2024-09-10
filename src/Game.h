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
#include "NetworkUtility.h"
#include "Controller.h"

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
        void Log();
        void Autonomous();

        int GetMouseX();
        int GetMouseY();



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
        Mix_Chunk *pThrustSFX;

        // Lander texture
        SDL_Texture *pLanderTexture;
        SDL_Texture *pThrustTexture;

        // Sprite Rect
        SDL_Rect thrustSpriteLocation = {.x=0, .y=0, .w=50, .h=50};
        uint32_t thrustSpriteIndex = 0;

        // POG MY DOG
        Environment *pEnv;
        Lander *pLander;

        // Log
        NetworkUtility *pSocket;

        // Controls
        Controller *pYController;
        Controller *pXController;
        Controller *pRotationController;


        // Frame rate
        float currTick;
        float prevTick;
        float deltaTime;

        // mouse position
        int mouseX = 0;
        int mouseY = 0;

        double x2;
        double y2;

};

#endif // GAME