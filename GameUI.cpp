//
// Created by tomps on 17/02/2025.
//

#include "GameUI.h"

#include "GameApi.h"


void GameUI::RunGame(GameApi* api) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowWidth, windowHeight, "OrderAndChaos");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        windowWidth = GetScreenWidth();
        windowHeight = GetScreenHeight();
        ClearBackground(RAYWHITE);
        this->drawGrids();
        this->drawTiles(api->state.board);
        EndDrawing();
    }
    CloseWindow();
}

void GameUI::drawGrids() {
    for (int i = 1; i < 6; i++) {
        DrawLineEx((Vector2){static_cast<float>(windowWidth) / 6 * i, 0},
                   (Vector2){static_cast<float>(windowWidth / 6 * i), static_cast<float>(windowHeight)},
                   static_cast<float>(windowWidth / 50),DARKPURPLE);
    }
    for (int i = 1; i < 6; i++) {
        DrawLineEx((Vector2){0, static_cast<float>(windowHeight) / 6 * i},
                   (Vector2){static_cast<float>(windowWidth), static_cast<float>(windowHeight / 6 * i),},
                   static_cast<float>(windowWidth / 50),DARKPURPLE);
    }
}

void GameUI::drawTiles(char board[6][6]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            char marker = board[i][j];
            if (marker == 1) {
                this->drawX(i, j);
            }
            else if (marker == 2) {
                this->drawO(i, j);
            }
        }
    }
}

void GameUI::drawX(int y, int x) {
    DrawLineEx(
        (Vector2){(x * static_cast<float>(windowWidth) * 11 / 73), y * static_cast<float>(windowWidth) * 11 / 73},
        (Vector2){((x+1) * static_cast<float>(windowWidth) * 11 / 73), (y+1) * static_cast<float>(windowWidth) * 11 / 73},
        10, DARKBLUE);
    DrawLineEx(
    (Vector2){(x * static_cast<float>(windowWidth) * 11 / 73), (y+1) * static_cast<float>(windowWidth) * 11 / 73},
    (Vector2){((x+1) * static_cast<float>(windowWidth) * 11 / 73), (y) * static_cast<float>(windowWidth) * 11 / 73},
    10, DARKBLUE);
}

void GameUI::drawO(int y, int x) {}
