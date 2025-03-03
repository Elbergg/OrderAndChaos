//
// Created by tomps on 17/02/2025.
//

#include "State.h"
#include "Minimax.h"
#include <cstdlib>
#include <random>


State State::makeMove(int y,int x, int val) {
    State newState = State(board, val, y, x, this->player);
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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1,2);
    return makeMove(y,x,distrib(gen));
}

State State::expertMove(Bot& bot, bool order)
{
    Cords cords = bot.move(*this, order);
    return makeMove(cords.y, cords.x, cords.val);
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
    check = this->checkAcrossTopBottom(0,5,0);
    if (check.over)
        return check;
    check = this->checkAcrossTopBottom(0,4,1);
    if (check.over)
        return check;
    check = this->checkAcrossTopBottom(1,5,0);
    if (check.over)
        return check;
    check = this->checkAcrossBottomTop(4,0,0);
    if (check.over)
        return check;
    check = this->checkAcrossBottomTop(5,0,0);
    if (check.over)
        return check;
    check = this->checkAcrossBottomTop(5,1,1);
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


EndInfo State::checkColumn(int x, int mode) {
    int count = 0;
    unsigned char curr = 0;
    int hcount;
    int xhcount = 0;
    int yhcount = 0;
    for (int i = 0; i < 6; i++) {
        if (board[i][x] == curr && curr != 0) {
            count++;
            if (curr == 1)
                xhcount++;
            else
                yhcount++;
        }
        else
        {
            count = 1;
            curr = board[i][x];
        }
        if (count == 5 && mode == END)
            return EndInfo{true, x, x, i-4, i, 1};
        if (count == 5 && mode == HEURISTIC)
            return EndInfo{false, 5000, 0, 0,0,0};
    }
    if (mode == HEURISTIC)
    {
        hcount = std::max(xhcount, yhcount);
        hcount = hcount *  hcount * hcount;
        return EndInfo{false, hcount, 0, 0, 0, 0};
    }
    return EndInfo{false, 0, 0, 0, 0, 0};
}


 EndInfo State::checkRow(int y, int mode) {
    int count = 0;
    int xhcount = 0;
    int yhcount = 0;
    unsigned char curr = 0;
    for (int i = 0; i < 6; i++) {
        if (board[y][i] == curr && curr != 0) {
            count++;
            if (curr == 1)
                xhcount++;
            else
                yhcount++;
        }
        else
        {
            count = 1;
            curr = board[y][i];
        }
        if (count == 5 && mode == END)
            return EndInfo{true, i-4, i, y, y, 1};
        if (count == 5 && mode == HEURISTIC)
            return EndInfo{false, 5000, 0, 0,0,0};
    }
    if (mode == HEURISTIC)
    {
        int hcount = std::max(xhcount, yhcount);
        hcount = hcount * hcount * hcount;
        return EndInfo{false, hcount, 0, 0, 0,0};
    }
    return EndInfo{false, 0, 0, 0, 0, 0};
}

EndInfo State::checkAcrossTopBottom(int y_beg, int y_end, int x, int mode)
{
    int count = 0;
    int xhcount = 0;
    int yhcount = 0;
    unsigned char curr = 0;
    int j = x;
    for (int i = y_beg; i <= y_end; i++)
    {
        if (board[i][j] == curr && curr != 0) {
            count++;
            if (curr == 1)
                xhcount++;
            else
                yhcount++;
        }
        else
        {
            count = 1;
            curr = board[i][j];
        }
        if (count == 5 && mode == END)
            return EndInfo{true, j,j-4,i,i-4,1};
        if (count == 5 && mode == HEURISTIC)
            return EndInfo{false, 5000, 0, 0,0,0};
        j++;
    }
    if (mode == HEURISTIC)
    {
        int hcount = std::max(xhcount, yhcount);
        hcount = hcount * hcount * hcount;
        return EndInfo{false, hcount, 0, 0, 0, 0};
    }
    return EndInfo{false,0,0,0,0,0};
}

EndInfo State::checkAcrossBottomTop(int y_beg, int y_end, int x, int mode)
{
    int count = 0;
    int xhcount = 0;
    int yhcount = 0;
    unsigned char curr = 0;
    int j = x;
    for (int i = y_beg; i >= y_end; i--)
    {
        if (board[i][j] == curr && curr != 0)
            {
            count++;
            if (curr == 1)
                xhcount++;
            else
                yhcount++;
        }
        else
        {
            count = 1;
            curr = board[i][j];
        }
        if (count == 5 && mode == END)
            return EndInfo{true, j-4,j,i+4,i,1};
        if (count == 5 && mode == HEURISTIC)
            return EndInfo{false, 5000, 0, 0,0,0};
        j++;
    }
    if (mode == HEURISTIC)
    {
        int hcount = std::max(xhcount, yhcount);
        hcount = hcount * hcount * hcount;
        return EndInfo{false, hcount, 0, 0, 0, 0};
    }
    return EndInfo{false,0,0,0,0,0};
}


int State::heuristic()
{
    int count = 0;
    for (int x = 0; x < 6; x++) {
        count += checkRow(x, HEURISTIC).start_x;
        count += checkColumn(x, HEURISTIC).start_x;
    }
    count += this->checkAcrossTopBottom(0,5,0, HEURISTIC).start_x;
    count += this->checkAcrossTopBottom(0,4,1, HEURISTIC).start_x;
    count += this->checkAcrossTopBottom(1,5,0, HEURISTIC).start_x;
    count += this->checkAcrossBottomTop(4,0,0, HEURISTIC).start_x;
    count += this->checkAcrossBottomTop(5,0,0, HEURISTIC).start_x;
    count += this->checkAcrossBottomTop(5,1,1, HEURISTIC).start_x;
    return count;
}
