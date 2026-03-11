#include "BrickBreaker.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    int size;
    cout << "Enter size: ";
    cin >> size;

    BrickBreaker bb(size, size);

    int numBricks;
    cout << "Enter number of bricks: ";
    cin >> numBricks;

    cout << "Enter brick positions (row col):" << endl;
    for (int i = 0; i < numBricks; i++) {
        int row, col;
        cin >> row >> col;
        bb.placeBricks(row, col, 1); // life = 1 for module 1
    }

    bb.printGameBoard();
    cout << "Ball count:" << bb.getBallLife() << endl;

    string command;
    while (bb.getBallLife() > 0) {
        cout << "\nEnter command (st/lt/rt): ";
        cin >> command;

        if (command == "st") {
            bb.straightHit();
        } else if (command == "lt") {
            int* pos = bb.getBallPosition();
            bb.initiateBall(pos[0], pos[1], -1, -1);
            bb.printGameBoard();
        } else if (command == "rt") {
            int* pos = bb.getBallPosition();
            bb.initiateBall(pos[0], pos[1], -1, 1);
            bb.printGameBoard();
        } else {
            cout << "Invalid command! Use st, lt, or rt." << endl;
            continue;
        }

        cout << "Ball count:" << bb.getBallLife() << endl;
    }

    cout << "Game Over!" << endl;

    return 0;
}
