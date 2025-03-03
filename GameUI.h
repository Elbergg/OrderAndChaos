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
    GameUI(int width, int height, int mWidth, int mHeight, GameApi& api) : Api(api) {
        windowWidth = width;
        windowHeight = height;
        menuWidth = mWidth;
        menuHeight = mHeight;
    }
    void run();
private:
    int windowWidth;
    int windowHeight;
    int menuWidth;
    int menuHeight;
    GameApi& Api;
    void runGame(const int& mode, bool order);
    void showMenu(int mode, int who);
    void drawGrids() const;
    void drawTiles(char board[6][6]) const;
    void drawX(int y, int x) const;
    void drawO(int y, int x) const;
    void checkForClicks() const;
    void initBoard();
    void playerAsOrder();
    void playerAsChaos();
    void drawEndLine(const EndInfo &check) const;
    void drawRectangles() const;
    void showTurnPopup() const;
    void StartProcedure() const;
    void reloadMenu() const;
    static void displayWhoWonInfo(const int& who);
    static void handleSideButton(bool& first);
    void showDifficulty(bool first);
    EndInfo isEnd() const;
};


