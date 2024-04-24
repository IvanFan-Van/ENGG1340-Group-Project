#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "battleship/color.h"
#include <string>

const int BOARD_SIZE = 10;
// const int SHIPS[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
const int SHIPS[] = {1};
extern const char EMPTY;
extern const char SHIP;
extern const char HIT;
extern const char MISS;

extern const std::string EMPTY_CELL;
extern const std::string SHIP_CELL;
extern const std::string HIT_CELL;
extern const std::string MISS_CELL;

#endif // CONSTANTS_H