//
// Created by tomek on 2/26/25.
//

#include "Minimax.h"


int Minimax::AlphaBeta(State state, int depth, int alpha, int beta)
{
    if (state.isFinished || depth == 0)
        return state.heuristic();
    std::vector<State> succesors = state.getSuccesors();
    if (state.player == 1)
    {
        for (auto succesor : succesors)
        {
            alpha = std::max(alpha, AlphaBeta(succesor, depth-1, alpha, beta));
            if (alpha >= beta)
                return beta;
        }
        return alpha;
    }
    else
    {
        for (auto succesor : succesors)
        {
            beta = std::min(beta, AlphaBeta(succesor, depth-1, alpha, beta));
            if (alpha <= beta)
                return alpha;
        }
        return beta;
    }
}

