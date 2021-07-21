#pragma once

#include <string>
#include <queue>
#include "../CheckerMove/CheckerMove.hpp"

namespace ArduinoAPI
{

    class MoveQueue
    {
        private:
        std::queue<CheckerMove> moveQueue = {};

        public:

        void clear();
        const bool empty() const;
        const int size() const;
        void push(const CheckerMove MoveCommand);
        const CheckerMove front() const;
        void pop();
    };

}