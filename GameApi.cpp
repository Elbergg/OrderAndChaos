//
// Created by tomps on 17/02/2025.
//

#include "GameApi.h"
#include "State.h"

void GameApi::makeMove(int y, int x, int player)
{
   state = state.makeMove(y,x,player);
}

void GameApi::randomMove()
{
   state = state.randomMove();
}
void GameApi::expertMove()
{
   state = state.expertMove();
}


void GameApi::makeEnemyMove()
{
   if (mode == RANDOM)
      randomMove();
   else if (mode == EXPERT){
      expertMove();
      }
}


EndInfo GameApi::isEnd()
{
   return state.checkIfFinished();
}


