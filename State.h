//
// Created by tomps on 17/02/2025.
//
#pragma once
#include <cstring>




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
        isFinished = checkIfFinished();
    }
    char checkIfFinished();
    char checkColumn(int x);
    char checkRow(int y);
    char checkAcrossLeft(int y_beg, int y_end, int x);
    char checkAcrossRight(int y_beg, int y_end, int x);
};




