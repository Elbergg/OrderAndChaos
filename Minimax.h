//
// Created by tomek on 2/26/25.
//

#ifndef MINIMAX_H
#define MINIMAX_H
#include "State.h"

struct Cords
{
    int y;
    int x;
};

class Minimax {
public:
    int depth();

    int AlphaBeta(State state, int depth, int alpha, int beta);
};



#endif //MINIMAX_H
