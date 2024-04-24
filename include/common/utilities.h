#ifndef BATTLESHIP_UTILITIES_H
#define BATTLESHIP_UTILITIES_H

#include "battleship/board.h"

void displayBoardsSideBySide(const Board &playerBoard,
                             const Board &opponentBoard, bool showPlayerShips,
                             bool showOpponentShips = false);

void clearScreen();

void clearBoard();

#endif // BATTLESHIP_UTILITIES_H