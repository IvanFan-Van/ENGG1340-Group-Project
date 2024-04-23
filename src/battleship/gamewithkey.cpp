#include "battleship/game.h"
#include "battleship/constants.h"
#include "battleship/utilities.h"
#include "battleship/action.h"
#include "battleship/color.h"
#include "battleship/keyboard.h"
#include <iostream>
#include <limits>
#include <ios>
#include <regex>
#include <unistd.h>

using namespace std;

void Game::keyplaceShips(Board &board, bool isPlayer)
{
    char key;
    bool placed;
    for (int shipSize : SHIPS){
        placed = false;
        int i = STARTPOINT - 1, j = STARTPOINT - 1;
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
                    if (i < BOARD_SIZE - 1){
                        i += 1;
                        board.DisplayColorPlacement(i, j, shipSize, isVertical);
                    }
                    break;
                case 'd':
                    if (j < BOARD_SIZE - 1){
                        j += 1;
                        board.DisplayColorPlacement(i, j, shipSize, isVertical);
                    }
                    break;
                case 'C':
                    if (i + shipSize <= BOARD_SIZE){
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
}




void Game::playerMove()
{
    displayBoardsSideBySide(playerBoard, computerBoard, true);
    // 获取用户输入
    string input;
    // 解析用户输入
    char row;
    int col;
    int x;
    int y;
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
        if (computerBoard.isHit(x, y))
        {
            cout << RED << "You've already fired at this location! Try again.\n"
                 << RESET_COLOR;
        }
        else
        {
            break;
        }
    }

    clearScreen();
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
        cout << RED << "Invalid coordinates!\n"
             << RESET_COLOR;
    }
}

void Game::computerMove()
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

Game::Game() : playerTurn(true)
{
    srand(time(0));
    clearScreen();
    placeShips(playerBoard, true);
    placeShips(computerBoard, false);
    clearScreen();
}

Game::~Game()
{
}

void Game::start()
{
    while (true)
    {
        if (playerTurn)
        {
            playerMove();
            if (computerBoard.allShipsSunk())
            {
                cout << "Congratulations! You win!\n";
                break;
            }
        }
        else
        {
            computerMove();
            if (playerBoard.allShipsSunk())
            {
                cout << "Sorry, computer wins!\n";
                break;
            }
        }
        playerTurn = !playerTurn;
    }
}