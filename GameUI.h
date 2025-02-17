//
// Created by tomps on 17/02/2025.
//
#include "GameApi.h"
#include "raylib.h"


class GameUI {
public:
    int windowWidth;
    int windowHeight;
    GameUI(int width, int height) {
        windowWidth = width;
        windowHeight = height;
    }
    void RunGame(GameApi* api);
    void drawGrids();
    void drawTiles(char board[6][6]);
    void drawX(int y, int x);
    void drawO(int y, int x);
};


