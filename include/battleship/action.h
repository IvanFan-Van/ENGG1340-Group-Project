#ifndef ACTION_H
#define ACTION_H

#include "battleship/board.h"
#include "common/constants.h"
#include <cstring>
#include <string>
// TODO
#include <iostream>

using namespace std;

enum ActionType { SHOOT, INIT, CHECK_WIN, START, GET_GAME_STATUS, DEFAULT };
struct Action {
  ActionType type;
  char data[1024];

  Action(ActionType t, const std::string &d) : type(t) {
    // cout << "接收到的用于初始化Action的字符串：" << d << endl;
    strcpy(data, d.c_str());

    // cout << "初始化Action的data：" << data << endl;
  }
  Action(ActionType t) : type(t) { memset(data, 0, sizeof(data)); }
  // 默认构造函数
  Action() : type(DEFAULT) { memset(data, 0, sizeof(data)); }
};

#endif // ACTION_H