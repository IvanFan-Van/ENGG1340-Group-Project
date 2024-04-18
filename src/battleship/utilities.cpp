#include "battleship/board.h"
#include <iostream>

using namespace std;

// New function to display both boards side by side
void displayBoardsSideBySide(const Board &playerBoard, const Board &computerBoard, bool showPlayerShips)
{
    cout << "  0 1 2 3 4 5 6 7 8 9      0 1 2 3 4 5 6 7 8 9\n";
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

void clearScreen()
{
    cout << "\033[2J\033[1;1H";
}

void clearBoard()
{
    cout << "\033[8A]";
    for (int i = 0; i < 11; i++)
    {
        cout << "\033[2K\033[1A";
    }
}