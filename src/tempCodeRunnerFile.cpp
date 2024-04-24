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

class Board
{
private:
    char board[BOARD_SIZE][BOARD_SIZE];
    bool hits[BOARD_SIZE][BOARD_SIZE]; // For tracking hits on opponent's board
public:
    Board()
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

    void display(bool showShips)
    {
        cout << "  1 2 3 4 5 6 7 8 9 10\n";
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            cout << char('A' + i) << ' ';
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                // Show hits or misses accordingly
                if (hits[i][j])
                {
                    cout << (board[i][j] == HIT ? HIT : MISS) << ' '; // Show HIT or MISS based on the current board status
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

    bool isValidPlacement(int x, int y, int size, bool isVertical)
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

    void placeShip(int x, int y, int size, bool isVertical)
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

    bool checkHit(int x, int y)
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

    bool allShipsSunk()
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

    bool isOccupied(int x, int y)
    {
        return board[x][y] != EMPTY;
    }

    void displayRow(int row, bool showShips) const
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

    Point getRandomPoint()
    {
        Point p;
        p.x = rand() % BOARD_SIZE;
        p.y = rand() % BOARD_SIZE;
        return p;
    }
};

// New function to display both boards side by side
void displayBoardsSideBySide(const Board &playerBoard, const Board &computerBoard, bool showPlayerShips)
{
    cout << "  1 2 3 4 5 6 7 8 9 10     1 2 3 4 5 6 7 8 9 10\n";
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        // Display player's board row
        cout << char('A' + i) << ' ';
        playerBoard.displayRow(i, showPlayerShips);
        cout << "   "; // Space between boards

        // Display computer's board row
        cout << char('A' + i) << ' ';
        computerBoard.displayRow(i, false);
        cout << endl;
    }
}

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

    void playerMove()
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
    Game() : playerTurn(true)
    {
        srand(time(0));
        placeShips(playerBoard, true);
        placeShips(computerBoard, false);
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
};

int main()
{
    Game battleshipGame;
    battleshipGame.start();
    return 0;
}