#include "battleship/action.h"
#include "battleship/board.h"
#include "battleship/point.h"
#include "common/serialization.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  // 测试 Point 类的序列化和反序列化
  Point point(1, 2);
  string serializedPoint = serializePoint(point);
  cout << "Serialized point: " << serializedPoint << endl;
  Point deserializedPoint = deserializePoint(serializedPoint);
  cout << "Deserialized point: " << deserializedPoint.x << ","
       << deserializedPoint.y << endl;

  // 测试 Ship 类的序列化和反序列化
  Ship ship(3);
  ship.addCell(Point(1, 2));
  ship.addCell(Point(3, 4));
  ship.addCell(Point(5, 6));
  string serializedShip = serializeShip(ship);
  cout << "Serialized ship: " << serializedShip << endl;
  Ship deserializedShip = deserializeShip(serializedShip);
  cout << "Deserialized ship: " << deserializedShip.size << ","
       << deserializedShip.hits << "," << deserializedShip.isVertical << ","
       << deserializedShip.cells.size();
  for (const auto &cell : deserializedShip.cells) {
    cout << ";" << cell.x << "," << cell.y;
  }
  cout << endl;

  // 测试 Board 类的序列化和反序列化
  Board board;
  Ship ship1(3);
  ship1.addCell(Point(1, 2));
  ship1.addCell(Point(1, 3));
  ship1.addCell(Point(1, 4));
  board.placeShip(ship1);
  Ship ship2(2);
  ship2.addCell(Point(3, 4));
  ship2.addCell(Point(4, 4));
  board.placeShip(ship2);
  // 如果反序列化的Board和原Board相同，说明序列化和反序列化正确
  string serializedBoard = serializeBoard(board);
  cout << "Serialized board: " << serializedBoard << endl;
  Board deserializedBoard = deserializeBoard(serializedBoard);
  cout << "Deserialized board: " << endl;
  cout << "Original board:" << endl;
  board.display(true);
  cout << "Deserialized board:" << endl;
  deserializedBoard.display(true);

  // 测试 Action 类的初始化
  Action action(INIT, serializeBoard(board));
  cout << "Action type: " << action.type << endl;
  cout << "Action data: " << action.data << endl;
}
