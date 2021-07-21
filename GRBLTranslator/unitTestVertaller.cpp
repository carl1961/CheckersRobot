#include "GRBLTranslator.hpp"
#include <iostream>
#include <thread>

using namespace ArduinoAPI;

int main(void)
{
    GRBLTranslator GcodeMaker;
    invertedAxises_t inverAxis = {true, true};

    CheckerMove move("A2", "B4", true);
    CheckerMove move1("A2", "B4", false);

    std::queue<std::string> queue = {};

    queue.push(GcodeMaker.inverdAxises(inverAxis));
    queue.push(GcodeMaker.mapMaxSpeed(110, 400));
    queue.push(GcodeMaker.mapMaxSpeed(111, 400));
    queue.push(GcodeMaker.mapAcceleration(120, 24));
    queue.push(GcodeMaker.mapAcceleration(121, 24));
    //queue.push(GcodeMaker.enableSoftLimits(true));
    //queue.push(GcodeMaker.mapSoftLimits(130, 300));
    //queue.push(GcodeMaker.mapSoftLimits(131, 300));
    queue.push(GcodeMaker.enableHardLimits(true));
    queue.push(GcodeMaker.setUnitMecherment(true));
    queue.push(GcodeMaker.mapAxisMovement(100, 130.6f, 4)); // moet ff gecheckt worden.
    queue.push(GcodeMaker.mapAxisMovement(101, 113.0f, 4)); // moet ff gecheckt worden.
    queue.push(GcodeMaker.setHome(true,true));

    std::queue<std::string> tmp = GcodeMaker.Move(move);
    queue.push("");
    //queue.push("\neerst move stappen:\n");
    while (!tmp.empty())
    {
        queue.push(tmp.front());
        tmp.pop();
    }

    tmp = GcodeMaker.Move(move1);
    
    queue.push("");

    //queue.push("\ntweede move stappen:\n");
    while (!tmp.empty())
    {
        queue.push(tmp.front());
        tmp.pop();
    }

    //queue.push("");

    while (!queue.empty())
    {   
        std::cout << "G code msg is: \"" << queue.front() << "\"\n";
        queue.pop();
    }

    return 0;
}