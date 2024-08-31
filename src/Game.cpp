#include "Game.h"
#include <iostream>
Game::Game(std::string title, int width, int height)
{
    pWindow = nullptr;
    pRenderer = nullptr;
    pFont = nullptr;
    pHeaderText = nullptr;
    pImage = nullptr;
    pMusic = nullptr;

    sampleRect = {.x = 10, .y = 10, .w = 100, .h = 100};
    inSampleRect = SDL_FALSE;

    windowWidth = width;
    windowHeight = height;

}

Game::~Game()
{
    std::cout << "dtor called" << std::endl;
}


void Game::Init()
{
    // Init SDL2
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "[ERROR] SDL Init: " << SDL_GetError() << std::endl;
    }
    else
    {
        std::cout << "SDL INITIALIZED" << std::endl;
        SDL_DisplayMode dm;
        SDL_GetCurrentDisplayMode(0, &dm);
        std::cout << "Current display mode is " << dm.w << "x" << dm.h << " @ " << dm.refresh_rate << std::endl;
    }

    // Init window and rednerer
    if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) != 0) 
    {
        std::cout << "[Error] Creating Window and Renderer: " << SDL_GetError() << std::endl;
        exit(0);
    }
    else 
    {
        std::cout << "Created window and renderer with dimensions " << windowWidth << "x" << windowHeight << std::endl;
    }

    // init ttf
    TTF_Init();
    // init audio
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
    {
        std::cout << "[Error] Error initializing audio" << std::endl;
    }
    else
    {
        std::cout << "Audio initialized" << std::endl;
    }

    // Setup app icon
    SDL_Surface *pIconSurface = IMG_Load("resources/appicon.jpg");

    SDL_SetWindowIcon(pWindow, pIconSurface);
    SDL_FreeSurface(pIconSurface);

    // Setup header text
    pFont = TTF_OpenFont("resources/OpenSans-Regular.ttf", 18);

    SDL_Surface *pTextSurface = TTF_RenderText_Blended(pFont, "Skibidi toilet rizz (press ESC to close)", white);
    
    pHeaderText = SDL_CreateTextureFromSurface(pRenderer, pTextSurface);

    headerTextRect.x = windowWidth/2 - pTextSurface->w/2;
    headerTextRect.y = 0;
    headerTextRect.w = pTextSurface->w;
    headerTextRect.h = pTextSurface->h;
    SDL_FreeSurface(pTextSurface);
    pTextSurface = nullptr;

    // Setup sample image
    pImage = nullptr;
    SDL_Surface *pLoadedSurface = IMG_Load("resources/floor.png");
    if (pLoadedSurface == nullptr)
    {
        std::cout << "[Error] Unable to load image: " << SDL_GetError() << std::endl;
        exit(0);
    }


    pImage = SDL_CreateTextureFromSurface(pRenderer, pLoadedSurface);
    if (pImage == nullptr)
    {
        std::cout << "[Error] Unable to create texture: " << SDL_GetError() << std::endl;
    }


    SDL_FreeSurface(pLoadedSurface);

    
    // Play audio
    pMusic = Mix_LoadMUS("resources/sound.ogg");
    if (Mix_PlayMusic(pMusic, -1) != 0)
    {
        std::cout << "[Error] Could not play music: " << SDL_GetError() << std::endl;
    }

}

void Game::HandleMouseDrag(SDL_Event e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point p = {.x = e.motion.x, .y = e.motion.y};
        if (SDL_PointInRect(&p, &sampleRect))
        {
            inSampleRect = SDL_TRUE;
        }
    }

    if (e.type == SDL_MOUSEBUTTONUP && inSampleRect == SDL_TRUE)
    {
        inSampleRect = SDL_FALSE;
    }

    if (e.type == SDL_MOUSEMOTION && inSampleRect == SDL_TRUE)
    {
        sampleRect.x += e.motion.xrel;
        sampleRect.y += e.motion.yrel;
    }
}

bool Game::IsRunning()
{
    return isRunning == SDL_TRUE;
}

void Game::HandleEvents()
{
    while (SDL_PollEvent(&event)) 
    {
        if (event.type == SDL_QUIT)
            isRunning = SDL_FALSE;
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    isRunning = SDL_FALSE;
                    break;
                default:
                    isRunning = SDL_TRUE;
            }
        }
        // Handle da mouse drag
        HandleMouseDrag(event);
    }
}

void Game::Update() // this is ur int main
{
    // do stuff with internal objects here meow meow meow

    
}

void Game::Render()
{
    // Renderer
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);
    SDL_RenderClear(pRenderer);

    // render sample texture
    SDL_RenderCopy(pRenderer, pImage, nullptr, nullptr);
    // Render rectangle
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 1);
    SDL_RenderFillRect(pRenderer, &sampleRect);
    // render text
    SDL_RenderCopy(pRenderer, pHeaderText, nullptr, &headerTextRect);
    // Presnet to renderer
    SDL_RenderPresent(pRenderer);
    SDL_Delay(10);
}


void Game::CleanUp()
{
    if (Mix_PlayingMusic())
    {
        Mix_HaltMusic();
    }

    Mix_FreeMusic(pMusic);
    Mix_CloseAudio();

    SDL_DestroyTexture(pHeaderText);
    SDL_DestroyTexture(pImage);
    TTF_CloseFont(pFont);
    TTF_Quit();
    SDL_DestroyWindow(pWindow);
    SDL_Quit();

}