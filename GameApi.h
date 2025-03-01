//
// Created by tomps on 17/02/2025.
//
#pragma once
#include "State.h"
#define PVP 1
#define RANDOM 2
#define EXPERT 3
#define X_mark 1
#define O_mark 2



class GameApi {
public:
    State state;
    int mode;
    GameApi() {
        state = State();
    }
    void makeMove(int y, int x, int val);
    void makeEnemyMove();
    void randomMove();
    void expertMove();
    EndInfo isEnd();
};


