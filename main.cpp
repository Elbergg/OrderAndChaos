//
// Created by tomps on 17/02/2025.
//
#include "GameApi.h"

#include "GameUI.h"


int main(void)
{
    GameApi gameApi = GameApi();
    GameUI gameUI = GameUI(500, 500, gameApi);
    gameUI.Run();
    return 0;
}
