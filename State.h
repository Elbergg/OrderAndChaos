//
// Created by tomps on 17/02/2025.
//
#pragma once
#include <cstring>




class State {
public:
    char board[6][6]{};
    char player;
    bool isFinished;
    State makeMove(const int y, const int x, char player);
    State() {
        std::memset(board, 0, sizeof(board));
        player = 1;
        isFinished = false;
    }
    State(char brd[6][6], char player, int x, int y) {
        std::memcpy(board, brd, sizeof(board));
        board[x][y] = player;
        this->player = (player == 1) ? 2 : 1;
        isFinished = checkIfFinished(board);
    }
    char checkIfFinished(char board[6][6]);
    char checkColumn(int x);
    char checkRow(int y);
};




