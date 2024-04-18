#include "battleship/game.h"
#include "battleship/constants.h"
#include "battleship/utilities.h"
#include "battleship/action.h"
#include <iostream>

using namespace std;

void Game::placeShips(Board &board, bool isPlayer)
{
    for (int shipSize : SHIPS)
    {
        while (true)
        {
            if (isPlayer)
            {
                board.display(true);
                cout << "Place ship of size " << shipSize << endl;
                cout << "Enter coordinates (e.g., A1) and orientation (0 for horizontal, 1 for vertical): ";
                char col;
                int row, orientation;
                cin >> col >> row >> orientation;
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
    displayBoardsSideBySide(playerBoard, computerBoard, true);
    cout << "\nYour turn.\nEnter coordinates to fire: ";
    char col;
    int row;
    cin >> col >> row;
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
    placeShips(playerBoard, true);
    placeShips(computerBoard, false);
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