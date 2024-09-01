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

    pLanderTexture = nullptr;
    pThrustTexture = nullptr;

    pEnv = nullptr;
    pLander = nullptr;

    currTick = 0.0;
    prevTick = 0.0;
    deltaTime = 0.0;

    windowWidth = width;
    windowHeight = height;
    
}

Game::~Game()
{
    std::cout << "dtor called" << std::endl;
    delete pEnv;
    delete pLander;
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

    SDL_Surface *pTextSurface = TTF_RenderText_Blended(pFont, "LunarLander v1 (press ESC to close)", white);
    
    pHeaderText = SDL_CreateTextureFromSurface(pRenderer, pTextSurface);

    headerTextRect.x = windowWidth/2 - pTextSurface->w/2;
    headerTextRect.y = 0;
    headerTextRect.w = pTextSurface->w;
    headerTextRect.h = pTextSurface->h;
    SDL_FreeSurface(pTextSurface);

    SDL_Surface *pLoadedSurface = IMG_Load("resources/space.jpg");
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


    
    // Load lander sprite
    SDL_Surface *pLanderSurface = IMG_Load("resources/lander.jpeg");
    if (pLanderSurface == nullptr)
    {
        std::cout << "[Error] Unable to load image: " << SDL_GetError() << std::endl;
        exit(0);
    }
    pLanderTexture = SDL_CreateTextureFromSurface(pRenderer, pLanderSurface);
    if (pLanderTexture == nullptr)
    {
        std::cout << "[Error] Unable to create texture: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(pLanderSurface);

    // Load thrust sprite
    SDL_Surface *pThrustSurface = IMG_Load("resources/thrust.jpeg");
    if (pThrustSurface == nullptr)
    {
        std::cout << "[Error] Unable to load image: " << SDL_GetError() << std::endl;
        exit(0);
    }
    pThrustTexture = SDL_CreateTextureFromSurface(pRenderer, pThrustSurface);
    if (pThrustTexture == nullptr)
    {
        std::cout << "[Error] Unable to create texture: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(pThrustSurface);

    
    // Play audio
    // pMusic = Mix_LoadMUS("resources/sound.ogg");
    // if (Mix_PlayMusic(pMusic, -1) != 0)
    // {
    //     std::cout << "[Error] Could not play music: " << SDL_GetError() << std::endl;
    // }
    // create env
    pEnv = new Environment(windowWidth, windowHeight);
    // Create rocket
    pLander = new Lander(50, 50, windowWidth/2 - 50/2, 100);
    pLander->SetAcceleration(pEnv->GetGlobalAcceleration());

}

void Game::HandleMouseDrag(SDL_Event e)
{

}

bool Game::IsRunning()
{
    return isRunning == SDL_TRUE;
}

void Game::HandleEvents()
{
    while (SDL_PollEvent(&event)) 
    {
        switch (event.type)
        {
            case (SDL_QUIT):
                isRunning = SDL_FALSE;
                break;
            // Handle key presses here!
            case (SDL_KEYDOWN):
                if (event.key.keysym.sym == SDLK_ESCAPE) 
                    isRunning = SDL_FALSE;
                else
                    KEYS[event.key.keysym.sym] = true;
                break;
            case (SDL_KEYUP):
                KEYS[event.key.keysym.sym] = false;
                break;
            default:
                break;
        }
        
        // Handle mouse events here :)
        HandleMouseDrag(event);
    }
}

void Game::Update() 
{
    // update physics every frame (i.e. gravity)
    pLander->Update(KEYS, pEnv);
    // std::cout << "Fuel: " << pLander->GetFuel() << std::endl;
    
}

void Game::Render()
{
    // Clear the background
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);
    SDL_RenderClear(pRenderer);

    // Render background image
    SDL_RenderCopy(pRenderer, pImage, nullptr, nullptr);

    // Render the Lander
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 1);
    // SDL_RenderFillRect(pRenderer, pLander->GetSDLRect());
    SDL_RenderCopyEx(pRenderer,                   // renderers
                     pLanderTexture,              // source texture
                     nullptr,                     // src rect
                     pLander->GetLanderSDLRect(), // dst rect
                     pLander->GetAngleDeg()-90,   // angle (subtract bc 0deg is straight up in SDL)
                     nullptr,                     // center ref point
                     SDL_FLIP_NONE);              // flip ?

    // Display thrust
    if (KEYS[SDLK_UP])
    {
        SDL_RenderCopyEx(pRenderer,                   // renderers
                         pThrustTexture,              // source texture
                         nullptr,                     // src rect
                         pLander->GetThrustSDLRect(), // dst rect
                         pLander->GetAngleDeg()-90,   // angle (subtract bc 0deg is straight up in SDL)
                         nullptr,                     // center ref point
                         SDL_FLIP_NONE);              // flip ?
        
        SDL_RenderDrawLine(pRenderer, pLander->GetLanderX(), pLander->GetLanderY(), pLander->GetThrustX(), pLander->GetThrustY());
    }
    // TODO: look into font atlases for optimal rendering of text
    // Render Text
    SDL_RenderCopy(pRenderer, pHeaderText, nullptr, &headerTextRect);

    // Add everything to renderer
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

    SDL_DestroyTexture(pLanderTexture);
    SDL_DestroyTexture(pHeaderText);
    SDL_DestroyTexture(pImage);
    TTF_CloseFont(pFont);
    TTF_Quit();
    SDL_DestroyWindow(pWindow);
    SDL_Quit();

}

void Game::Run()
{
    Init();
    while (IsRunning())
    {
        currTick = SDL_GetTicks();
        deltaTime = currTick - prevTick;
        if (deltaTime > 1000/60.0)
        {
            prevTick = currTick;
            
            HandleEvents();
            // update state of internal objects
            Update();
            // display to the screen
            Render();
        }
    }
    CleanUp();
}