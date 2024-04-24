#include "battleship/game.h"
#include "battleship/action.h"
#include "battleship/color.h"
#include "battleship/constants.h"
#include "battleship/utilities.h"
#include <ios>
#include <iostream>
#include <limits>
#include <regex>
#include <unistd.h>

using namespace std;

void Game::placeShips(Board &board, bool isPlayer) {
  for (int shipSize : SHIPS) {

    if (isPlayer) {
      gameLogic.placeShips(board, shipSize);
    } else {
      while (true) {
        Point p = board.getRandomPoint();
        bool isVertical = rand() % 2 == 0;
        if (board.isValidPlacement(p.x, p.y, shipSize, isVertical)) {
          board.placeShip(p.x, p.y, shipSize, isVertical);
          break;
        }
      }
    }
  }
}

void Game::playerMove() {
  int x = -1;
  int y = -1;
  gameLogic.getMoveFromPlayer(playerBoard, computerBoard, x, y);

  if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
    if (computerBoard.checkHit(x, y)) {
      cout << "Hit!\n";
    } else {
      cout << "Miss!\n";
    }
  } else {
    cout << RED << "Invalid coordinates!\n" << RESET_COLOR;
  }
}

void Game::computerMove() {
  while (true) {
    Point p = playerBoard.getRandomPoint();
    if (!playerBoard.isOccupied(p.x, p.y)) {
      if (playerBoard.checkHit(p.x, p.y)) {
        cout << "Computer's turn: Hit at " << char('A' + p.x) << p.y + 1
             << endl;
      } else {
        cout << "Computer's turn: Miss at " << char('A' + p.x) << p.y + 1
             << endl;
      }
      break;
    }
  }
}

Game::Game() : playerTurn(true) {
  srand(time(0));
  clearScreen();
  placeShips(playerBoard, true);
  placeShips(computerBoard, false);
  clearScreen();
}

Game::~Game() {}

void Game::start() {
  while (true) {
    if (playerTurn) {
      playerMove();
      if (computerBoard.allShipsSunk()) {
        displayBoardsSideBySide(playerBoard, computerBoard, true, true);
        cout << YELLOW << "Congratulations! You win!\n" << RESET_COLOR;
        break;
      }
    } else {
      computerMove();
      if (playerBoard.allShipsSunk()) {
        displayBoardsSideBySide(playerBoard, computerBoard, true, true);
        cout << RED << "Sorry, computer wins!\n" << RESET_COLOR;
        break;
      }
    }
    playerTurn = !playerTurn;
  }
}