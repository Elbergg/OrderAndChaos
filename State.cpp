//
// Created by tomps on 17/02/2025.
//

#include "State.h"

State State::makeMove(int y,int x, char player) {
    State newState = State(board, player, y, x);
    return newState;
}
char State::checkIfFinished(char brd[6][6]) {
    char result = 0;
    for (int x = 0; x < 6; x++) {
        result = this->checkColumn(x);
    }
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
}
