#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "battleship/board.h"
#include "battleship/keyboard.h"
#include "color.h"
#include "common/utilities.h"
#include "constants.h"

using namespace std;

class GameLogic {
public:
  // void placeShips(Board &board, int shipSize)
  // {
  //   while (true)
  //   {
  //     board.display(true);
  //     cout << "Place ship of size " << shipSize << endl;
  //     cout << "Enter coordinates (e.g., A1) and orientation (0 for
  //     horizontal, 1 for vertical): "; string input; getline(cin, input);

  //     // Regular expression to match the input format
  //     regex pattern("[A-J][0-9] [01]");

  //     if (!regex_match(input, pattern))
  //     {
  //       cout << RED << "Invalid input! Try again.\n\n"
  //            << RESET_COLOR;
  //       continue;
  //     }

  //     // Parse the input
  //     char row = input[0];
  //     int col = input[1] - '0';
  //     int orientation = input[3] - '0';

  //     int x = row - 'A';
  //     int y = col;
  //     if (board.isValidPlacement(x, y, shipSize, orientation == 1))
  //     {
  //       board.placeShip(x, y, shipSize, orientation == 1);
  //       break;
  //     }
  //     else
  //     {
  //       cout << RED << "Invalid placement! Try again.\n"
  //            << RESET_COLOR;
  //     }
  //   }
  // }

  void placeShips(Board &board, int shipSize);

  void getMoveFromPlayer(Board playerBoard, Board opponentBoard, int &x,
                         int &y);
};

#endif // GAME_LOGIC_H