//
// Created by tomps on 17/02/2025.
//

#include "GameApi.h"
#include "State.h"
void GameApi::makeMove(int y, int x, int player)
{
   state = state.makeMove(y,x,player);
}

EndInfo GameApi::isEnd()
{
   return state.checkIfFinished();
}

