#include "common/game_logic.h"
#include "common/utilities.h"
#include <iostream>
#include <regex>

using namespace std;

// void GameLogic::placeShips(Board &board, int shipSize) {
//   while (true) {
//     board.display(true);
//     cout << "Place ship of size " << shipSize << endl;
//     cout << "Enter coordinates (e.g., A1) and orientation (0 for horizontal,
//     "
//             "1 for vertical): ";
//     string input;
//     getline(cin, input);

//     // Regular expression to match the input format
//     regex pattern("[A-J][0-9] [01]");

//     if (!regex_match(input, pattern)) {
//       cout << RED << "Invalid input! Try again.\n\n" << RESET_COLOR;
//       continue;
//     }

//     // Parse the input
//     char row = input[0];
//     int col = input[1] - '0';
//     int orientation = input[3] - '0';

//     int x = row - 'A';
//     int y = col;
//     if (board.isValidPlacement(x, y, shipSize, orientation == 1)) {
//       board.placeShip(x, y, shipSize, orientation == 1);
//       break;
//     } else {
//       cout << RED << "Invalid placement! Try again.\n" << RESET_COLOR;
//     }
//   }
// }

void GameLogic::placeShips(Board &board, Ship &ship) {
  int shipSize = ship.size;
  char key;
  bool placed = false;
  int x = STARTPOINT, y = STARTPOINT;
  bool isVertical = true;
  board.DisplayColorPlacement(x, y, shipSize, isVertical);
  while (!placed) {
    key = keyboard();
    switch (key) {
    case 'w':
      if (x > 0) {
        x -= 1;
        board.DisplayColorPlacement(x, y, shipSize, isVertical);
      }
      break;
    case 'a':
      if (y > 0) {
        y -= 1;
        board.DisplayColorPlacement(x, y, shipSize, isVertical);
      }
      break;
    case 's':
      if (x < BOARD_SIZE - (isVertical ? shipSize : 1)) {
        x += 1;
        board.DisplayColorPlacement(x, y, shipSize, isVertical);
      }
      break;
    case 'd':
      if (y < BOARD_SIZE - (isVertical ? 1 : shipSize)) {
        y += 1;
        board.DisplayColorPlacement(x, y, shipSize, isVertical);
      }
      break;
    case 'C': // change orientation
      if ((isVertical ? y : x) + shipSize <= BOARD_SIZE) {
        isVertical = !isVertical;
        board.DisplayColorPlacement(x, y, shipSize, isVertical);
      }
      break;
    case 'Y': // choice made
      if (board.isValidPlacement(x, y, shipSize, isVertical)) {
        placed = true;
        if (isVertical) {
          for (int i = x; i < x + shipSize; ++i) {
            ship.addCell({i, y});
          }
        } else {
          for (int i = y; i < y + shipSize; ++i) {
            ship.addCell({x, i});
          }
        }
        // 将船放入船队
        board.placeShip(ship);
      }
      break;
    case 'N': // 加了个中途退出功能，此处待定
      placed = true;
      break;
    }
  }
}

void GameLogic::getMoveFromPlayer(Board playerBoard, Board opponentBoard,
                                  int &x, int &y) {
  displayBoardsSideBySide(playerBoard, opponentBoard, true);
  // 获取用户输入
  string input;
  // 解析用户输入
  char row;
  int col;
  while (true) {
    cout << "\nYour turn.\nEnter coordinates to fire: ";
    getline(cin, input);
    regex pattern("[A-J][0-9]");
    if (!regex_match(input, pattern)) {
      cout << RED << "Invalid input! Try again.\n" << RESET_COLOR;
      continue;
    }
    row = input[0];
    col = input[1] - '0';
    x = row - 'A';
    y = col;
    if (opponentBoard.isHit(x, y)) {
      cout << RED << "You've already fired at this location! Try again.\n"
           << RESET_COLOR;
    } else {
      break;
    }
  }
}