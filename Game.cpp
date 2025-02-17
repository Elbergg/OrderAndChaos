//
// Created by tomps on 17/02/2025.
//

#include "Game.h"

void Game::makeMove(int y, int x, char player)
{
   state = state.makeMove(y,x,player);
}
