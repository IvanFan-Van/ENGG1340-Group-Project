#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "color.h"
#include <string>

const int BOARD_SIZE = 10;
const int SHIPS[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
// const int SHIPS[] = {1};
// Cell types
const char EMPTY = '.';
const char SHIP = 'S';
const char HIT = 'X';
const char MISS = 'O';
// Colored cells
const std::string EMPTY_CELL = RESET_COLOR + EMPTY + RESET_COLOR;
const std::string SHIP_CELL = BLUE + SHIP + RESET_COLOR;
const std::string HIT_CELL = MAGENTA + HIT + RESET_COLOR;
const std::string MISS_CELL = CYAN + MISS + RESET_COLOR;

const int STARTPOINT = 4;

#endif // CONSTANTS_H