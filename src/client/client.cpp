#include <iostream>
#include "client/client_game.h"
#include <signal.h>

using namespace std;

int main(int argc, char *argv[])
{
  const string DEFAULT_IP = "43.143.114.119";
  if (argc > 2)
  {
    cout << "Usage: " << argv[0] << " <ip>\n";
    return 0;
  }
  string ip = argc == 2 ? argv[1] : DEFAULT_IP;

  // 匹配成功
  ClientGame battleshipGame = ClientGame(ip);
  battleshipGame.start();

  cout << "Closing Game...\n";
  battleshipGame.stop();

  return 0;
}