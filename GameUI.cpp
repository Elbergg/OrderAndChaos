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





void GameUI::run()
{
    showMenu(FIRST, 0);
}


void GameUI::reloadMenu() const {
    this->Api = GameApi(this->Api.bot);
    GuiLoadStyleDefault();
    Font defaultFont = GetFontDefault();
    GuiSetFont(defaultFont);
}

void GameUI::displayWhoWonInfo(int const& who)
{
    if (who==1)
        GuiLabel(Rectangle{(float)GetScreenWidth()/6, (float)GetScreenHeight()/10,(float)GetScreenWidth()*2/3, (float)GetScreenHeight()/6}, "Order won!");
    else if (who==2)
        GuiLabel(Rectangle{(float)GetScreenWidth()/6, (float)GetScreenHeight()/10,(float)GetScreenWidth()*2/3, (float)GetScreenHeight()/6}, "Chaos won!");

}

void GameUI::handleSideButton(bool &first)
{
    int side;
    if (first) {
        side = GuiButton((Rectangle){(float)(GetScreenWidth()*5/7), (float)(GetScreenHeight()*3/10), (float)(GetScreenWidth()/7), (float)(GetScreenHeight()/12)}, "Order");
        if (side) {
            first = false;
        }
    }
    else{
        side = GuiButton((Rectangle){(float)(GetScreenWidth()*5/7), (float)(GetScreenHeight()*3/10), (float)(GetScreenWidth()/7), (float)(GetScreenHeight()/12)}, "Chaos");
        if (side)
            first = true;
    }
}



void GameUI::showMenu(const int mode, const int who)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(menuWidth,menuHeight, "OrderAndChaosMenu");
    SetTargetFPS(60);
    if (mode==NEXT)
    {
        reloadMenu();
    }
    int pvp = 0;
    int pve = 0;
    bool first = true;
    int bigger = 0;
    while (!WindowShouldClose())
    {
        bigger =  GetScreenWidth() > GetScreenHeight() ? GetScreenWidth() : GetScreenHeight();
        menuWidth = GetScreenWidth();
        menuHeight = GetScreenHeight();
        BeginDrawing();
        ClearBackground(MENU);
        GuiSetStyle(DEFAULT, TEXT_SIZE, bigger/24);
        if (mode==NEXT)
        {
            displayWhoWonInfo(who);
        }
        else
        {
            GuiLabel(Rectangle{(float)GetScreenWidth()/6, (float)GetScreenHeight()/10,(float)GetScreenWidth()*2/3, (float)GetScreenHeight()/6}, "Welcome to order and chaos");
        }
        GuiSetStyle(DEFAULT, TEXT_SIZE, bigger/60);
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
        GuiSetStyle(DEFAULT, TEXT_SIZE, bigger/42);
        GuiLabel((Rectangle){(float)(GetScreenWidth()*4/7), (float)(GetScreenHeight()*3/10), (float)(GetScreenWidth()/7), (float)(GetScreenHeight()/12)}, "Im playing as: ");
        GuiSetStyle(DEFAULT, TEXT_SIZE, bigger/60);
        handleSideButton(first);
        if (!pve && !pvp) {
            EndDrawing();
            continue;
        }
        if (pvp==1)
        {
            EndDrawing();
            CloseWindow();
            runGame(PVP, first);
        }
        if (pve)
        {
            showDifficulty(first);
        }
        EndDrawing();
    }
    CloseWindow();
}

void GameUI::initBoard()
{
    BeginDrawing();
    ClearBackground(BACKGROUND);
    windowWidth = GetScreenWidth();
    windowHeight = GetScreenHeight();
    drawGrids();
    drawTiles(Api.state.board);
    showTurnPopup();
    EndDrawing();
}

void GameUI::showDifficulty(const bool first)
{
    int i = -1;
    const int drop = GuiDropdownBox(Rectangle{
              (float) GetScreenWidth() * 4 / 7, (float) GetScreenHeight() * 2 / 5,
              (float) GetScreenWidth() * 2 / 7, (float) GetScreenHeight() / 7
          }, "Random;Expert", &i, true);
    if (drop)
    {
        if (i == 0) {
            EndDrawing();
            CloseWindow();
            runGame(RANDOM, first);
        }
        if (i == 1) {
            EndDrawing();
            CloseWindow();
            runGame(EXPERT, first);
        }
    }
}


inline void GameUI::playerAsOrder()
{
    checkForClicks();
    initBoard();
    if (Api.state.player == 2)
    {
        Api.makeEnemyMove(true);
    }
    initBoard();
}

