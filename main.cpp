//
// Created by tomps on 17/02/2025.
//
#include "GameApi.h"

#include "GameUI.h"
#include "Minimax.h"


/* to do:
 * - add music
 * - private methods
 */

int main(void)
{
    Minimax minimax = {};
    GameApi gameApi = GameApi(minimax);
    GameUI gameUI = GameUI(500, 500, 600, 400, gameApi);
    gameUI.run();
    return 0;
}
