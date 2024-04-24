#include "battleship/constants.h"
#include <string>

const char EMPTY = '.';
const char SHIP = 'S';
const char HIT = 'X';
const char MISS = 'O';

const std::string EMPTY_CELL = RESET_COLOR + EMPTY + RESET_COLOR;
const std::string SHIP_CELL = BLUE + SHIP + RESET_COLOR;
const std::string HIT_CELL = RED + HIT + RESET_COLOR;
const std::string MISS_CELL = GREY + MISS + RESET_COLOR;