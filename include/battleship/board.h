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
    bool isHit(int x, int y);
    void displayRow(int row, bool showShips) const;
    bool allShipsPlaced();
    Point getRandomPoint();
    bool withinBoard(int x, int y, int size, bool isVertical);
    void DisplayColorPlacement(int x, int y, int size, bool isVertical);
};