#pragma once

#include "iostream"
#include "../CheckerMove/CheckerMove.hpp"
#include "../general/general.hpp"
#include <queue>
#include <string>

namespace ArduinoAPI
{
    typedef struct _invertedAxises
    {
        bool xAxis;
        bool yAxis;
    } invertedAxises_t;

    typedef struct _maxSpeed
    {
        int xSpeed;
        int ySpeed;
    } maxSpeed_t;

    typedef struct _maxAccel
    {
        int xSpeed;
        int ySpeed;
    } maxAccel_t;

    typedef struct _maxTravel
    {
        int xMax;
        int yMax;
    } maxTravel_t;

    typedef struct _stepsPerMiliMeter
    {
        int xAmountOfSteps;
        int yAmountOfSteps;
        int xRealDistance;
        int yRealDistance;
    } stepsPerMiliMeter_t;

    typedef enum _plane
    {
        XY = 0,
        XZ,
        YZ
    } plane_t;

    /**
    * Implementation of a GRBLTranslator
    */
    class GRBLTranslator
    {
    private:
        static const int defaultMinimumStepPulseWidth = 25;
        const int microsteps = 16; // 1, 2, 4, 16 degrecess the torque
        int feedRate = 2400;       // movement speed of the arm
        bool homeSet = true;      // check for move to home function
        bool metric = true;        // effects the output for strate line movement
        int curentX;               // contians the x postion of the last move
        int curentY;               // contians the y postion of the last move

        std::string GcodeMoveAlgoritme(int starting, int end, std::string base);

    public:
        /**
        * @param inverAxis when the x bool is TRUE the x-axis will be inverted, same goes for the y-axis
        */
        std::string inverdAxises(const invertedAxises_t inverAxis);

        /**
        * @param axisNumber 110 = X, 111 = Y, 112 = Z
        * @param maxSpeed the maximum speed for the selected axis
        */
        std::string mapMaxSpeed(const int axisNumber, const int maxSpeed);

         /**
        * @param axisNumber 120 = X, 121 = Y, 122 = Z
        * @param maxSpeed the maximum speed for the selected axis
        */
        std::string mapAcceleration(const int axisNumber, const int maxAccel);

       /**
        * @param axisNumber 130 = X, 131 = Y, 132 = Z
        * @param maxSpeed the maximum speed for the selected axis
        */
        std::string mapSoftLimits(const int axisNumber, const int maxTravel);

        /**
        * @param axisNumber 100 = X, 101 = Y, 102 = Z
        * @param AmountOfSteps amount of steps take to get to set distance
        * @param realDistance distance in mm or in depence on setUnitMecherment();
        */
        std::string mapAxisMovement(const int axisNumber, const float AmountOfSteps, const int realDistance);

        /**
        * @param StepPulse 
        */
        std::string mapStepPulse(const int StepPulse);

        /**
        *  @param setXHome sets x home on current position x position\n
        *  @param setYHome sets y home on current position y position
        */
        std::string setHome(const bool setXHome, const bool setYHome);

        /**
        * sets plane XY, XZ, YZ
        */
        std::string setPlane(const plane_t workingPlane);

        /**
        *  @param metric if boolean is set the mercherment are in mm else it wilbe in inches
        */
        std::string setUnitMecherment(const bool metric);

        /**
        *   if home is set it wil move to this position
        */
        std::string returnToHomePos();

        /**
        *   enable's the us of softlimits from mapSoftLimits()
        *   @param enabled true enables soft limits
        */
        std::string enableSoftLimits(bool enabled);


        /**
        *   hardware switches are needed to use it!
        *   @param enabled true enables hard limits
        */
        std::string enableHardLimits(bool enabled);

        /**
        *   move to general area form the last position 
        *   a move to the home position is recomande after using it
        *   @param move contains the 2 position on the checkerboard en take boolean
        */
        std::queue<std::string> move(CheckerMove move);
    };

}