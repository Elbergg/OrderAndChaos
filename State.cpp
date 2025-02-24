//
// Created by tomps on 17/02/2025.
//

#include "State.h"

State State::makeMove(int y,int x, int player) {
    State newState = State(board, player, y, x);
    return newState;
}

char State::checkIfFinished() {
    for (int x = 0; x < 6; x++) {
        if ( this->checkColumn(x) || this->checkRow(x))
            return 1;
    }
    if (
    this->checkAcrossLeft(0, 6, 0) ||
    this->checkAcrossLeft(0, 5, 1) ||
    this->checkAcrossLeft(1, 6, 0) ||
    this->checkAcrossRight(0, 6, 5) ||
    this->checkAcrossRight(1, 6, 5) ||
    this->checkAcrossRight(0, 5, 4))
        return 1;
    return 0;
}

char State::checkColumn(int x) {
    int count = 0;
    for (int i = 0; i < 6; i++) {
        if (board[i][x] == 1) {
            count++;
        }
        else {
            count = 0;
        }
        if (count == 5)
            return 1;
    }
    return 0;
}


char State::checkRow(int y) {
    int count = 0;
    for (int i = 0; i < 6; i++) {
        if (board[y][i] == 1) {
            count++;
        }
        else {
            count = 0;
        }
        if (count == 5)
            return 1;
    }
    return 0;
}

char State::checkAcrossLeft(int y_beg, int y_end, int x)
{
    int count = 0;
    int j = x;
    for (int i = y_beg; i < y_end; i++)
    {
        if (board[i][j] == 1) {
            count++;
        }
        else {
            count = 0;
        }
        if (count == 5)
            return 1;
        j++;
    }
    return 0;
}

char State::checkAcrossRight(int y_beg, int y_end, int x)
{
    int count = 0;
    int j = x;
    for (int i = y_beg; i > y_end; i--)
    {
        if (board[i][j] == 1) {
            count++;
        }
        else {
            count = 0;
        }
        if (count == 5)
            return 1;
        j++;
    }
    return 0;
}

