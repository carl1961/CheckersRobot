#pragma once

#include <string>
#include <queue>

namespace ArduinoAPI
{

    class GCodeQueue
    {
        private:
        std::queue<std::string> GCodeQueue = {};

        public:
        void clear();
        const bool empty() const;
        const int size() const;
        void push(const std::string GCode);
        const std::string front() const;
        void pop();
    };

}