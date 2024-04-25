#ifndef SHIP_H
#define SHIP_H

#include "battleship/point.h"
#include <vector>
class Ship {
public:
  // Number of cells occupied
  bool isVertical; // True if the ship is vertical
  int size;
  int hits;                 // Number of hits taken
  std::vector<Point> cells; // Cells occupied by the ship

  Ship(int s) : isVertical(false), size(s), hits(0){};
  ~Ship(){};

  /**
   * @brief Check if the ship is sunk
   */
  bool isSunk() { return hits == size; }

  /**
   * @brief Add a cell to the ship
   */
  bool isHit(Point p) {
    for (Point &cell : cells) {
      if (cell == p) {
        hits++;
        return true;
      }
    }
    return false;
  }

  /**
   * @brief Add a cell to the ship
   */
  bool addCell(Point p) {
    if ((int)cells.size() < size) {
      cells.push_back(p);
      return true;
    }
    return false;
  }

  /**
   * @brief Get the cells occupied by the ship
   */
  std::vector<Point> getCells() { return cells; }
};

#endif // SHIP_H