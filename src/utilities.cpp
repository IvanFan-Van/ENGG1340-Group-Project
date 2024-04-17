#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "battleship/utilities.h"
#include "battleship/constants.h"
#include "battleship/board.h"

using namespace std;

void displayBoardsSideBySide(const Board &playerBoard, const Board &computerBoard, bool showPlayerShips) {
    cout << "  1 2 3 4 5 6 7 8 9 10     1 2 3 4 5 6 7 8 9 10\n";
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        // Display player's board row
        cout << char('A' + i) << ' ';
        playerBoard.displayRow(i, showPlayerShips);
        cout << "   "; // Space between boards

        // Display computer's board row
        cout << char('A' + i) << ' ';
        computerBoard.displayRow(i, false);
        cout << endl;
    }
}