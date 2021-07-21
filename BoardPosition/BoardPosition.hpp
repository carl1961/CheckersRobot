#pragma once
/**
 * @file BoardPosition.hpp
 *
 * @author Thomas Kikkert
 */
#include <string>

namespace ArduinoAPI
{
    /**
     * Implementation of a board position for the CheckerRobot
     */
    class BoardPosition
    {
    private:
        int row = 5;
        char column = 'B';

        void checkRow(const int row);
        void checkColumn(const char column);

    public:
        /**
         *  default constuctor need for queue
         */
        BoardPosition();

        /**
         * Constructor using combined position
         * @param position  position on the checker board ("A4")
         */
        BoardPosition(std::string position);

        /**
         * Constructor using separate column and row
         * @param column    column on the checker board (A - H)
         * @param row       row on the checker board (1 - 8)
         */
        BoardPosition(const char column, const int row);

        void update(const int row, const int column);

        /**
         * fetch the row number
         */
        const int getRow() const;

        /**
         * fetch the column char
         */
        const char getColumn() const;
    };
}