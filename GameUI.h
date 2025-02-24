//
// Created by tomps on 17/02/2025.
//
#include "GameApi.h"
#include "raylib.h"


class GameUI {
public:
    int windowWidth;
    int windowHeight;
    GameApi& Api;
    GameUI(int width, int height, GameApi& api) : Api(api) {
        windowWidth = width;
        windowHeight = height;
    }
    void RunGame();
    void drawGrids();
    void drawTiles(char board[6][6]);
    void drawX(int y, int x);
    void drawO(int y, int x);
    void checkForClicks();
    void drawEndLine(EndInfo check);
    EndInfo isEnd();
};


