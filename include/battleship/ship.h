#ifndef SHIP_H
#define SHIP_H

class Ship {
private:
  // Number of cells occupied
  bool isVertical; // True if the ship is vertical
  int hits;        // Number of hits taken

public:
  int size;
  Ship(int s) : isVertical(false), size(s){};
  ~Ship(){};

  bool isSunk() { return hits == size; }
};

#endif // SHIP_H