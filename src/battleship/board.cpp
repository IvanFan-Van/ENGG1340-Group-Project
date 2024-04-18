#include "battleship/board.h"
#include "battleship/constants.h"
#include <iostream>

using namespace std;

Board::Board()
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            board[i][j] = EMPTY;
            hits[i][j] = false;
        }
    }
}

Board::Board(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            this->board[i][j] = board[i][j];
            hits[i][j] = false;
        }
    }
}

void Board::display(bool showShips)
{
    cout << "  0 1 2 3 4 5 6 7 8 9\n";
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        cout << char('A' + i) << ' ';
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            // Show hits or misses accordingly
            if (hits[i][j])
            {
                cout << ((board[i][j] == HIT || board[i][j] == SHIP) ? HIT : MISS) << ' '; // Show HIT or MISS based on the current board status
            }
            else if (showShips && board[i][j] == SHIP)
            {
                cout << SHIP << ' '; // Show ships if they are supposed to be shown
            }
            else
            {
                cout << EMPTY << ' '; // Show empty space otherwise
            }
        }
        cout << endl;
    }
}

bool Board::isValidPlacement(int x, int y, int size, bool isVertical)
{
    // 加入检查相邻格子的逻辑
    if (isVertical)
    {
        if (x + size > BOARD_SIZE || y + 1 > BOARD_SIZE)
            return false;
        for (int i = x - 1; i <= x + size; ++i)
        {
            for (int j = y - 1; j <= y + 1; ++j)
            {
                if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && board[i][j] != EMPTY)
                    return false;
            }
        }
    }
    else
    {
        if (y + size > BOARD_SIZE || x + 1 > BOARD_SIZE)
            return false;
        for (int i = x - 1; i <= x + 1; ++i)
        {
            for (int j = y - 1; j <= y + size; ++j)
            {
                if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && board[i][j] != EMPTY)
                    return false;
            }
        }
    }
    return true;
}

bool Board::allShipsPlaced()
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (board[i][j] == SHIP)
            {
                return true;
            }
        }
    }
    return false;
}

void Board::placeShip(int x, int y, int size, bool isVertical)
{
    if (isVertical)
    {
        for (int i = x; i < x + size; ++i)
        {
            board[i][y] = SHIP;
        }
    }
    else
    {
        for (int i = y; i < y + size; ++i)
        {
            board[x][i] = SHIP;
        }
    }
}

bool Board::checkHit(int x, int y)
{
    if (hits[x][y])
    {
        // If the position was already hit before, we don't need to change anything
        // Consider providing feedback that the position was already targeted.
        return false;
    }
    hits[x][y] = true; // Record the hit attempt regardless of whether it's a hit or miss
    if (board[x][y] == SHIP)
    {
        board[x][y] = HIT; // 更新板上的位置为HIT标记
        // 标记对角线位置为MISS，并更新hits数组
        // 标记对角线位置为MISS
        int dx[] = {-1, -1, 1, 1};
        int dy[] = {-1, 1, -1, 1};
        for (int i = 0; i < 4; ++i)
        {
            int newX = x + dx[i];
            int newY = y + dy[i];

            // 检查新位置是否在棋盘范围内，并且是空的
            if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE && board[newX][newY] == EMPTY)
            {
                board[newX][newY] = MISS;
                hits[newX][newY] = true;
            }
        }
        return true;
    }
    else
    {
        board[x][y] = MISS; // Update the board with a MISS marker
        return false;
    }
}

bool Board::allShipsSunk()
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (board[i][j] == SHIP)
            {
                return false;
            }
        }
    }
    return true;
}

bool Board::isOccupied(int x, int y)
{
    return board[x][y] != EMPTY;
}

bool Board::isHit(int x, int y)
{
    return hits[x][y];
}

void Board::displayRow(int row, bool showShips) const
{
    for (int j = 0; j < BOARD_SIZE; ++j)
    {
        if (showShips || hits[row][j])
        {
            cout << (hits[row][j] ? (board[row][j] == HIT ? HIT : MISS) : (board[row][j] == SHIP ? SHIP : EMPTY)) << ' ';
        }
        else
        {
            cout << EMPTY << ' ';
        }
    }
}

Point Board::getRandomPoint()
{
    Point p;
    p.x = rand() % BOARD_SIZE;
    p.y = rand() % BOARD_SIZE;
    return p;
}