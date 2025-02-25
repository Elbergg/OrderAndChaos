//
// Created by tomps on 17/02/2025.
//
#pragma once
#include "State.h"
#define PVP 1
#define RANDOM 2
#define EXPERT 3



class GameApi {
public:
    State state;
    int mode;
    GameApi() {
        state = State();
    }
    void makeMove(int y, int x, int player);
    void makeEnemyMove();
    void randomMove();
    void expertMove();
    EndInfo isEnd();
};


