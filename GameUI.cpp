//
// Created by tomps on 17/02/2025.
//
#define RAYGUI_IMPLEMENTATION

#include "GameUI.h"
#include "raygui.h"
#include "GameApi.h"
#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>
#include <unistd.h>
#define OFFSET 40
#define FIRST 1
#define NEXT 2



void GameUI::Run()
{
    showMenu(FIRST, 0);
}


void GameUI::showMenu(int mode, int who)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(600,400, "OrderAndChaosMenu");
    SetTargetFPS(60);
    if (mode==NEXT) {
        this->Api = GameApi(this->Api.bot);
        GuiLoadStyleDefault();
        Font defaultFont = GetFontDefault();
        GuiSetFont(defaultFont);
    }
    int pvp = 0;
    int pve = 0;
    int side1 = 0;
    int side2 = 0;
    bool first = true;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(MENU);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 25);
        if (mode==NEXT)
        {
            if (who==1)
                GuiLabel(Rectangle{(float)GetScreenWidth()/6, (float)GetScreenHeight()/10,(float)GetScreenWidth()*2/3, (float)GetScreenHeight()/6}, "Order won!");
            else if (who==2)
                GuiLabel(Rectangle{(float)GetScreenWidth()/6, (float)GetScreenHeight()/10,(float)GetScreenWidth()*2/3, (float)GetScreenHeight()/6}, "Chaos won!");
        }
        else
        {
            GuiLabel(Rectangle{(float)GetScreenWidth()/6, (float)GetScreenHeight()/10,(float)GetScreenWidth()*2/3, (float)GetScreenHeight()/6}, "Welcome to order and chaos");
        }
        GuiSetStyle(DEFAULT, TEXT_SIZE, 10);
        if (!pvp)
            pvp = GuiButton(Rectangle{
                          (float) GetScreenWidth() / 7, (float) GetScreenHeight() * 2 / 5, (float) GetScreenWidth() * 2 / 7,
                          (float) GetScreenHeight() / 5
                      }, "PVP");
        GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        if (!pve)
            pve = GuiButton(Rectangle{
                          (float) GetScreenWidth() * 4 / 7, (float) GetScreenHeight() * 2 / 5,
                          (float) GetScreenWidth() * 2 / 7, (float) GetScreenHeight() / 5
                      }, "PVE");
        GuiSetStyle(DEFAULT, TEXT_SIZE, 14);
        GuiLabel((Rectangle){(float)(GetScreenWidth()*4/7), (float)(GetScreenHeight()*3/10), (float)(GetScreenWidth()/7), (float)(GetScreenHeight()/12)}, "Im playing as: ");
        GuiSetStyle(DEFAULT, TEXT_SIZE, 10);
        // GuiComboBox((Rectangle){(float)(GetScreenWidth()*5/7), (float)(GetScreenHeight()*3/10), (float)(GetScreenWidth()/7), (float)(GetScreenHeight()/12)}, "Order;Chaos", &side);
        if (first) {
            side2 = GuiButton((Rectangle){(float)(GetScreenWidth()*5/7), (float)(GetScreenHeight()*3/10), (float)(GetScreenWidth()/7), (float)(GetScreenHeight()/12)}, "Order");
            if (side2) {
                first = false;
            }
        }
        else{
            side1 = GuiButton((Rectangle){(float)(GetScreenWidth()*5/7), (float)(GetScreenHeight()*3/10), (float)(GetScreenWidth()/7), (float)(GetScreenHeight()/12)}, "Chaos");
            if (side1)
                first = true;
        }

        if (!pve && !pvp) {
            EndDrawing();
            continue;
        }
        if (pvp==1)
        {
            EndDrawing();
            CloseWindow();
            RunGame(PVP);
        }
        if (pve)
        {
            int i = -1;
            int drop = GuiDropdownBox(Rectangle{
                      (float) GetScreenWidth() * 4 / 7, (float) GetScreenHeight() * 2 / 5,
                      (float) GetScreenWidth() * 2 / 7, (float) GetScreenHeight() / 7
                  }, "Random;Expert", &i, true);
            if (drop)
            {
                if (i == 0) {
                    EndDrawing();
                    CloseWindow();
                    RunGame(RANDOM);
                }
                if (i == 1) {
                    EndDrawing();
                    CloseWindow();
                    RunGame(EXPERT);
                }
            }
        }
        EndDrawing();
    }
    CloseWindow();
}



