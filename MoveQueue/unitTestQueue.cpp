#include "queue.hpp"
#include <iostream>

using namespace ArduinoAPI;
using std::cout, std::endl;

int main(void)
{
    MoveQueue queue;
    CheckerMove move("A2", "B4", 1);

    queue.push(move);
    queue.push(move);
    queue.push(move);

    cout << "queue size is: " << queue.size() << ", en should be '3'\n";
    if(queue.size() != 3) cout << "queue size did not match!!\n";


    cout << "frist pop of the stack\n";
    ChessMove res = queue.front();
    queue.pop();
    
    const BoardPosition bPos = res.getBpos();
    const BoardPosition ePos = res.getEpos();

    cout << "reseved start position (" << bPos.getColumn() << ", " << bPos.getRow() << ")";
    cout << ", end position(" << ePos.getColumn() << ", " << ePos.getRow() << "), take is: " << res.getTake() << endl;

    queue.pop();
    queue.pop();
    return 0;
}
