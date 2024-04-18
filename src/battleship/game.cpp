#include <iostream>
#include "battleship/board.h"
#include "battleship/constants.h"
#include "battleship/utilities.h"


using namespace std;

class Game
{
private:
  Board playerBoard;
  Board computerBoard;
  bool playerTurn;
  void placeShips(Board &board, bool isPlayer)
  {
    for (int shipSize : SHIPS)
    {
      while (true)
      {
        if (isPlayer)
        {
          board.display(true);
          cout << "Place the size of ship " << shipSize << endl;
          cout << "Enter coordinates (e.g., A 1 0 (A:column, 1:row and orientation (0 for horizontal, 1 for vertical): ";
          char col;
          int row, orientation;
          cin >> col >> row >> orientation;
          if ((col > 'J' || col < 'A') || (row < 1 || row > 10) || (orientation != 0 && orientation != 1))
          {
            cout << "invalid input value, please try again" << endl;
            continue;
          }
          int x = col - 'A';
          int y = row - 1;
          if (board.isValidPlacement(x, y, shipSize, orientation == 1))
          {
            board.placeShip(x, y, shipSize, orientation == 1);
            break;
          }
          else
          {
            cout << "Invalid placement! Try again.\n";
          }
        }
        else
        {
          Point p = board.getRandomPoint();
          bool isVertical = (rand() % 2 == 0);
          if (board.isValidPlacement(p.x, p.y, shipSize, isVertical))
          {

            board.placeShip(p.x, p.y, shipSize, isVertical);
            break;
          }
        }
      }
    }
  }

  void playerMove()
  {
    displayBoardsSideBySide(playerBoard, computerBoard, true); // The player need to see their own boat
    cout << "\nYour turn.\nEnter coordinates (e.g. A 1) to fire: ";
    char col;
    int row;
    cin >> col >> row;
    while (true)
    {
      if ((col > 'J' || col < 'A') || (row < 1 || row > 10))
      {
        cout << "invalid input value, please try again" << endl;
        cin >> col >> row;
      }
      else
      {
        break;
      }
    }
    int x = col - 'A';
    int y = row - 1;
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
    {
      if (computerBoard.checkHit(x, y))
      {
        cout << "Hit!\n";
      }
      else
      {
        cout << "Miss!\n";
      }
    }
    else
    {
      cout << "Invalid coordinates!\n";
    }
  }

  void computerMove()
  {
    while (true)
    {
      Point p = playerBoard.getRandomPoint();
      if (!playerBoard.isOccupied(p.x, p.y))
      {
        if (playerBoard.checkHit(p.x, p.y))
        {
          cout << "Computer's turn: Hit at " << char('A' + p.x) << p.y + 1 << endl;
        }
        else
        {
          cout << "Computer's turn: Miss at " << char('A' + p.x) << p.y + 1 << endl;
        }
        break;
      }
    }
  }

public:
  Game()
  {
    srand(time(0));
    placeShips(playerBoard, true);
    placeShips(computerBoard, true);
  }

  void start()
  {
    while (true)
    {
      if (playerTurn)
      {
        playerMove();
        if (computerBoard.allShipsSunk())
        {
          cout << "congratulations, you have win!" << endl;
          break;
        }
      }
      else
      {
        computerMove();
        if (playerBoard.allShipsSunk())
        {
          cout << "Oh no, you lose." << endl;
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