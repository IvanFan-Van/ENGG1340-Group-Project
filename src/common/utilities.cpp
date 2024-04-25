#include "battleship/board.h"
#include "common/utilities.h"
#include <iostream>

using namespace std;

// New function to display both boards side by side
void displayBoardsSideBySide(const Board &playerBoard,
                             Board &opponentBoard, bool showPlayerShips, int x, int y,
                             bool showOpponentShips = false) {
  clearScreen();
  bool isValid = opponentBoard.isHit(x, y);
  cout << "  0 1 2 3 4 5 6 7 8 9      0 1 2 3 4 5 6 7 8 9\n";
  for (int i = 0; i < BOARD_SIZE; ++i) {
    // Display player's board row
    cout << char('A' + i) << ' ';
    if (x == i){
      playerBoard.displayRow(i, showPlayerShips, y);
    }
    else{
      playerBoard.displayRow(i, showPlayerShips, -1);
    }
    cout << "   "; // Space between boards

    // Display computer's board row
    cout << char('A' + i) << ' ';
    opponentBoard.displayRow(i, showOpponentShips, -1);
    cout << endl;
  }
}

void clearScreen() { cout << "\033[2J\033[1;1H"; }

void clearBoard() {
  cout << "\033[8A]";
  for (int i = 0; i < 11; i++) {
    cout << "\033[2K\033[1A";
  }
}