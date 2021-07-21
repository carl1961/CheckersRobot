#include "main.hpp"

using namespace std;
using namespace ArduinoAPI;

int main(void)
{
    CheckersRobotInterface interface;
    bool connected = interface.connect();
    if (!connected)
    {
        return EXIT_FAILURE;
    }

    httplib::Server svr;
    svr.Get("/set", [&interface](const httplib::Request &req, httplib::Response &res)
    {
        auto orgPos = req.get_param_value("org");
        auto newPos = req.get_param_value("new");
        auto take = req.get_param_value("take");

        BoardPosition bPos(orgPos);
        BoardPosition ePos(newPos);
        if (take[0] == '0' || take[0] == '1')
        {
            interface.move(bPos, ePos, take[0] - '0');
        }
    });
    
    svr.listen("0.0.0.0", 12345);

    interface.disconnect();

    return 0;
}