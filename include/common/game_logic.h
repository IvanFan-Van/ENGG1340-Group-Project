#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "battleship/board.h"
#include "battleship/keyboard.h"
#include "battleship/ship.h"
#include "color.h"
#include "common/utilities.h"
#include "constants.h"

using namespace std;

class GameLogic {
public:
  /**
   * @brief Place ships on the board
   */
  void placeShips(Board &board, Ship &ship);

  /**
   * @brief Get move from the player
   */
  void getMoveFromPlayer(Board playerBoard, Board opponentBoard, int &x,
                         int &y);
};

#endif // GAME_LOGIC_H