void GameUI::RunGame(int mode)
{
    Api.mode = mode;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowWidth, windowHeight, "OrderAndChaos");
    ClearBackground(BACKGROUND);
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BACKGROUND);
        windowWidth = GetScreenWidth();
        windowHeight = GetScreenHeight();
        drawGrids();
        checkForClicks();
        if (mode != PVP && Api.state.player == 2)
            Api.makeEnemyMove();
        drawTiles(Api.state.board);
        showTurnPopup();
        if (Api.state.isFinished)
        {
            EndInfo check = isEnd();
            EndDrawing();
            BeginDrawing();
            drawTiles(Api.state.board);
            showTurnPopup();
            EndDrawing();
            if (check.who == 1) {
                drawEndLine(check);
            }
            else {
                drawRectangles();
            }
            showMenu(NEXT, check.who);
            return;
        }
        EndDrawing();
    }
    CloseWindow();
}

void GameUI::drawRectangles()
{
    std::vector<int> x_list;
    std::vector<int> y_list;
    std::vector<int> width_list;
    std::vector<int> height_list;
    std::vector<Color> colors;
    for (int i = 0; i < 30; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        BeginDrawing();
        int x = rand()%windowWidth;
        int y = rand()%windowHeight;
        x_list.push_back(x);
        y_list.push_back(y);
        width_list.push_back(rand()%(windowWidth-x-1));
        height_list.push_back(rand()%(windowHeight-y-1));
        colors.push_back(RANDOMCOLOR);
        for (int j = 0; j < width_list.size(); j++)
        {
            DrawRectangle(x_list[j],y_list[j],width_list[j], height_list[j], colors[j]);
        }
        EndDrawing();
    }
}


EndInfo GameUI::isEnd()
{
    return Api.isEnd();
}

void GameUI::drawEndLine(EndInfo check)
{
    for (int i = 0; i< 30; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        BeginDrawing();
        int tileWidth = windowWidth/6;
        int tileHeight = windowHeight/6;
        int paddingWidth = windowWidth/12;
        int paddingHeight = windowHeight/12;
        DrawLineEx(Vector2{(float) check.start_x*tileWidth + paddingWidth, (float) check.start_y*tileHeight + paddingHeight},
                   Vector2{(float) check.end_x*tileWidth + paddingWidth, (float) check.end_y*tileHeight + paddingHeight}, windowWidth / 30, RANDOMCOLOR);
        EndDrawing();
    }
}

void GameUI::checkForClicks()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))){
        int x = GetMouseX()/(float)(windowWidth/6);
        int y = GetMouseY()/(float)(windowHeight/6);
        if (Api.state.board[y][x]!=0)
            return;
        if (x >= 0 && y >= 0 && x <=5 && y<=5) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Api.makeMove(y,x,X_mark);
            }
            else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
            {
                Api.makeMove(y,x,O_mark);
            }
        }
    }
}


void GameUI::showTurnPopup()
{
    int twidth = windowWidth/3;
    int theight = windowHeight/24;
    const char* text = "grrr";
    if (Api.state.player == 1)
        text = "Order's turn";
    else
        text = "Chaos's turn";
    GuiLoadStyleDefault();
    Font defaultFont = GetFontDefault();
    GuiSetFont(defaultFont);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 10);
    GuiButton((Rectangle){(float)(windowWidth-twidth), 0.0f, (float)(twidth), (float)(theight)}, text);
}


void GameUI::drawGrids() {
    float thickness = windowWidth/100;
    for (int i = 1; i < 6; i++) {
        DrawLineEx((Vector2){static_cast<float>(windowWidth) / 6 * i, 0},
                   (Vector2){static_cast<float>(windowWidth / 6 * i), static_cast<float>(windowHeight)},
                   thickness,GRID);
    }
    for (int i = 1; i < 6; i++) {
        DrawLineEx((Vector2){0, static_cast<float>(windowHeight) / 6 * i},
                   (Vector2){static_cast<float>(windowWidth), static_cast<float>(windowHeight / 6 * i),},
                   thickness,GRID);
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
        10, X);
    DrawLineEx(
    (Vector2){(x * static_cast<float>(windowWidth) * 1 / 6 +padding_x), (y+1) * static_cast<float>(windowHeight) * 1/6 - padding_y},
    (Vector2){((x+1) * static_cast<float>(windowWidth) * 1 / 6 -padding_x), y * static_cast<float>(windowHeight) * 1/6 + padding_y},
    10, X);
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
             }, radius * 0.9f, radius, 360.0f, 0.0f,0.0f, O
    );
}
