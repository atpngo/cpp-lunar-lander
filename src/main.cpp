#include "Game.h"
#include "constants.h"

int main()
{  
  Game *pGame = new Game("LunarLander", WINDOW_WIDTH, WINDOW_HEIGHT);
  
  pGame->Run();

  delete pGame;
}