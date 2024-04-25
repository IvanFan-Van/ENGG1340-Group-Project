#ifndef BOARD_H
#define BOARD_H

#include "common/constants.h"
#include "point.h"

class Board {
public:
  char board[BOARD_SIZE][BOARD_SIZE];
  bool hits[BOARD_SIZE][BOARD_SIZE];

  Board();
  Board(char board[BOARD_SIZE][BOARD_SIZE]);
  void display(bool showShips);

  bool isValidPlacement(int x, int y, int size, bool isVertical);

  void placeShip(int x, int y, int size, bool isVertical);

  bool handleHit(int x, int y);

  bool allShipsSunk();

  bool isOccupied(int x, int y);

  bool isHit(int x, int y);

  void displayRow(int row, bool showShips, bool isSelected) const;

  bool allShipsPlaced();

  Point getRandomPoint();

  void DisplayColorPlacement(int x, int y, int size, bool isVertical);
};

#endif // BOARD_H