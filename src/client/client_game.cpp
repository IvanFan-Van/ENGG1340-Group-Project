#include "client/client_game.h"
#include "battleship/action.h"
#include "battleship/game.h"
#include "client/ctcpclient.h"
#include "common/constants.h"
#include "common/utilities.h"
#include <algorithm>
#include <iostream>
#include <regex>
#include <unistd.h>

using namespace std;

void ClientGame::init(Board &board) {
  for (int shipSize : SHIPS) {
    gameLogic.placeShips(board, shipSize);
  }

  // 发送初始化棋盘行为
  board.display(true);
  // cout << "size of Action: " << sizeof(Action) << endl;
  // 初始化棋盘
  Action initAction;
  initAction.type = INIT;
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      initAction.initData.board[i][j] = playerBoard.board[i][j];
    }
  }

  // cout << "size of initAction: " << sizeof(initAction) << endl;

  if (!client.send(&initAction, sizeof(initAction))) {
    cout << "Failed to send board to server\n";
    return;
  };
}

void ClientGame::getGameStatus() {
  Action action;
  action.type = GET_GAME_STATUS;
  action.getGameStatusData = {};
  if (!client.send(&action, sizeof(action))) {
    cout << "Failed to send get game status action to server\n";
    return;
  };

  Board playerBoard;
  if (!client.recv(&playerBoard, sizeof(playerBoard))) {
    cout << "Failed to receive player board from server\n";
    return;
  };
  this->playerBoard = playerBoard;

  Board opponentBoard;
  if (!client.recv(&opponentBoard, sizeof(opponentBoard))) {
    cout << "Failed to receive opponent board from server\n";
    return;
  };
  this->opponentBoard = opponentBoard;

  cout << "Successfully received game status from server\n";
}

void ClientGame::playerMove() {
  getGameStatus();

  Action action;
  action.type = SHOOT;
  int x = -1;
  int y = -1;
  gameLogic.getMoveFromPlayer(playerBoard, opponentBoard, x, y);

  action.shootData.x = x;
  action.shootData.y = y;

  if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {

    if (!client.send(&action, sizeof(action))) {
      cout << "Failed to send shoot action to server\n";
      return;
    };

    bool hit;
    if (!client.recv(&hit, sizeof(bool))) {
      cout << "Failed to receive hit status from server\n";
      return;
    };

    if (hit) {
      cout << "Hit!\n";
    } else {
      cout << "Miss!\n";
    }

    getGameStatus();
    displayBoardsSideBySide(playerBoard, opponentBoard, true, -1, -1);
    cout << "Waiting for the opponent to move...\n";
    checkWin();
  } else {
    cout << "Invalid coordinates!\n";
  }
}

ClientGame::ClientGame(string &ip) : gameStarted(false) {
  this->ip = ip;
  srand(time(0));
  this->playerBoard = Board();
  // 连接服务器
  // 创建客户端对象
  this->client = CTcpClient();
}

ClientGame::~ClientGame() {
  cout << "Game Exit...\n";
  client.close();
}

void ClientGame::checkWin() {
  Action action;
  action.type = CHECK_WIN;
  action.checkWinData = {};
  if (!client.send(&action, sizeof(action))) {
    cout << "Failed to send check win action to server\n";
    return;
  };

  string message;
  if (!client.recv(message, 1024)) {
    cout << "Failed to receive message from server\n";
    return;
  };
  handleMessage(message);
  return;
}

void ClientGame::checkStart() {
  Action action;
  action.type = START;
  action.startData = {};
  if (!client.send(&action, sizeof(action))) {
    cout << "Failed to send start action to server\n";
    return;
  };

  if (!client.recv(&gameStarted, sizeof(bool))) {
    cout << "Failed to receive game start status from server\n";
    return;
  };
}

void ClientGame::stop() { client.close(); }

string trim(const string &str) {
  const auto strBegin = str.find_first_not_of(" \t\r\n\0");
  if (strBegin == string::npos) {
    return "";
  }

  const auto strEnd = str.find_last_not_of(" \t\r\n\0");
  const auto strRange = strEnd - strBegin + 1;

  return str.substr(strBegin, strRange);
}

void ClientGame::handleLost() {
  getGameStatus();
  displayBoardsSideBySide(playerBoard, opponentBoard, true, -1, -1, true);
  cout << RED << "Sorry, You Lose\n" << RESET_COLOR;
  stop();
}

void ClientGame::handleMessage(const string &rawMessage) {
  string message = trim(rawMessage);

  // cout << "Received message: " << message << endl;

  // 打印16进制字符做检测
  // for (unsigned char c : message)
  // {
  //     cout << hex << static_cast<int>(c) << ' ';
  // }
  // cout << endl;

  // for (unsigned char c : "Your turn")
  // {
  //     cout << hex << static_cast<int>(c) << ' ';
  // }
  // cout << endl;
  if (message == "Your turn") {
    cout << "Your turn.\n";
    playerMove();
  } else if (message == "Opponent's turn") {
    cout << "Opponent's turn.\n";
  } else if (message == "You win") {
    cout << YELLOW << "Congratulations! You win!\n" << RESET_COLOR;
    stop();
  } else if (message == "You lose") {
    handleLost();
  }
}

void ClientGame::start() {
  if (!client.connect(ip, 3004)) {
    cout << "connect failed\n";
    stop();
  };

  // 获取匹配码
  cout << "Enter Match Code: ";
  string buffer;
  getline(cin, buffer);
  if (!client.send(buffer)) {
    cout << "send failed\n";
    stop();
  }

  // 等待匹配成功
  buffer.clear();
  if (!client.recv(buffer, 1024)) {
    cout << "recv failed\n";
    stop();
  }
  cout << buffer << endl;

  while (buffer != "Match Success") {
    buffer.clear();
    if (!client.recv(buffer, 1024)) {
      cout << "recv failed\n";
      stop();
    }

    if (buffer == "Match Success") {
      break;
    }
  }

  init(playerBoard);

  // 等待游戏开始
  if (!gameStarted) {
    cout << "Waiting for the other player to initialize the board...\n";
  }
  while (!gameStarted) {
    checkStart();
    sleep(1);
  }

  cout << "Game started!\n";

  while (true) {
    string message;
    if (!client.recv(message, 1024)) {
      cout << "Failed to receive message from server\n";
      break;
    };
    handleMessage(message);
  }
}