//
// Created by tomps on 17/02/2025.
//

#include "GameApi.h"

void GameApi::makeMove(int y, int x, int player)
{
   state = state.makeMove(y,x,player);
}

bool GameApi::isEnd()
{
   return state.isFinished();
}

