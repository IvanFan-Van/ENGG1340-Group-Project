#include "battleship/game.h"
#include "battleship/constants.h"
#include "battleship/utilities.h"
#include "battleship/action.h"
#include "battleship/color.h"
#include <iostream>
#include <limits>
#include <ios>
#include <regex>
#include <unistd.h>

using namespace std;

void Game::placeShips(Board &board, bool isPlayer)
{
    for (int shipSize : SHIPS)
    {

        if (isPlayer)
        {
            gameLogic.placeShips(board, shipSize);
        }
        else
        {
            while (true)
            {
                Point p = board.getRandomPoint();
                bool isVertical = rand() % 2 == 0;
                if (board.isValidPlacement(p.x, p.y, shipSize, isVertical))
                {
                    board.placeShip(p.x, p.y, shipSize, isVertical);
                    break;
                }
            }
        }
    }
}

void Game::playerMove()
{
    // displayBoardsSideBySide(playerBoard, computerBoard, true);
    // // 获取用户输入
    // string input;
    // // 解析用户输入
    // char row;
    // int col;
    // int x;
    // int y;
    // while (true)
    // {
    //     cout << "\nYour turn.\nEnter coordinates to fire: ";
    //     getline(cin, input);
    //     regex pattern("[A-J][0-9]");
    //     if (!regex_match(input, pattern))
    //     {
    //         cout << RED << "Invalid input! Try again.\n"
    //              << RESET_COLOR;
    //         continue;
    //     }
    //     row = input[0];
    //     col = input[1] - '0';
    //     x = row - 'A';
    //     y = col;
    //     if (computerBoard.isHit(x, y))
    //     {
    //         cout << RED << "You've already fired at this location! Try again.\n"
    //              << RESET_COLOR;
    //     }
    //     else
    //     {
    //         break;
    //     }
    // }

    int x = -1;
    int y = -1;
    gameLogic.getMoveFromPlayer(playerBoard, computerBoard, x, y);

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
                cout << YELLOW << "Congratulations! You win!\n"
                     << RESET_COLOR;
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