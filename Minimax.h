//
// Created by tomek on 2/26/25.
//

#ifndef MINIMAX_H
#define MINIMAX_H


struct Cords
{
    int y;
    int x;
};

class Minimax {
public:
    int depth();
    Cords AlphaBeta();
};



#endif //MINIMAX_H
