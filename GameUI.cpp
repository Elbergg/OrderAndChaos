//
// Created by tomps on 17/02/2025.
//

#include "GameUI.h"

#include "GameApi.h"
#include <iostream>
#define OFFSET 40

void GameUI::RunGame() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowWidth, windowHeight, "OrderAndChaos");
    ClearBackground((Color){10, 10, 10, 255});
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        windowWidth = GetScreenWidth();
        windowHeight = GetScreenHeight();
        this->drawGrids();
        checkForClicks();
        this->drawTiles(Api.state.board);
        EndDrawing();
    }
    CloseWindow();
}

void GameUI::checkForClicks() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        int x = GetMouseX()/(float)(windowWidth/6);
        int y = GetMouseY()/(float)(windowHeight/6);
        std::cout << x << " " << y << std::endl;
        if (x >= 0 && y >= 0 && x <=5 && y<=5) {
            Api.makeMove(y,x,Api.state.player);
        }

    }

}


void GameUI::drawGrids() {
    float thickness = windowWidth/100;
    for (int i = 1; i < 6; i++) {
        DrawLineEx((Vector2){static_cast<float>(windowWidth) / 6 * i, 0},
                   (Vector2){static_cast<float>(windowWidth / 6 * i), static_cast<float>(windowHeight)},
                   thickness,(Color){235,64,237, 255});
    }
    for (int i = 1; i < 6; i++) {
        DrawLineEx((Vector2){0, static_cast<float>(windowHeight) / 6 * i},
                   (Vector2){static_cast<float>(windowWidth), static_cast<float>(windowHeight / 6 * i),},
                   thickness,(Color){235,64,237, 255});
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
    float padding_x = windowWidth/OFFSET;
    float padding_y = windowHeight/OFFSET;
    DrawLineEx(
        (Vector2){(x * static_cast<float>(windowWidth) * 1 / 6 +padding_x), y * static_cast<float>(windowHeight) * 1/6 + padding_y},
        (Vector2){((x+1) * static_cast<float>(windowWidth) * 1 / 6 -padding_x), (y+1) * static_cast<float>(windowHeight) * 1/6 - padding_y},
        10, (Color){32, 164, 243, 255});
    DrawLineEx(
    (Vector2){(x * static_cast<float>(windowWidth) * 1 / 6 +padding_x), (y+1) * static_cast<float>(windowHeight) * 1/6 - padding_y},
    (Vector2){((x+1) * static_cast<float>(windowWidth) * 1 / 6 -padding_x), y * static_cast<float>(windowHeight) * 1/6 + padding_y},
    10, (Color){32, 164, 243, 255});
}

void GameUI::drawO(int y, int x) {
    float radius;
    if (windowHeight > windowWidth)
        radius = windowWidth / 15;
    else
        radius = windowHeight / 15;
    DrawRing((Vector2){
                 ((x + 0.5f) * static_cast<float>(windowWidth) * 1 / 6),
                 (y + 0.5f) * static_cast<float>(windowHeight) * 1 / 6
             }, radius * 0.9f, radius, 360.0f, 0.0f,0.0f, (Color) {252, 224, 248, 255}
    );
}
