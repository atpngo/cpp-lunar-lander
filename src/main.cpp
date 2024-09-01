#include "Game.h"
#include <iostream>

#include "constants.h"
int main()
{  
  Game *pGame = new Game("LunarLander", 640, 800);
  
  pGame->Run();

  delete pGame;
}