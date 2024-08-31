#include "Game.h"
#include <iostream>

int main()
{

  Game *pGame = new Game("Skibidi Toilet Rizz", 640, 480);
  pGame->Init();
  while (pGame->IsRunning())
  {
    pGame->HandleEvents();
    // update state of internal objects
    pGame->Update();
    // display to the screen
    pGame->Render();
  }
  pGame->CleanUp();

  delete pGame;

}