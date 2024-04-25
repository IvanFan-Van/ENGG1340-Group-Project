#ifndef BATTLESHIP_UTILITIES_H
#define BATTLESHIP_UTILITIES_H

#include "battleship/board.h"

void displayBoardsSideBySide(const Board &playerBoard,
                             Board &opponentBoard, bool showPlayerShips, int x, int y,
                             bool showOpponentShips);

void clearScreen();

void clearBoard();

#endif // BATTLESHIP_UTILITIES_H