inline void GameUI::playerAsChaos()
{
    if (Api.state.player == 1)
    {
        Api.makeEnemyMove(false);
        initBoard();
    }
    checkForClicks();
    initBoard();
}

void GameUI::StartProcedure() const
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowWidth, windowHeight, "OrderAndChaos");
    ClearBackground(BACKGROUND);
    SetTargetFPS(60);
}


void GameUI::runGame(const int& mode, const bool order)
{
    Api.mode = mode;
    StartProcedure();
    initBoard();
    while (!WindowShouldClose())
    {
        initBoard();
        if (mode == PVP)
            checkForClicks();
        else
        {
            if (order)
            {
                playerAsOrder();
            }
            else
            {
                playerAsChaos();
            }
        }
        if (Api.state.isFinished)
        {
            const EndInfo check = isEnd();
            initBoard();
            initBoard();
            if (check.who == 1) {
                drawEndLine(check);
            }
            else {
                drawRectangles();
            }
            showMenu(NEXT, check.who);
            return;
        }
    }
    CloseWindow();
}

void GameUI::drawRectangles() const {
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


EndInfo GameUI::isEnd() const
{
    return Api.isEnd();
}

void GameUI::drawEndLine(const EndInfo &check) const
{
    for (int i = 0; i< 30; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        BeginDrawing();
        const int tileWidth = windowWidth/6;
        const int tileHeight = windowHeight/6;
        const int paddingWidth = windowWidth/12;
        const int paddingHeight = windowHeight/12;
        DrawLineEx(Vector2{(float) check.start_x*tileWidth + paddingWidth, (float) check.start_y*tileHeight + paddingHeight},
                   Vector2{(float) check.end_x*tileWidth + paddingWidth, (float) check.end_y*tileHeight + paddingHeight}, windowWidth / 30, RANDOMCOLOR);
        EndDrawing();
    }
}

void GameUI::checkForClicks() const
{
    const int x = GetMouseX()/(float)(windowWidth/6);
    const int y = GetMouseY()/(float)(windowHeight/6);
    if (Api.state.board[y][x]!=0)
        return;
    if (x >= 0 && y >= 0 && x <=5 && y<=5) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            Api.makeMove(y,x,X_mark);
        }
        else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
        {
            Api.makeMove(y,x,O_mark);
        }
    }
}


void GameUI::showTurnPopup() const
{
    int twidth = windowWidth/3;
    int theight = windowHeight/24;
    const char* text;
    if (Api.state.player == 1)
        text = "Order's turn";
    else
        text = "Chaos's turn";
    GuiLoadStyleDefault();
    const Font defaultFont = GetFontDefault();
    GuiSetFont(defaultFont);
    GuiSetStyle(DEFAULT, TEXT_SIZE, (GetScreenWidth() > GetScreenHeight() ? GetScreenWidth() : GetScreenHeight())/50);
    GuiButton((Rectangle){(float)(windowWidth-twidth), 0.0f, (float)(twidth), (float)(theight)}, text);
}


void GameUI::drawGrids() const {
    const float thickness = (windowWidth > windowHeight ? windowWidth : windowHeight)/100;
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

void GameUI::drawTiles(char board[6][6]) const {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (char marker = board[i][j]; marker == 1) {
                this->drawX(i, j);
            }
            else if (marker == 2) {
                this->drawO(i, j);
            }
        }
    }
}
void GameUI::drawX(int y, int x) const
{
    const float padding_x = windowWidth/OFFSET;
    const float padding_y = windowHeight/OFFSET;
    DrawLineEx(
        (Vector2){(x * static_cast<float>(windowWidth) * 1 / 6 +padding_x), y * static_cast<float>(windowHeight) * 1/6 + padding_y},
        (Vector2){((x+1) * static_cast<float>(windowWidth) * 1 / 6 -padding_x), (y+1) * static_cast<float>(windowHeight) * 1/6 - padding_y},
        10, X);
    DrawLineEx(
    (Vector2){(x * static_cast<float>(windowWidth) * 1 / 6 +padding_x), (y+1) * static_cast<float>(windowHeight) * 1/6 - padding_y},
    (Vector2){((x+1) * static_cast<float>(windowWidth) * 1 / 6 -padding_x), y * static_cast<float>(windowHeight) * 1/6 + padding_y},
    10, X);
}

void GameUI::drawO(int y, int x) const
{
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
