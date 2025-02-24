//
// Created by tomps on 17/02/2025.
//
#pragma once
#include <cstring>


struct EndInfo {
    bool over;
    int start_x;
    int end_x;
    int start_y;
    int end_y;
    int who;
};

class State {
public:
    char board[6][6]{};
    int player;
    bool isFinished;
    State makeMove(int y,  int x, int player);
    State() {
        std::memset(board, 0, sizeof(board));
        player = 1;
        isFinished = false;
    }
    State(char brd[6][6], int player, int x, int y) {
        std::memcpy(board, brd, sizeof(board));
        board[x][y] = player;
        this->player = (player == 1) ? 2 : 1;
        isFinished = checkIfFinished().over;
    }
    EndInfo checkIfFinished();
    EndInfo checkColumn(int x);
    EndInfo checkRow(int y);
    EndInfo checkAcrossLeft(int y_beg, int y_end, int x);
    EndInfo checkAcrossRight(int y_beg, int y_end, int x);
    EndInfo checkChaos();
};




