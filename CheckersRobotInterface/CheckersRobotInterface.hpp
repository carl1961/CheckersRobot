/**
 * @file CheckersRobotInterface.hpp
 *
 * @author Thomas Kikkert
 */
#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <queue>
#include <wiringSerial.h>
#include "../BoardPosition/BoardPosition.hpp"
#include "../MoveQueue/MoveQueue.hpp"
#include "../CheckerMove/CheckerMove.hpp"
#include "../GRBLTranslator/GRBLTranslator.hpp" 

namespace ArduinoAPI
{
    /**
     * Implementation of a ChessRobotCommunicator
     */
    class CheckersRobotInterface
    {
    private:
        bool connected = false;
        bool running = false;
        int fd = 0;
        ArduinoAPI::MoveQueue moveQueue;
        std::thread *processingThread = NULL;
        std::queue<std::string> GCodeQueue = {};

        static void scheduler(bool *isRunning, bool *isConnected, std::queue<std::string> *GCodeQueue, int *fd, ArduinoAPI::MoveQueue *moveQueue); //

    public:
        /**
         * Default destructor for closing the connection with arduino when program ends
         */
        ~CheckersRobotInterface();

        CheckersRobotInterface();


        /**
         * Connect to the arduino
         */
        bool connect();

        /**
         * Move a Chess Piece
         *
         * @param startPosition contains the start position (row and column) on the board
         * @param endPosition contains the end position (row and column) on the board
         * @param endPositionContainsChessPiece true if there is a chess piece at the end position
         */
        bool move(BoardPosition &startPosition,  BoardPosition &endPosition, bool endPositionContainsChessPiece);


        /**
         * Close the connection to the arduino
         */
        bool disconnect();
    };
}