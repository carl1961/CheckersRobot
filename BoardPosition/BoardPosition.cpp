#include "BoardPosition.hpp"
#include <iostream>

using ArduinoAPI::BoardPosition;

BoardPosition::BoardPosition()
{
}

BoardPosition::BoardPosition( std::string position)
{
    // the data should look like this: A2 or a2
    if (position.length() < 2)
    {
        throw "Invalid position length";
    }
    else
    {
        checkColumn(position[0]);
        checkRow(position[1] - '0');
        this->column = position[0];
        this->row = position[1] - '0';
    }
}

BoardPosition::BoardPosition(const char column, const int row)
{
    checkColumn(column);
    checkRow(row);
    this->column = column;
    this->row = row;
}

void BoardPosition::update(const int row, const int column)
{
    checkColumn(row);
    checkColumn(column);

    this->row = row;
    this->column = column;
}

void BoardPosition::checkRow(const int row)
{
    if (row < 1 || row > 8)
    {
        throw "Invalid row number";
    }
}

void BoardPosition::checkColumn(const char column)
{
    //std::cout << column << " as inter value: " << (int)column << "\n";
    if (column < 65 || column > 72)
    {
        throw "Invalid column character";
    }
}

const int BoardPosition::getRow() const
{
    return row;
}

const char BoardPosition::getColumn() const
{
    return column;
}
