#include <iostream>
#include "client/ctcpclient.h"
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

  // 创建客户端对象
  CTcpClient client;
  if (!client.connect(ip, 3004))
  {
    cout << "connect failed\n";
    return 0;
  };

  // 获取匹配码

  cout << "Enter Match Code: ";
  string buffer;
  getline(cin, buffer);
  if (!client.send(buffer))
  {
    cout << "send failed\n";
    return 0;
  }

  // 等待匹配成功
  buffer.clear();
  if (!client.recv(buffer, 1024))
  {
    cout << "recv failed\n";
    return 0;
  }
  cout << buffer << endl;

  while (buffer != "Match Success")
  {
    buffer.clear();
    if (!client.recv(buffer, 1024))
    {
      cout << "recv failed\n";
      return 0;
    }

    if (buffer == "Match Success")
    {
      break;
    }
  }

  // 匹配成功
  ClientGame battleshipGame = ClientGame(client);
  battleshipGame.start();

  cout << "Closing connection...\n";
  // 4. close connection
  client.close();

  return 0;
}