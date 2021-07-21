#include "MoveQueue.hpp"

using namespace ArduinoAPI;

void MoveQueue::push(const CheckerMove MoveCommand)
{
    moveQueue.push(MoveCommand);
}

const int MoveQueue::size() const
{
    return moveQueue.size();
}

void MoveQueue::clear()
{
    while(!moveQueue.empty())
    {
        moveQueue.pop();
    }
}

const bool MoveQueue::empty() const
{
    return moveQueue.empty();
}

const CheckerMove MoveQueue::front() const
{
    return moveQueue.front();
}

void MoveQueue::pop()
{
    if (!moveQueue.empty())
    {
        moveQueue.pop();
    }
}