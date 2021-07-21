#include "GRBLTranslator.hpp"
#include <iostream>

using ArduinoAPI::GRBLTranslator;

std::string GRBLTranslator::inverdAxises(const invertedAxises_t inverAxis)
{
    std::string command = {};

    if (inverAxis.xAxis && inverAxis.yAxis)
    {
        command += "$3=3";
    }
    else if (!inverAxis.xAxis && inverAxis.yAxis)
    {
        command += "$3=2";
    }
    else if (inverAxis.xAxis && !inverAxis.yAxis)
    {
        command += "$3=1";
    }
    else
    {
        command += "$3=0";
    }
    return command;
}

std::string GRBLTranslator::mapMaxSpeed(const int axisNumber, const int maxSpeed)
{
    std::string command = {};
    command += "$";
    command += std::to_string(axisNumber);
    command += "=";
    command += std::to_string(maxSpeed);
    return command;
}

std::string GRBLTranslator::mapAcceleration(const int axisNumber, const int maxAccel)
{
    std::string command = {};
    command += "$";
    command += std::to_string(axisNumber);
    command += "=";
    command += std::to_string(maxAccel);
    return command;
}

std::string GRBLTranslator::mapSoftLimits(const int axisNumber, const int maxTravel)
{
    std::string command = {};
    command += "$";
    command += std::to_string(axisNumber);
    command += "=";
    command += std::to_string(maxTravel);
    return command;
}

std::string GRBLTranslator::mapAxisMovement(const int axisNumber, const float AmountOfSteps, const int realDistance)
{
    std::string command = {};
    command += "$";
    command += std::to_string(axisNumber);
    command += "=";
    command += std::to_string((AmountOfSteps * microsteps) / realDistance);
    return command;
}

std::string GRBLTranslator::mapStepPulse(const int StepPulse)
{
    std::string command = {};
    command += "$0=";

    if (StepPulse < defaultMinimumStepPulseWidth)
    {
        command += std::to_string(defaultMinimumStepPulseWidth);
        return command;
    }
    command += std::to_string(StepPulse);
    return command;
}

std::string GRBLTranslator::setHome(const bool setXHome, const bool setYHome)
{
    if (setXHome && setYHome)
    {
        return "G10 P0 L20 X0 Y0";
    }
    else if (setXHome)
    {
        homeSet = true;
        ;
        return "G10 P0 L20 X0";
    }
    else if (setYHome)
    {
        return "G10 P0 L20 Y0";
    }
    return "";
}

std::string GRBLTranslator::setPlane(const plane_t workingPlane)
{
    switch (workingPlane)
    {
    case XY:
        return "G17";
        break;

    case XZ:
        return "G18";
        break;

    case YZ:
        return "G19";
        break;
    }
    return "";
}

std::string GRBLTranslator::setUnitMecherment(const bool metric)
{
    if (metric)
    {
        return "G21";
    }
    return "G20";
}

std::string GRBLTranslator::returnToHomePos()
{
    if (!homeSet)
    {
        return "";
    }
    return "G90 G0 X0 Y0\n";
}

std::queue<std::string> GRBLTranslator::move(CheckerMove move)
{
    std::queue<std::string> queue = {};
    std::string res = {};

    BoardPosition bPos = move.getBpos();
    BoardPosition ePos = move.getEpos();

    if (!move.getTake())
    {
        queue.push(returnToHomePos());
        res = GcodeMoveAlgoritme(0, (bPos.getColumn() - 'A') + 1, "G21G91X");
        res = GcodeMoveAlgoritme(0, bPos.getRow(), res + "Y");
        res += "F127000";
        queue.push(res);

        res = GcodeMoveAlgoritme((bPos.getColumn() - 'A') + 1, (ePos.getColumn() - 'A') + 1, "G21G91X");
        res = GcodeMoveAlgoritme(bPos.getRow(), ePos.getRow(), res + "Y");
        res += "F127000";
        queue.push(res);
        queue.push(returnToHomePos());
        queue.push("G21G91X-40F127000");
    }
    else
    {
        queue.push(returnToHomePos());
        res = GcodeMoveAlgoritme(0, (ePos.getColumn() - 'A') + 1, "G21G91X");
        res = GcodeMoveAlgoritme(0, ePos.getRow(), res + "Y");
        res += "F127000";
        queue.push(res);

        res = GcodeMoveAlgoritme((ePos.getColumn() - 'A') + 1, (ePos.getColumn() - 'A') + 1, "G21G91X");
        res = GcodeMoveAlgoritme(ePos.getRow(), 9, res + "Y");
        res += "F127000";
        queue.push(res);

        res = GcodeMoveAlgoritme((ePos.getColumn() - 'A') + 1, (bPos.getColumn() - 'A') + 1, "G21G91X");
        res = GcodeMoveAlgoritme(9, bPos.getRow(), res + "Y");
        res += "F127000";
        queue.push(res);

        res = GcodeMoveAlgoritme((ePos.getColumn() - 'A') + 1, (ePos.getColumn() - 'A') + 1, "G21G91X");
        res = GcodeMoveAlgoritme(bPos.getRow(), ePos.getRow(), res + "Y");
        res += "F127000";
        queue.push(res);
        queue.push(returnToHomePos());
        queue.push("G21G91X-40F127000");
    }

    return queue;
}

std::string GRBLTranslator::GcodeMoveAlgoritme(int starting, int end, std::string base)
{
    float mv = delta(starting, end)* 33;
    //std::cout << "starting: " << starting <<"\n";
    //std::cout << "end: " << end <<"\n";

    if (mv > 0)
    {
        mv -= 18;
    }
    else if (mv < 0)
    {
        mv += 18;
    }
    else
    {
        base.erase(base.size() - 1);
        return base;
    }

    //std::cout << "delta mv: " << mv << std::endl;
    return (base + std::to_string(mv));
}

std::string GRBLTranslator::enableSoftLimits(bool enabled)
{
    return "$20=" + std::to_string(enabled);
}

std::string GRBLTranslator::enableHardLimits(bool enabled)
{
    return "$21=" + std::to_string(enabled);
}
