#include "CheckersRobotInterface.hpp"

using ArduinoAPI::BoardPosition;
using ArduinoAPI::CheckersRobotInterface;
using std::string;
using namespace std::chrono;

CheckersRobotInterface::~CheckersRobotInterface()
{
    running = false;
    disconnect();
}

CheckersRobotInterface::CheckersRobotInterface()
{
}

bool CheckersRobotInterface::connect()
{
    using namespace std::chrono;

    if (!connected)
    {
        if ((fd = serialOpen("/dev/ttyACM0", 115200)) > 0)
        {
            std::cout << "Connected to Arduino [/dev/ttyACM0]\n";
        }
        else if ((fd = serialOpen("/dev/ttyACM1", 115200)) > 0)
        {
            std::cout << "Connected to Arduino [/dev/ttyACM1]\n";
        }
        else
        {
            return 0;
        }

        string res = {};
        while ((serialDataAvail(fd) <= 0))
        {
        }
        while ((serialDataAvail(fd) > 0))
        {
            res += char(serialGetchar(fd));
            std::this_thread::sleep_for(15ms);
        }
        std::cout << "response is:\n"
                  << res << std::endl;
        fflush(stdout);

        if (fd > 0)
        {
            running = true;
            connected = true;
            std::cout << "thread made\n";
            std::cout << "running test: " << running << "\n";
            std::cout << "fd test: " << fd << "\n";
            std::cout << "connected test: " << connected << "\n";
            std::this_thread::sleep_for(350ms);
            processingThread = new std::thread(scheduler, &running, &connected, &GCodeQueue, &fd, &moveQueue); //

            return true;
        }
    }
    return connected;
}

bool CheckersRobotInterface::move(BoardPosition &startPosition, BoardPosition &endPosition, bool endPositionContainsChessPiece)
{
    if (!connected)
    {
        std::cout << "Arduino is not connected\n";
        return false;
    }
    else
    {
        CheckerMove move(startPosition, endPosition, endPositionContainsChessPiece);
        moveQueue.push(move);
    }

    return true;
}

bool CheckersRobotInterface::disconnect()
{
    if (connected)
    {
        connected = false;
        running = false;
        std::cout << "closing thread\n";
        processingThread->join();
        delete processingThread;
        std::cout << "thread closed\n";
        serialClose(fd);
        fd = -1;
        std::cout << "Disconnected from Arduino\n";
    }

    return true;
}

void CheckersRobotInterface::scheduler(bool *isRunning, bool *isConnected, std::queue<std::string> *GCodeQueue, int *fd, ArduinoAPI::MoveQueue *moveQueue) //
{
    GRBLTranslator translator;
    string res = {};
    serialPuts(*fd, "G21G91X-40F12700\n"); 
    while ((serialDataAvail(*fd) <= 0))
    {
    }
    while ((serialDataAvail(*fd) > 0))
    {
        res += char(serialGetchar(*fd));
        std::this_thread::sleep_for(15ms);
    }
    while (*isRunning)
    {
        if (!moveQueue->empty())
        {
            std::cout << "moveQueue buffer is niet leeg\n";
            CheckerMove move = moveQueue->front();
            BoardPosition bPos = move.getBpos();
            std::cout << move.getTake() << ", bPos: " << bPos.getColumn() << bPos.getRow() << "\n";
            std::queue<std::string> tmp = translator.move(moveQueue->front());
            while (!tmp.empty())
            {
                GCodeQueue->push(tmp.front());
                std::cout << "G-code is: " << tmp.front() << "\n";
                tmp.pop();
            }
            fflush(stdout);

            moveQueue->pop();
        }

        if (!GCodeQueue->empty())
        {
            int i = 0;
            string msg = GCodeQueue->front();
            GCodeQueue->pop();
            string res = {};
            msg += "\n";
            std::cout << "sending G code: " << msg.c_str() << std::endl;
            serialPuts(*fd, (char *)msg.c_str()); //
            while ((serialDataAvail(*fd) <= 0))
            {
            }
            while ((serialDataAvail(*fd) > 0))
            {
                res += char(serialGetchar(*fd));
                std::this_thread::sleep_for(15ms);
            }
            std::cout << "response is:\n"
                      << res << std::endl;
            fflush(stdout);
            std::this_thread::sleep_for(15s);
        }

        std::this_thread::sleep_for(250ms); 
    }
     res = {};
    serialPuts(*fd, "G90 G0 X0 Y0\n"); 
    while ((serialDataAvail(*fd) <= 0))
    {
    }
    while ((serialDataAvail(*fd) > 0))
    {
        res += char(serialGetchar(*fd));
        std::this_thread::sleep_for(15ms);
    }
    std::cout << "response is:\n" << res << std::endl;
    fflush(stdout);
}