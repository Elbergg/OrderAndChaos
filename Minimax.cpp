//
// Created by tomek on 2/26/25.
//

#include "Minimax.h"


int Minimax::AlphaBeta(State state, int depth, int alpha, int beta)
{
    if (state.isFinished || depth == 0)
        return state.heuristic();
    std::vector<State> succesors = state.getSuccesors();
    int  val = -100000;
    if (state.player == 1)
    {
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

