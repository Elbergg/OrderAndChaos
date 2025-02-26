//
// Created by tomps on 17/02/2025.
//

#include "State.h"

#include <cstdlib>


State State::makeMove(int y,int x, int player) {
    State newState = State(board, player, y, x);
    return newState;
}

State State::randomMove()
{
    int y = rand()%6;
    int x = rand()%6;
    while (board[y][x]!=0)
    {
        y = rand()%6;
        x = rand()%6;
    }
    return makeMove(y,x,2);
}

State State::expertMove()
{
    Minimax minimax;
    Cords result = minimax.AlphaBeta();
    return makeMove(result.y, result.x, 2);
}


EndInfo State::checkIfFinished() {
    EndInfo check;
    for (int x = 0; x < 6; x++) {
            check = checkRow(x);
        if (check.over)
            return check;
        check = checkColumn(x);
        if (check.over)
            return check;
    }
    check = this->checkAcrossLeft(0,6,0);
    if (check.over)
        return check;
    check = this->checkAcrossLeft(0,5,1);
    if (check.over)
        return check;
    check = this->checkAcrossLeft(1,6,0);
    if (check.over)
        return check;
    check = this->checkAcrossRight(4,0,0);
    if (check.over)
        return check;
    check = this->checkAcrossRight(5,0,0);
    if (check.over)
        return check;
    check = this->checkAcrossRight(5,0,1);
    if (check.over)
        return check;
    check = this->checkChaos();
    if (check.over)
        return check;
    return EndInfo{false,0,0,0,0,0};
}

EndInfo State::checkChaos() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (board[i][j]==0)
                return EndInfo{false,0,0,0,0,0};
        }
    }
    return EndInfo{true,0,0,0,0, 2};
}


EndInfo State::checkColumn(int x) {
    int count = 0;
    for (int i = 0; i < 6; i++) {
        if (board[i][x] == 1) {
            count++;
        }
        else {
            count = 0;
        }
        if (count == 5)
            return EndInfo{true, x, x, i-4, i, 1};
    }
    return EndInfo{false, 0, 0, 0, 0, 0};
}


 EndInfo State::checkRow(int y) {
    int count = 0;
    for (int i = 0; i < 6; i++) {
        if (board[y][i] == 1) {
            count++;
        }
        else {
            count = 0;
        }
        if (count == 5)
            return EndInfo{true, i-4, i, y, y, 1};
    }
    return EndInfo{false, 0, 0, 0, 0, 0};
}

EndInfo State::checkAcrossLeft(int y_beg, int y_end, int x)
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
            return EndInfo{true, j,j-4,i,i-4,1};
        j++;
    }
    return EndInfo{false,0,0,0,0,0};
}

EndInfo State::checkAcrossRight(int y_beg, int y_end, int x)
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
            return EndInfo{true, j-4,j,i+4,i,1};
        j++;
    }
    return EndInfo{false,0,0,0,0,0};
}

int State::heuristic()
{

}
