class Board
{
private:
  char board[BOARD_SIZE][BOARD_SIZE]; 
  bool hits[BOARD_SIZE][BOARD_SIZE];  

public:
  Board(){
    for (int i = 0; i < BOARD_SIZE; i++)
    {
      for (int j = 0; j < BOARD_SIZE; j++)
      {
        board[i][j] = EMPTY;
        hits[i][j] = false;
      }
    }
  }

  void display(bool showShips){
    cout << "  1 2 3 4 5 6 7 8 9 10\n";
    for (int i = 0; i < BOARD_SIZE; i++)
    {
      cout << char('A' + i) << ' ';
      for (int j = 0; j < BOARD_SIZE; j++)
      {
        if (hits[i][j])
        {
          cout << (board[i][j] == HIT ? HIT : MISS) << ' ';
        }
        else if (showShips && board[i][j] == SHIP)
        {
          cout << SHIP << ' ';
        }
        else
        {
          cout << EMPTY << ' ';
        }
      }
      cout << endl;
    }
  }

  bool isValidPlacement(int x, int y, int size, bool isVertical)
  {
    if (isVertical)
    {
      if (x + size > BOARD_SIZE || y + 1 > BOARD_SIZE)
      {
        return false;
      }
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
      {
        return false;
      }
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

  void placeShip(int x, int y, int size, bool isVertical){
    if (isVertical)
    {
      for (int i = x; i < x+size; i++)
      {
        board[i][y] = SHIP;
      }
    }
    else
    {
      for (int i = y; i < y+size; i++)
      {
        board[x][i] = SHIP;
      }
    }
  }

  bool checkHit(int x, int y){
    if (hits[x][y])
    {
      return false;
    }
    hits[x][y] = true;
    if (board[x][y] = SHIP)
    {
      board[x][y] = HIT;
      int dx[] = {-1, -1, 1, 1};
      int dy[] = {-1, 1, -1, 1};
      for (int i = 0; i < 4; i++)
      {
        int newX = x + dx[i];
        int newY = y + dy[i];
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
      board[x][y] = MISS;
      return false;
    }
  }

  bool allShipsSunk(){
    for (int i = 0; i < BOARD_SIZE; i++)
    {
      for (int j = 0; j < BOARD_SIZE; j++)
      {
        if (board[i][j] == SHIP)
        {
          return false;
        }
      }
    }
    return true;
  }

  bool isOccupied(int x, int y){
    return board[x][y] != EMPTY;
  }

  void displayRow(int row, bool showShips) const
  {
    for (int j = 0; j < BOARD_SIZE; j++)
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
  
  Point getRandomPoint(){
    Point p;
    p.x = rand() % BOARD_SIZE;
    p.y = rand() % BOARD_SIZE;
    return p;
  }
};