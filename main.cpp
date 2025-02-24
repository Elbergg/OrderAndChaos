//
// Created by tomps on 17/02/2025.
//
#include "GameApi.h"

#include "GameUI.h"


int main(void)
{
    GameApi gameApi = GameApi();
    gameApi.makeMove(1,0,1);
    gameApi.makeMove(1,1,1);
    gameApi.makeMove(1,2,1);
    gameApi.makeMove(1,3,1);
    gameApi.makeMove(1,4,1);
    gameApi.makeMove(1,5,2);
    gameApi.makeMove(2,5,2);
    int result = 0;
    result = gameApi.state.checkIfFinished();
    GameUI gameUI = GameUI(500, 500, gameApi);
    gameUI.RunGame();

    return 0;
}
