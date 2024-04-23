#include "client/client_game.h"
#include "battleship/game.h"
#include "battleship/color.h"
#include <iostream>
#include <limits>

using namespace std;

int main(int argc, char *argv[])
{
  cout << YELLOW << "Welcome to BattleShip Game!" << RESET_COLOR << endl;

  cout << "> Computer" << endl;
  cout << "> Online" << endl;
  cout << "Enter your choice: ";

  int choice;
  cin >> choice;
  while (choice != 0 && choice != 1)
  {
    cout << "Wrong Input, Please Enter 0 or 1..." << endl;
    cout << "Enter your choice: ";
    cin >> choice;
  }

  if (choice == 0)
  {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Add this line
    Game battleshipGame = Game();
    battleshipGame.start();
  }
  else if (choice == 1)
  {
    string DEFAULT_IP = "43.143.114.119";

    // 匹配成功
    ClientGame battleshipGame = ClientGame(DEFAULT_IP);
    battleshipGame.start();

    cout << "Closing Game...\n";
    battleshipGame.stop();
  }

  return 0;
}