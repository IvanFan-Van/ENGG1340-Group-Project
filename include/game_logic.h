#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <iostream>
#include <regex>
#include "battleship/color.h"
#include "battleship/utilities.h"
#include "battleship/constants.h"
#include "battleship/board.h"
#include "battleship/keyboard.h"

using namespace std;

class GameLogic
{
public:
  // void placeShips(Board &board, int shipSize)
  // {
  //   while (true)
  //   {
  //     board.display(true);
  //     cout << "Place ship of size " << shipSize << endl;
  //     cout << "Enter coordinates (e.g., A1) and orientation (0 for horizontal, 1 for vertical): ";
  //     string input;
  //     getline(cin, input);

  //     // Regular expression to match the input format
  //     regex pattern("[A-J][0-9] [01]");

  //     if (!regex_match(input, pattern))
  //     {
  //       cout << RED << "Invalid input! Try again.\n\n"
  //            << RESET_COLOR;
  //       continue;
  //     }

  //     // Parse the input
  //     char row = input[0];
  //     int col = input[1] - '0';
  //     int orientation = input[3] - '0';

  //     int x = row - 'A';
  //     int y = col;
  //     if (board.isValidPlacement(x, y, shipSize, orientation == 1))
  //     {
  //       board.placeShip(x, y, shipSize, orientation == 1);
  //       break;
  //     }
  //     else
  //     {
  //       cout << RED << "Invalid placement! Try again.\n"
  //            << RESET_COLOR;
  //     }
  //   }
  // }

  void placeShips(Board &board, int shipSize)
  {
    char key;
    bool placed = false;
    int i = STARTPOINT, j = STARTPOINT;
    bool isVertical = true;
    board.DisplayColorPlacement(i, j, shipSize, isVertical);
    while (!placed){
      key = keyboard();
      switch (key){
          case 'w':
              if (i > 0){
                  i -= 1;
                  board.DisplayColorPlacement(i, j, shipSize, isVertical);
              }
              break;
          case 'a':
              if (j > 0){
                  j -= 1;
                  board.DisplayColorPlacement(i, j, shipSize, isVertical);
              }
              break;
          case 's':
              if (i < BOARD_SIZE - shipSize){
                  i += 1;
                  board.DisplayColorPlacement(i, j, shipSize, isVertical);
              }
              break;
          case 'd':
              if (j < BOARD_SIZE - shipSize){
                  j += 1;
                  board.DisplayColorPlacement(i, j, shipSize, isVertical);
              }
              break;
          case 'C':
              if ((isVertical?j:i) + shipSize <= BOARD_SIZE){
                  isVertical = !isVertical;
                  board.DisplayColorPlacement(i, j, shipSize, isVertical);
              }
              break;
          case 'Y'://choice made
              if (board.isValidPlacement(i, j, shipSize, isVertical)){
                  placed = true;
                  board.placeShip(i, j, shipSize, isVertical);
              }
              break;
          case 'N'://加了个中途退出功能，此处待定
              placed = true;
              break;
      }
    }
  }

  void getMoveFromPlayer(Board playerBoard, Board opponentBoard, int &x, int &y)
  {
    displayBoardsSideBySide(playerBoard, opponentBoard, true);
    // 获取用户输入
    string input;
    // 解析用户输入
    char row;
    int col;
    while (true)
    {
      cout << "\nYour turn.\nEnter coordinates to fire: ";
      getline(cin, input);
      regex pattern("[A-J][0-9]");
      if (!regex_match(input, pattern))
      {
        cout << RED << "Invalid input! Try again.\n"
             << RESET_COLOR;
        continue;
      }
      row = input[0];
      col = input[1] - '0';
      x = row - 'A';
      y = col;
      if (opponentBoard.isHit(x, y))
      {
        cout << RED << "You've already fired at this location! Try again.\n"
             << RESET_COLOR;
      }
      else
      {
        break;
      }
    }
  }
};

#endif // GAME_LOGIC_H