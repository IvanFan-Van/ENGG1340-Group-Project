#include "battleship/board.h"
#include "common/color.h"
#include "common/constants.h"
#include "common/utilities.h"
#include <iostream>

using namespace std;

Board::Board() {
  for (int i = 0; i < BOARD_SIZE; ++i) {
    for (int j = 0; j < BOARD_SIZE; ++j) {
      board[i][j] = EMPTY;
      hits[i][j] = false;
    }
  }
}

Board::Board(char board[BOARD_SIZE][BOARD_SIZE]) {
  for (int i = 0; i < BOARD_SIZE; ++i) {
    for (int j = 0; j < BOARD_SIZE; ++j) {
      this->board[i][j] = board[i][j];
      hits[i][j] = false;
    }
  }
}

void Board::display(bool showShips) {
  cout << "  0 1 2 3 4 5 6 7 8 9\n";
  for (int i = 0; i < BOARD_SIZE; ++i) {
    cout << char('A' + i) << ' ';
    for (int j = 0; j < BOARD_SIZE; ++j) {
      // Show hits or misses accordingly
      if (hits[i][j]) {
        if (board[i][j] == HIT) {
          cout << HIT_CELL << ' ';
        } else {
          cout << MISS_CELL << ' ';
        }
      } else if (showShips && board[i][j] == SHIP) {
        cout << SHIP_CELL << ' '; // Show ships if they are supposed to be shown
      } else {
        cout << EMPTY_CELL << ' '; // Show empty space otherwise
      }
    }
    cout << endl;
  }
}

bool Board::isValidPlacement(int x, int y, int size, bool isVertical) {
  // 加入检查相邻格子的逻辑
  if (isVertical) {
    if (x + size > BOARD_SIZE || y + 1 > BOARD_SIZE)
      return false;
    for (int i = x - 1; i <= x + size; ++i) {
      for (int j = y - 1; j <= y + 1; ++j) {
        if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE &&
            board[i][j] != EMPTY)
          return false;
      }
    }
  } else {
    if (y + size > BOARD_SIZE || x + 1 > BOARD_SIZE)
      return false;
    for (int i = x - 1; i <= x + 1; ++i) {
      for (int j = y - 1; j <= y + size; ++j) {
        if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE &&
            board[i][j] != EMPTY)
          return false;
      }
    }
  }
  return true;
}

bool Board::allShipsPlaced() {
  for (int i = 0; i < BOARD_SIZE; ++i) {
    for (int j = 0; j < BOARD_SIZE; ++j) {
      if (board[i][j] == SHIP) {
        return true;
      }
    }
  }
  return false;
}

void Board::placeShip(int x, int y, int size, bool isVertical) {
  if (isVertical) {
    for (int i = x; i < x + size; ++i) {
      board[i][y] = SHIP;
    }
  } else {
    for (int i = y; i < y + size; ++i) {
      board[x][i] = SHIP;
    }
  }
}

bool Board::handleHit(int x, int y) {
  if (hits[x][y]) {
    // If the position was already hit before, we don't need to change anything
    // Consider providing feedback that the position was already targeted.
    return false;
  }
  hits[x][y] =
      true; // Record the hit attempt regardless of whether it's a hit or miss
  if (board[x][y] == SHIP) {
    board[x][y] = HIT; // 更新板上的位置为HIT标记
    // 标记对角线位置为MISS，并更新hits数组
    // 标记对角线位置为MISS
    int dx[] = {-1, -1, 1, 1};
    int dy[] = {-1, 1, -1, 1};
    for (int i = 0; i < 4; ++i) {
      int newX = x + dx[i];
      int newY = y + dy[i];

      // 检查新位置是否在棋盘范围内，并且是空的
      if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE &&
          board[newX][newY] == EMPTY) {
        board[newX][newY] = MISS;
        hits[newX][newY] = true;
      }
    }
    return true;
  } else {
    board[x][y] = MISS; // Update the board with a MISS marker
    return false;
  }
}

bool Board::allShipsSunk() {
  for (int i = 0; i < BOARD_SIZE; ++i) {
    for (int j = 0; j < BOARD_SIZE; ++j) {
      if (board[i][j] == SHIP) {
        return false;
      }
    }
  }
  return true;
}

