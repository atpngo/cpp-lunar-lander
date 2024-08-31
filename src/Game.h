#ifndef GAME
#define GAME
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>

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


    private:
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
        // sample trctangle
        SDL_Rect sampleRect; 
        SDL_bool inSampleRect;
        // sample music
        Mix_Music *pMusic;


};

#endif // GAME