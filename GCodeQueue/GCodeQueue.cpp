#include "GCodeQueue.hpp"

using namespace ArduinoAPI;

void GCodeQueue::push(const std::string GCode)
{
    GCodeQueue.push(GCode);
}

const int GCodeQueue::size() const
{
    return GCodeQueue.size();
}

void GCodeQueue::clear()
{
    while(!GCodeQueue.empty())
    {
        GCodeQueue.pop();
    }
}

const bool GCodeQueue::empty() const
{
    return GCodeQueue.empty();
}

const std::string GCodeQueue::front() const
{
    return GCodeQueue.front();
}

void GCodeQueue::pop()
{
    if (!GCodeQueue.empty())
    {
        GCodeQueue.pop();
    }
}