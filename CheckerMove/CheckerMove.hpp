#pragma once

#include "../BoardPosition/BoardPosition.hpp"

namespace ArduinoAPI
{

    class CheckerMove
    {
    private:
        int beginRow;
        char beginColumn;
        int endRow;
        char endColumn;
        bool take;

    public:
        CheckerMove(BoardPosition &bPos, BoardPosition &ePos, bool take);
        CheckerMove(const std::string bPos, const std::string ePos, bool take);
        CheckerMove();

        const BoardPosition getBpos() const;
        const BoardPosition getEpos() const;
        const bool getTake() const;
    };
}