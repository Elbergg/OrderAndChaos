//
// Created by tomps on 17/02/2025.
//
#include "GameApi.h"
#include "raylib.h"
#define BACKGROUND (Color){22, 22, 22, 255}
#define GRID (Color){235,64,237, 255}
#define X (Color){32, 164, 243, 255}
#define O (Color) {252, 224, 248, 255}
#define MENU (Color) {201, 237, 220,10}
#define RANDOMCOLOR Color{static_cast<unsigned char>(rand()% 256),static_cast<unsigned char>(rand()%256),static_cast<unsigned char>(rand()%256),255}

class GameUI {
public:
    int windowWidth;
    int windowHeight;
    GameApi& Api;
    GameUI(int width, int height, GameApi& api) : Api(api) {
        windowWidth = width;
        windowHeight = height;
    }
    void Run();
    void RunGame(const int& mode, bool order);
    void showMenu(int mode, int who);
    void drawGrids() const;
    void drawTiles(char board[6][6]);
    void drawX(int y, int x) const;
    void drawO(int y, int x) const;
    void checkForClicks() const;
    void InitBoard();
    void PlayerAsOrder();
    void PlayerAsChaos();
    void drawEndLine(const EndInfo &check) const;
    void drawRectangles();
    void showTurnPopup() const;
    void StartProcedure() const;
    void ReloadMenu();
    void DisplayWhoWonInfo(const int& who);
    void HandleSideButton(bool& first);
    void ShowDifficulty(bool first);
    EndInfo isEnd() const;
};


