#include "CheckerMove.hpp"

using namespace ArduinoAPI;

CheckerMove::CheckerMove(BoardPosition &bPos, BoardPosition &ePos, bool take)
{
    this->beginRow = bPos.getRow();
    this->beginColumn = bPos.getColumn();
    this->endRow = ePos.getRow();
    this->endColumn = ePos.getColumn();
    this->take = take;
}

CheckerMove::CheckerMove(const std::string bPos, const std::string ePos, bool take)
{
    BoardPosition beginPos(bPos);
    BoardPosition endPos(ePos);

    this->beginRow = beginPos.getRow();
    this->beginColumn = beginPos.getColumn();
    this->endRow = endPos.getRow();
    this->endColumn = endPos.getColumn();
    this->take = take;
}

CheckerMove::CheckerMove()
{
    this->beginRow = 1;
    this->beginColumn = 'A';
    this->endRow = 1;
    this->endColumn = 'A';
    this->take = 0;
}

const BoardPosition CheckerMove::getBpos() const
{
    BoardPosition bPos(beginColumn, beginRow);
    
    return bPos;
}

const BoardPosition CheckerMove::getEpos() const
{
    BoardPosition ePos(endColumn, endRow);

    return ePos;
}

const bool CheckerMove::getTake() const
{
    return take;
}
