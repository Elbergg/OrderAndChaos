//
// Created by tomek on 3/1/25.
//
#pragma once
#include "State.h"
#ifndef BOT_H
#define BOT_H

struct Cords;
class State;


class Bot
{
public:
    virtual ~Bot() = default;
    virtual Cords move(State& state) = 0;
};

#endif //BOT_H
