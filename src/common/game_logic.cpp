#include "common/game_logic.h"
#include "common/utilities.h"
#include "battleship/keyboard.h"
#include <iostream>
#include <regex>

using namespace std;

bool GameLogic::placeShips(Board &board, Ship &ship) {
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
      return false;
      break;
    }
  }
  return true;
}

bool GameLogic::getMoveFromPlayer(Board playerBoard, Board opponentBoard,
                                  int &i, int &j) {
  bool placed = false;
  i = STARTPOINT, j = STARTPOINT;
  displayBoardsSideBySide(playerBoard, opponentBoard, true, i, j, false);
  while (!placed) {
    char key = keyboard();
    switch (key) {
      case 'w':
        if (i > 0) {
          i -= 1;
          displayBoardsSideBySide(playerBoard, opponentBoard, true, i, j, false);
        }
        break;
      case 'a':
        if (j > 0) {
          j -= 1;
          displayBoardsSideBySide(playerBoard, opponentBoard, true, i, j, false);

        }
        break;
      case 's':
        if (i < BOARD_SIZE - 1) {
          i += 1;
          displayBoardsSideBySide(playerBoard, opponentBoard, true, i, j, false);
        }
        break;
      case 'd':
        if (j < BOARD_SIZE - 1) {
          j += 1;
          displayBoardsSideBySide(playerBoard, opponentBoard, true, i, j, false);
        }
        break;
      case 'Y': // choice made
        if (!opponentBoard.isHit(i, j)) {
          placed = true;
        }
        break;
      case 'N': // 加了个中途退出功能，此处待定
        placed = true;
        return false;
        break;
    }
  }
  return true;
}