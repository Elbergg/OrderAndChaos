//
// Created by tomps on 17/02/2025.
//
#pragma once
#include <algorithm>

#include "State.h"
#define PVP 1
#define RANDOM 2
#define EXPERT 3
#define X_mark 1
#define O_mark 2



class GameApi {
public:
    explicit GameApi(Bot& enemy): bot(enemy)
    {
        state = State();
    }
    GameApi& operator=(GameApi&& other) noexcept {
        this->state = other.state;
        if (this != &other) {
            this->bot = other.bot;
        }
        return *this;
    }
    Bot& bot;
    State state;
    void makeMove(int y, int x, int val);
    void makeEnemyMove(bool order);
    void randomMove();
    void expertMove(bool order);
    int mode{};
    EndInfo isEnd();
};


