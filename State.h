//
// Created by tomps on 17/02/2025.
//
#pragma once
#include <cstring>
#include <vector>
#define END 1
#define HEURISTIC 2


struct EndInfo {
    bool over;
    int start_x;
    int end_x;
    int start_y;
    int end_y;
    int who;
};
struct Cords
{
    int y;
    int x;
    int val;
};

class State {
public:
    char board[6][6]{};
    int player;
    bool isFinished;
    State makeMove(int y,  int x, int val);
    State randomMove();
    State expertMove();
    int heuristic();
    std::vector<State> getSuccesors();
    std::vector<Cords> getSuccCords();
    State() {
        std::memset(board, 0, sizeof(board));
        player = 1;
        isFinished = false;
    }
    State(char brd[6][6], int val, int x, int y, int plr) {
        std::memcpy(board, brd, sizeof(board));
        board[x][y] = val;
        this->player = (plr == 1) ? 2 : 1;
        isFinished = checkIfFinished().over;
    }
    EndInfo checkIfFinished();
    EndInfo checkColumn(int x, int mode=END);
    EndInfo checkRow(int y, int mode=END);
    EndInfo checkAcrossTopBottom(int y_beg, int y_end, int x, int mode=END);
    EndInfo checkAcrossBottomTop(int y_beg, int y_end, int x, int mode=END);
    EndInfo checkChaos();
};




