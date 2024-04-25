#ifndef POINT_H
#define POINT_H

struct Point {
  int x;
  int y;

  bool operator==(const Point &p) const { return x == p.x && y == p.y; }
  // 拷贝赋值操作符
  Point &operator=(const Point &other) {
    if (this != &other) { // 防止自赋值
      x = other.x;
      y = other.y;
    }
    return *this;
  }

  Point(int x, int y) : x(x), y(y) {}
  Point() : x(-1), y(-1) {}
};

#endif // POINT_H