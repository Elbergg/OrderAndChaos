//
// Created by tomek on 3/1/25.
//
#pragma once
#ifndef BOT_H
#define BOT_H

struct Cords;
class State;


class Bot
{
public:
    virtual ~Bot() = default;
    virtual Cords move(State& state, bool order) = 0;
};

#endif //BOT_H
