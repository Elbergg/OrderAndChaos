//
// Created by tomps on 17/02/2025.
//
#pragma once
#include "State.h"




class GameApi {
public:
    State state;
    GameApi() {
        state = State();
    }
    void makeMove(int y, int x, int player);
};


