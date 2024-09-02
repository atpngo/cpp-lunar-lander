#include "Game.h"
#include "NetworkUtility.h"

int main()
{  
  Game *pGame = new Game("LunarLander", 640, 800);
  
  pGame->Run();

  delete pGame;
}