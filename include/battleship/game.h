#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H

#include "board.h"
#include "common/game_logic.h"
#include <string>

using namespace std;

class Game {
private:
  Board playerBoard; // The board representing the player's ships and attacks.
  Board
      computerBoard; // The board representing the computer's ships and attacks.
  bool playerTurn;   // A flag indicating whether it is the player's turn.
  GameLogic gameLogic; // An instance of the GameLogic class.
  /**
   * @brief Places the ships on the given board.
   *
   * This function is used to place the ships on the board for either the player
   * or the computer.
   *
   * @param board The board on which to place the ships.
   * @param isPlayer A flag indicating whether the board belongs to the player.
   */
  void placeShips(Board &board, bool isPlayer);

  /**
   * @brief Executes the player's move.
   *
   * This function is called when it is the player's turn to make a move.
   */
  void playerMove();

  /**
   * @brief Executes the computer's move.
   *
   * This function is called when it is the computer's turn to make a move.
   */
  void computerMove();

public:
  /**
   * @brief Default constructor for the Game class.
   */
  Game();

  ~Game();

  /**
   * @brief Starts the game.
   *
   * This function starts the game by initializing the boards, placing the
   * ships, and executing the turns until the game is over.
   */
  void start();
};

#endif // BATTLESHIP_GAME_H