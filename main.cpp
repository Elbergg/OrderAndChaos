//
// Created by tomps on 17/02/2025.
//
#include "GameApi.h"

#include "GameUI.h"
#include "Minimax.h"


int main(void)
{
    Minimax minimax = {};
    GameApi gameApi = GameApi(minimax);
    GameUI gameUI = GameUI(500, 500, gameApi);
    gameUI.Run();
    return 0;
}
