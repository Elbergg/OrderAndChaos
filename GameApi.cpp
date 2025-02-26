//
// Created by tomps on 17/02/2025.
//

#include "GameApi.h"

#include <cstdlib>

#include "State.h"
#include "Minimax.h"

void GameApi::makeMove(int y, int x, int player)
{
   state = state.makeMove(y,x,player);
}

void GameApi::randomMove()
{
    int y = rand()%6;
    int x = rand()%6;
    while (state.board[y][x]!=0)
    {
       y = rand()%6;
       x = rand()%6;
    }
   makeMove(y,x,2);
}
void GameApi::expertMove()
{
   Minimax minimax;
   Cords result = minimax.AlphaBeta();
   makeMove()
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


