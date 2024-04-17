<<<<<<< HEAD
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Point
{
  int x;
  int y;
}
=======
#pragma once
#include "point.h"
#include "constants.h"

class Board
{
public:
    char board[BOARD_SIZE][BOARD_SIZE];
    bool hits[BOARD_SIZE][BOARD_SIZE];

    Board();
    Board(char board[BOARD_SIZE][BOARD_SIZE]);
    void display(bool showShips);
    bool isValidPlacement(int x, int y, int size, bool isVertical);
    void placeShip(int x, int y, int size, bool isVertical);
    bool checkHit(int x, int y);
    bool allShipsSunk();
    bool isOccupied(int x, int y);
    void displayRow(int row, bool showShips) const;
    bool allShipsPlaced();
    Point getRandomPoint();
>>>>>>> f7c581d642e0c0c4ca574c75d6fa755c5117cb3b
};