bool Board::isOccupied(int x, int y) { return board[x][y] != EMPTY; }

bool Board::isHit(int x, int y) { return hits[x][y]; }

void Board::displayRow(int row, bool showShips, int col) const {
  for (int j = 0; j < BOARD_SIZE; ++j) {
    if (!showShips && col == j){
      if (!hits[row][j]){
        cout << GREEN << '#' << ' ' << RESET_COLOR;
      }
      else{
        cout << RED_BG << '#' << RESET_COLOR << ' ';
      }
    }
    else if (showShips || hits[row][j]) {
      if (hits[row][j]) {
        if (board[row][j] == HIT) {
          cout << HIT_CELL << ' ';
        } else {
          cout << MISS_CELL << ' ';
        }
      } else if (board[row][j] == SHIP) {
        cout << SHIP_CELL << ' ';
      } else {
        cout << EMPTY_CELL << ' ';
      }
    } else {
      cout << EMPTY_CELL << ' ';
    }
  }
}

Point Board::getRandomPoint() {
  Point p;
  p.x = rand() % BOARD_SIZE;
  p.y = rand() % BOARD_SIZE;
  return p;
}

void Board::DisplayColorPlacement(int x, int y, int size, bool isVertical) {
  clearScreen();
  cout << "Place a ship of size " << CYAN << BOLD << size << RESET_COLOR << endl << endl;
  cout << "Please use " << ITALIC << UNDERLINE << "wasd " << RESET_COLOR << "or "
       << ITALIC << UNDERLINE << "arrow keys" << RESET_COLOR 
       << " to move your ship, \nOr press the "
       << BOLD << UNDERLINE << BLINKING << "[  spacebar  ]" << RESET_COLOR
       << " to change its orientation. \nNote: upperleft corner will be "
          "fixed during rotation."
       << endl << endl;
  cout << "When the ship is" << RED << " red" << RESET_COLOR
       << ", it is an invalid placement." << endl;
  cout << "When it is " << BOLD << GREEN << "green" << RESET_COLOR
       << ", it is valid!" << endl;
  cout << "Press the " << BOLD << CYAN << "Enter" << RESET_COLOR
       << " key to place this ship." << endl << endl;

  cout << "  0 1 2 3 4 5 6 7 8 9\n";
  bool isValid = isValidPlacement(x, y, size, isVertical);
  for (int i = 0; i < BOARD_SIZE; ++i) {
    cout << char('A' + i) << ' ';
    for (int j = 0; j < BOARD_SIZE; ++j) {
      if (isVertical) { // when the ship is vertical:
        if (x <= i && i < x + size &&
            y == j) { // check if the ij-th block is under the ship to be placed
          if (j < BOARD_SIZE - 1) { // if the block is not at the rightmost end,
                                    // add a space after it
            if (!(isValid)) {
              cout << RED << SHIP << ' ' << RESET_COLOR;
            } else {
              cout << GREEN << SHIP << ' ' << RESET_COLOR;
            }
          } else {
            if (!(isValid)) { // at the rightmost end -> no space added
              cout << RED << SHIP << RESET_COLOR;
            } else {
              cout << GREEN << SHIP << RESET_COLOR;
            }
          }
        } else {
          if (j < BOARD_SIZE - 1)
            cout << board[i][j] << ' ';
          else {
            cout << board[i][j];
          }
        }
      } else {
        if (y <= j && j < y + size && x == i) {
          if (j < BOARD_SIZE - 1) {
            if (!(isValid)) {
              cout << RED << SHIP << ' ' << RESET_COLOR;
            } else {
              cout << GREEN << SHIP << ' ' << RESET_COLOR;
            }
          } else {
            if (!(isValid)) {
              cout << RED << SHIP << RESET_COLOR;
            } else {
              cout << GREEN << SHIP << RESET_COLOR;
            }
          }
        } else {
          if (j < BOARD_SIZE - 1)
            cout << board[i][j] << ' ';
          else {
            cout << board[i][j];
          }
        }
      }
    }
    cout << endl;
  }
}