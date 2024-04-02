#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int BOARD_SIZE = 10;
const int SHIPS[] = {4, 3, 2, 1}; // Number of ships of each size
const char EMPTY = '.';
const char SHIP = 'S';
const char HIT = 'X';
const char MISS = 'O';

struct Point
{
  int x;
  int y;
};

/**
 * @class Board
 * @brief Represents the game board.
 *
 * The Board class is responsible for managing the game board and performing operations on it.
 * It keeps track of the positions of ships, hits on the opponent's board, and provides functions
 * to display the board, place ships, check hits, and more.
 */
class Board
{
private:
  char board[BOARD_SIZE][BOARD_SIZE]; /**< The game board */
  bool hits[BOARD_SIZE][BOARD_SIZE];  /**< For tracking hits on opponent's board */

public:
  /**
   * @brief Default constructor for the Board class.
   */
  Board();

  /**
   * @brief Display the board.
   *
   * This function displays the game board. If showShips is true, it also displays the ships on the board.
   *
   * @param showShips Whether to display ships on the board. For player, it is true; for opponent, it is false.
   */
  void display(bool showShips);

  /**
   * @brief Checks if a ship can be placed at the given position.
   *
   * This function checks if a ship of a given size can be placed at a given position on the board.
   * The position is specified by the coordinates of the ship's head. The orientation of the ship
   * (vertical or horizontal) is also taken into account.
   *
   * @param x The x-coordinate of the ship's head.
   * @param y The y-coordinate of the ship's head.
   * @param size The size of the ship.
   * @param isVertical The orientation of the ship. If true, the ship is vertical. If false, the ship is horizontal.
   * @return true If the ship can be placed at the given position.
   * @return false If the ship cannot be placed at the given position (e.g., it would go off the board or overlap with another ship).
   */
  bool isValidPlacement(int x, int y, int size, bool isVertical);

  /**
   * @brief Place a ship on the board.
   *
   * This function places a ship of a given size at the given position on the board.
   * The position is specified by the coordinates of the ship's head. The orientation of the ship
   * (vertical or horizontal) is also taken into account.
   *
   * @param x The x-coordinate of the ship's head.
   * @param y The y-coordinate of the ship's head.
   * @param size The size of the ship.
   * @param isVertical The orientation of the ship. If true, the ship is vertical. If false, the ship is horizontal.
   */
  void placeShip(int x, int y, int size, bool isVertical);

  /**
   * @brief Check if a position has been hit.
   *
   * This function checks if a position on the opponent's board has been hit.
   *
   * @param x The x-coordinate of the position.
   * @param y The y-coordinate of the position.
   * @return true If the position has been hit.
   * @return false If the position has not been hit.
   */
  bool checkHit(int x, int y);

  /**
   * @brief Check if all ships have been sunk.
   *
   * This function checks if all ships on the board have been sunk.
   *
   * @return true If all ships have been sunk.
   * @return false If not all ships have been sunk.
   */
  bool allShipsSunk();

  /**
   * @brief Check if a position is occupied by a ship.
   *
   * This function checks if a position on the board is occupied by a ship.
   *
   * @param x The x-coordinate of the position.
   * @param y The y-coordinate of the position.
   * @return true If the position is occupied by a ship.
   * @return false If the position is not occupied by a ship.
   */
  bool isOccupied(int x, int y);

  /**
   * @brief Display a row of the board.
   *
   * This function displays a single row of the board. If showShips is true, it also displays the ships on the row.
   *
   * @param row The row number to display.
   * @param showShips Whether to display ships on the row. For player, it is true; for opponent, it is false.
   */
  void displayRow(int row, bool showShips);

  /**
   * @brief Get a random point on the board.
   *
   * This function returns a random point on the board.
   *
   * @return Point A random point on the board.
   */
  Point getRandomPoint();
};

/**
 * @brief
 *
 * Displays the player's board and the computer's board side by side.
 *
 * @param playerBoard The player's board.
 * @param computerBoard The computer's board.
 */
void displayBoardsSideBySide(const Board &playerBoard, const Board &computerBoard);

/**
 * @class Game
 * @brief Represents the game logic and flow.
 *
 * The Game class is responsible for managing the game logic and flow. It includes functions for placing ships, executing moves, and starting the game.
 */
class Game
{
private:
  Board playerBoard;   // The board representing the player's ships and attacks.
  Board computerBoard; // The board representing the computer's ships and attacks.
  bool playerTurn;     // A flag indicating whether it is the player's turn.

  /**
   * @brief Places the ships on the given board.
   *
   * This function is used to place the ships on the board for either the player or the computer.
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

  /**
   * @brief Starts the game.
   *
   * This function starts the game by initializing the boards, placing the ships, and executing the turns until the game is over.
   */
  void start();
};

int main()
{
  Game battleshipGame;
  battleshipGame.start();
  return 0;
}