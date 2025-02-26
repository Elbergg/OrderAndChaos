//
// Created by tomek on 2/26/25.
//

#include "Minimax.h"


Cords Minimax::AlphaBeta(State state, int depth, int alpha, int beta)
{
    if (state.isFinished || depth == 0)
        return state.heuristic();
    return (Cords){0,0};
}

