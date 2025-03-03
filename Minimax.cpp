//
// Created by tomek on 2/26/25.
//

#include "Minimax.h"

#include <algorithm>
#include <cstdlib>
#include <random>

#include "State.h"

std::vector<Cords> Minimax::getSuccCords(State& state)
{
    std::vector<Cords> succesors;
    for (int y = 0; y < 6; y++)
    {
        for (int x = 0; x < 6; x++)
        {
            if (state.board[y][x] == 0)
            {
                succesors.push_back(Cords{y,x, 1});
                succesors.push_back(Cords{y,x, 2});
            }
        }
    }
    return succesors;
}

std::vector<State> Minimax::getSuccesors(State& state)
{
    std::vector<State> succesors;
    for (int y = 0; y < 6; y++)
    {
        for (int x = 0; x < 6; x++)
        {
            if (state.board[y][x] == 0)
            {
                succesors.push_back(state.makeMove(y,x,1));
                succesors.push_back(state.makeMove(y,x,2));
            }
        }
    }
    return succesors;
}

Cords Minimax::move(State& state, bool order)
{
    std::vector<Cords> cords= getSuccCords(state);
    std::vector<State> succs = getSuccesors(state);
    std::vector<int> results;
    std::vector<int> equals;
    for (auto succ: succs)
    {
        results.push_back(this->AlphaBeta(succ, 3, -10000000, 10000000));
    }
    if (order)
    {
        int smallest = 100000000;
        for (int i = 0; i < results.size(); i++)
        {
            if (results[i] < smallest)
            {
                smallest = results[i];
                equals = {i};
            }
            else if (results[i] == smallest)
                equals.push_back(i);
        }
    }
    else
    {
        int biggest = -100000000;
        for (int i = 0; i < results.size(); i++)
        {
            if (results[i] > biggest)
            {
                biggest = results[i];
                equals = {i};
            }
            else if (results[i] == biggest)
                equals.push_back(i);
        }
    }
    std::shuffle(equals.begin(), equals.end(), std::mt19937(std::random_device()()));
    return cords[equals[0]];
}

int Minimax::AlphaBeta(State state, int depth, int alpha, int beta)
{
    if (state.isFinished || depth == 0)
        return state.heuristic()*(depth+1);
    std::vector<State> succesors = getSuccesors(state);
    int  val;
    if (state.player == 1)
    {
        val = -100000;
        for (auto succesor : succesors)
        {
            val = std::max(val, AlphaBeta(succesor, depth-1, alpha, beta));
            if (val >= beta)
                break;
            alpha = std::max(alpha, val);
        }
        return val;
    }
    else
    {
        val = 100000;
        for (auto succesor : succesors)
        {
            val = std::min(val, AlphaBeta(succesor, depth-1, alpha, beta));
            if (val < alpha)
                break;
            beta = std::min(beta, val);
        }
        return val;
    }
}

