//
// Created by tomps on 17/02/2025.
//
#pragma once
#include "State.h"




class Game {
public:
    State state;
    Game() {
        state = State();
    }
    void makeMove(int y, int x, char player);
};


