#include "battleship/game.h"
#include "battleship/keyboard.h"
#include "common/action.h"
#include "common/color.h"
#include "common/constants.h"
#include "common/utilities.h"
#include <ios>
#include <iostream>
#include <limits>
#include <regex>
#include <unistd.h>
#include <fstream>
#include <sstream>


using namespace std;

void Game::placeShips(Board &board, bool isPlayer) {
  for (int shipSize : SHIPS) {
    // 创建一个船对象
    Ship ship(shipSize);
    if (isPlayer) {
      gameLogic.placeShips(board, ship);
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

void Game::loadGame(string filepath){
  ifstream fin;
  fin.open(filepath);
  string line;
  
  istringstream line_stream(line);
  for(int i = 0; i<BOARD_SIZE;++i){
    for(int j =0; j<BOARD_SIZE;++j){
      line_stream>>playerBoard.board[i][j];
    }
  }
  istringstream line_stream(line);
  for(int i = 0; i<BOARD_SIZE;++i){
    for(int j =0; j<BOARD_SIZE;++j){
      line_stream>>playerBoard.hits[i][j];
    }
  }
  fin.close();
  
}


void Game::saveGame(){
  ofstream fout;
  fout.open("Recorder.txt");
  for(int i = 0; i<BOARD_SIZE;++i){
    for(int j =0; j<BOARD_SIZE;++j){
      fout<<playerBoard.board[i][j]<<" ";
    }
  }
  fout<<"\n";
  for(int i = 0; i<BOARD_SIZE;++i){
    for(int j =0; j<BOARD_SIZE;++j){
      fout<<playerBoard.hits[i][j]<<" ";
    }
  }
  fout<<"\n";
  fout.close();
}

bool Game::playerMove() {
  int x = -1;
  int y = -1;
  if(!gameLogic.getMoveFromPlayer(playerBoard, computerBoard, x, y)){
    return false;
    
  }

  if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
    if (computerBoard.handleHit(x, y)) {
      cout << "Hit!\n";
    } else {
      cout << "Miss!\n";
    }
  } else {
    cout << RED << "Invalid coordinates!\n" << RESET_COLOR;
  }
  return true;
}

void Game::computerMove() {
  while (true) {
    Point p = playerBoard.getRandomPoint();
    if (!playerBoard.isHit(p.x, p.y)) {
      if (playerBoard.handleHit(p.x, p.y)) {
        cout << "Computer's turn: Hit at " << char('A' + p.x) << p.y
             << endl;
      } else {
        cout << "Computer's turn: Miss at " << char('A' + p.x) << p.y
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
      if(!playerMove()){
        break;
        
      }
      if (computerBoard.allShipsSunk()) {
        displayBoardsSideBySide(playerBoard, computerBoard, true, -1, -1, true);
        cout << YELLOW << "Congratulations! You win!\n" << RESET_COLOR;
        break;
      }
      

    } else {
      computerMove();
      if (playerBoard.allShipsSunk()) {
        displayBoardsSideBySide(playerBoard, computerBoard, true, -1, -1, true);
        cout << RED << "Sorry, computer wins!\n" << RESET_COLOR;
        break;
      }
    }
    playerTurn = !playerTurn;
  }
}