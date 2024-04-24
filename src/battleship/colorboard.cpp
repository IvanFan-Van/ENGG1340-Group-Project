// #include "battleship/board.h"
// #include "battleship/constants.h"
// #include "battleship/color.h"
// #include "battleship/keyboard.h"
// #include "common/utilities.h"
// #include <iostream>

// using namespace std;

// // void Board::DisplayColorPlacement(int x, int y, int size, bool
// isVertical){
// //     clearScreen();
// //     cout << "Place a ship of size "<< size << endl;
// //     cout << "Please use \"wasd\" or arrow keys to move your ship, \nOr
// press the spacebar to change its orientation. Note: upperleft corner will be
// fixed during rotation."<< endl;
// //     cout << "When the ship is green, it is a valid placement!" << endl;
// //     cout << "Press the Enter key to place this ship."<< endl;

// //     cout << "  0 1 2 3 4 5 6 7 8 9\n";
// //     bool isValid = isValidPlacement(x, y, size, isVertical);
// //     for (int i = 0; i < BOARD_SIZE; ++i)
// //     {
// //         cout << char('A' + i) << ' ';
// //         for (int j = 0; j < BOARD_SIZE; ++j)
// //         {
// //             if (isVertical){ //when the ship is vertical:
// //                 if (x <= i && i < x + size && y == j){ //check if the
// ij-th block is under the ship to be placed
// //                     if (j < BOARD_SIZE - 1){//if the block is not at the
// rightmost end, add a space after it
// //                         if (!(isValid)){
// //                             cout << RED << SHIP << ' ' << RESET_COLOR;
// //                         }
// //                         else{
// //                             cout << GREEN << SHIP << ' ' << RESET_COLOR;
// //                         }
// //                     }
// //                     else{
// //                         if (!(isValid)){ //at the rightmost end -> no
// space added
// //                             cout << RED << SHIP << RESET_COLOR;
// //                         }
// //                         else{
// //                             cout << GREEN << SHIP << RESET_COLOR;
// //                         }
// //                     }
// //                 }
// //                 else{
// //                     if (j < BOARD_SIZE - 1)
// //                         cout << board[i][j] << ' ';
// //                     else {
// //                         cout << board[i][j];
// //                     }
// //                 }
// //             }
// //             else{
// //                 if (y <= j && j < y + size && x == i){
// //                     if (j < BOARD_SIZE - 1){
// //                         if (!(isValid)){
// //                             cout << RED << SHIP << ' ' << RESET_COLOR;
// //                         }
// //                         else{
// //                             cout << GREEN << SHIP << ' ' << RESET_COLOR;
// //                         }
// //                     }
// //                     else{
// //                         if (!(isValid)){
// //                             cout << RED << SHIP << RESET_COLOR;
// //                         }
// //                         else{
// //                             cout << GREEN << SHIP << RESET_COLOR;
// //                         }
// //                     }
// //                 }
// //                 else{
// //                     if (j < BOARD_SIZE - 1)
// //                         cout << board[i][j] << ' ';
// //                     else {
// //                         cout << board[i][j];
// //                     }
// //                 }
// //             }
// //         }
// //         cout << endl;
// //     }
// // }

// // bool Board::withinBoard(int x, int y, int size, bool isVertical){
// //     if (x < 1 || y < 1){
// //         return false;
// //     }
// //     if (isVertical)
// //     {
// //         if (x + size > BOARD_SIZE || y + 1 > BOARD_SIZE)
// //             return false;
// //     }
// //     else{
// //         if (y + size > BOARD_SIZE || x + 1 > BOARD_SIZE)
// //             return false;
// //     }
// //     return true;
// // }

// // bool Board::isValidPlacement(int x, int y, int size, bool isVertical)
// // {
// //     // check whether there is overlapping with existing ships
// //     if (isVertical)
// //     {
// //         for (int i = x; i < x + size; ++i)
// //         {
// //             if (i >= 0 && i < BOARD_SIZE && y >= 0 && y < BOARD_SIZE &&
// board[i][y] != EMPTY)
// //                 return false;

// //         }
// //     }
// //     else
// //     {
// //         for (int j = y; j < y + size; ++j)
// //         {
// //             if (x >= 0 && x < BOARD_SIZE && j >= 0 && j < BOARD_SIZE &&
// board[x][j] != EMPTY)
// //                 return false;
// //         }

// //     }
// //     return true;
// // }

// bool Board::allShipsPlaced()
// {
//     for (int i = 0; i < BOARD_SIZE; ++i)
//     {
//         for (int j = 0; j < BOARD_SIZE; ++j)
//         {
//             if (board[i][j] == SHIP)
//             {
//                 return true;
//             }
//         }
//     }
//     return false;
// }

// void Board::placeShip(int x, int y, int size, bool isVertical)
// {
//     if (isVertical)
//     {
//         for (int i = x; i < x + size; ++i)
//         {
//             board[i][y] = SHIP;
//         }
//     }
//     else
//     {
//         for (int i = y; i < y + size; ++i)
//         {
//             board[x][i] = SHIP;
//         }
//     }
// }

// bool Board::checkHit(int x, int y)
// {
//     if (hits[x][y])
//     {
//         // If the position was already hit before, we don't need to change
//         anything
//         // Consider providing feedback that the position was already
//         targeted. return false;
//     }
//     hits[x][y] = true; // Record the hit attempt regardless of whether it's a
//     hit or miss if (board[x][y] == SHIP)
//     {
//         board[x][y] = HIT; // 更新板上的位置为HIT标记
//         // 标记对角线位置为MISS，并更新hits数组
//         // 标记对角线位置为MISS
//         int dx[] = {-1, -1, 1, 1};
//         int dy[] = {-1, 1, -1, 1};
//         for (int i = 0; i < 4; ++i)
//         {
//             int newX = x + dx[i];
//             int newY = y + dy[i];

//             // 检查新位置是否在棋盘范围内，并且是空的
//             if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY <
//             BOARD_SIZE && board[newX][newY] == EMPTY)
//             {
//                 board[newX][newY] = MISS;
//                 hits[newX][newY] = true;
//             }
//         }
//         return true;
//     }
//     else
//     {
//         board[x][y] = MISS; // Update the board with a MISS marker
//         return false;
//     }
// }

// bool Board::allShipsSunk()
// {
//     for (int i = 0; i < BOARD_SIZE; ++i)
//     {
//         for (int j = 0; j < BOARD_SIZE; ++j)
//         {
//             if (board[i][j] == SHIP)
//             {
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// bool Board::isOccupied(int x, int y)
// {
//     return board[x][y] != EMPTY;
// }

// bool Board::isHit(int x, int y)
// {
//     return hits[x][y];
// }

// void Board::displayRow(int row, bool showShips) const
// {
//     for (int j = 0; j < BOARD_SIZE; ++j)
//     {
//         if (showShips || hits[row][j])
//         {
//             cout << (hits[row][j] ? (board[row][j] == HIT ? HIT : MISS) :
//             (board[row][j] == SHIP ? SHIP : EMPTY)) << ' ';
//         }
//         else
//         {
//             cout << EMPTY << ' ';
//         }
//     }
// }

// Point Board::getRandomPoint()
// {
//     Point p;
//     p.x = rand() % BOARD_SIZE;
//     p.y = rand() % BOARD_SIZE;
//     return p;
// }