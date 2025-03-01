//
// Created by tomek on 2/26/25.
//
#pragma once
#ifndef MINIMAX_H
#define MINIMAX_H
#include <vector>
#include "Bot.h"


class Minimax : public Bot{
public:
    std::vector<Cords>getSuccCords(State& state);
    std::vector<State>getSuccesors(State& state);
    Cords move(State& state);
    int AlphaBeta(State state, int depth, int alpha, int beta);
};



#endif //MINIMAX_H
