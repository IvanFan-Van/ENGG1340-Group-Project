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
  Board() {};

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
  bool allShipsSunk() {return true;};

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
  Point getRandomPoint() {
    return {0, 0};
  };
};

/**
 * @brief
 *
 * Displays the player's board and the computer's board side by side.
 *
 * @param playerBoard The player's board.
 * @param computerBoard The computer's board.
 */
void displayBoardsSideBySide(const Board &playerBoard, const Board &computerBoard, bool showPlayerShips);

/**
 * @class Game
 * @brief Represents the game logic and flow.
 *
 * The Game class is responsible for managing the game logic and flow. It includes functions for placing ships, executing moves, and starting the game.
 */
class Game
{
private:
    Board playerBoard;
    Board computerBoard;
    bool playerTurn;
    void placeShips(Board &board, bool isPlayer){
        for (int shipSize : SHIPS){
            while (true){
                if (isPlayer){
                    board.display(true);
                    cout << "Place the size of ship " << shipSize << endl;
                    cout << "Enter coordinates (e.g., A 1 0 (A:column, 1:row and orientation (0 for horizontal, 1 for vertical): ";
                    char col;
                    int row, orientation;
                    cin >> col >> row >> orientation;
                    if((col>'J'||col<'A')||(row<1||row>10)||(orientation!=0&&orientation!=1)){
                        cout<<"invalid input value, please try again"<<endl;
                        continue;
                    }
                    int x = col - 'A';
                    int y = row - 1;
                    if (board.isValidPlacement(x, y, shipSize, orientation == 1)){
                        board.placeShip(x, y, shipSize, orientation == 1);
                        break;
                    }
                    else{
                        cout << "Invalid placement! Try again.\n";
                    }
                }
                else{
                    Point p = board.getRandomPoint();
                    bool isVertical = (rand() % 2 == 0);
                    if (board.isValidPlacement(p.x, p.y, shipSize, isVertical)){

                        board.placeShip(p.x, p.y, shipSize, isVertical);
                        break;
                    }
                }
            }
        }
    }

    void playerMove(){
        displayBoardsSideBySide(playerBoard, computerBoard, true);//The player need to see their own boat
        cout << "\nYour turn.\nEnter coordinates (e.g. A 1) to fire: " ;
        char col;
        int row;
        cin >> col >> row;
        while(true){
          if((col>'J'||col<'A')||(row<1||row>10)){
                        cout<<"invalid input value, please try again"<<endl;
                        cin >> col >> row;
                        
          }
          else{
            break;
          }
        }
        int x = col - 'A';
        int y = row - 1;
        if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE){
            if (computerBoard.checkHit(x, y)){
                cout << "Hit!\n";
            }
            else{
                cout << "Miss!\n";
            }
        }
        else{
            cout << "Invalid coordinates!\n";
        }
    }

    void computerMove(){
        while (true){
            Point p = playerBoard.getRandomPoint();
            if (!playerBoard.isOccupied(p.x, p.y)){
                if (playerBoard.checkHit(p.x, p.y)){
                  cout << "Computer's turn: Hit at " << char('A' + p.x) << p.y + 1 << endl;
                }
                else{
                  cout << "Computer's turn: Miss at " << char('A' + p.x) << p.y + 1 << endl;
                }
              break;
            }
        }
    }

public:
  Game(){
    srand(time(0));
    placeShips(playerBoard, true);
    placeShips(computerBoard, true);
  }

  void start(){
    while(true){
      if(playerTurn){
        playerMove();
        if(computerBoard.allShipsSunk()){
          cout<<"congratulations, you have win!"<<endl;
          break;
        }
      }
      else{
        computerMove();
        if(playerBoard.allShipsSunk()){
          cout<<"Oh no, you lose."<<endl;
          break;
        }
      }
    }
  }
};

int main()
{
  Game battleshipGame;
  battleshipGame.start();
  return 0;
}