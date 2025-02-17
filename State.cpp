//
// Created by tomps on 17/02/2025.
//

#include "State.h"

State State::makeMove(int x,int y, char player) {
    State newState = State(board, player, x, y);
    return newState;
}
char State::checkIfFinished(char brd[6][6]) {
    return 0;
}
