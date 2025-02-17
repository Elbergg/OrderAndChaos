//
// Created by tomps on 17/02/2025.
//

#include "Game.h"

void Game::makeMove(int x, int y, char player)
{
   state = state.makeMove(x,y,player);
}
