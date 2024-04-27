#include "battleship/game.h"
#include "client/client_game.h"
#include "common/color.h"
#include <chrono>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <vector>
// 引入 ncurses 库
#include <ncursesw/ncurses.h>
#include <ncursesw/panel.h>

// #define KEY_UP 65
// #define KEY_DOWN 66
#define ENTER_KEY 10

const string DEFAULT_IP = "43.143.114.119";
struct termios orig_termios;

using namespace std;

/**
 * @brief 禁用标准输入的缓冲区
 */
void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

/**
 * @brief 恢复标准输入的缓冲区
 */

void disableRawMode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); }

/**
 * @brief 打印进度条
 */
void printProgressBar(size_t current, size_t total) {
  // 进度条的宽度
  int barWidth = 70;

  // 计算进度百分比
  float progress = static_cast<float>(current) / total;

  int y_max, x_max;
  getmaxyx(stdscr, y_max, x_max); // 获取屏幕尺寸
  int y_pos = y_max / 3 + 6; // 假设Logo高度为5行，再往下一行开始打印进度条
  int x_pos = (x_max - barWidth) / 2; // 计算进度条的居中位置

  move(y_pos, x_pos); // 移动到进度条开始的位置
  clrtoeol();         // 清除当前行

  printw("[");
  int pos = static_cast<int>(barWidth * progress);
  for (int i = 0; i < barWidth; ++i) {
    if (i < pos)
      printw("=");
    else if (i == pos)
      printw(">");
    else
      printw(" ");
  }
  printw("] %d %%", int(progress * 100.0));
  printw("\n");
  refresh();
}

/**
 * @brief 显示游戏的Logo
 */
void displayLogo() {
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);

  const char *logo[] = {
      "    ____  ___  ______________    ___________ __  __________ ",
      "   / __ )/   |/_  __/_  __/ /   / ____/ ___// / / /  _/ __ \\",
      "  / __  / /| | / /   / / / /   / __/  \\__ \\/ /_/ // // /_/ /",
      " / /_/ / ___ |/ /   / / / /___/ /___ ___/ / __  // // ____/",
      "/_____/_/  |_/_/   /_/ /_____/_____//____/_/ /_/___/_/     ",
      ""};

  // 计算行数
  int num_lines = sizeof(logo) / sizeof(logo[0]);
  int y_max, x_max;
  getmaxyx(stdscr, y_max, x_max); // 获取屏幕尺寸

  // 启用蓝色和黑色颜色对
  attron(COLOR_PAIR(1));
  for (size_t i = 0; i < num_lines; ++i) {
    for (size_t j = 0; j < strlen(logo[i]); ++j) {
      int x_pos = (x_max - strlen(logo[i])) / 2 + j; // 计算每个字符的居中位置
      mvaddch((y_max - num_lines) / 3 + i, x_pos, logo[i][j]); // 逐字符打印
      refresh(); // 刷新屏幕以显示每个字符
      std::this_thread::sleep_for(std::chrono::milliseconds(8)); // 等待25ms
    }

    // Print the progress bar at the bottom.
    printProgressBar(i + 1, num_lines);

    // // Delay for demonstration purposes.
    // std::this_thread::sleep_for(std::chrono::milliseconds(25));

    // // Move the cursor back to the top.
    // // std::cout << "\033[" << lines.size() << "A";

    // refresh(); // 刷新屏幕
  }
  attroff(COLOR_PAIR(1));
  // After the final iteration, move the cursor below the art and progress bar
  // std::cout << "\033[" << lines.size() + 1 << "B" << std::endl;

  this_thread::sleep_for(
      chrono::milliseconds(500)); // Delay for demonstration purposes
}

/**
 * @brief 显示游戏菜单
 */
void displayMenu(bool isComputerSelected) {
  const string options[] = {"Computer", "Online"};
  int y_max, x_max;
  getmaxyx(stdscr, y_max, x_max); // 获取屏幕尺寸

  // Logo和进度条总共占用了8行，那么菜单从第9行开始
  int y_pos = y_max / 3 + 8; // Logo和进度条下方开始的纵坐标
  for (size_t i = 0; i < sizeof(options) / sizeof(options[0]); ++i) {
    std::string optionText = options[i];
    int optionLength = optionText.length();
    int x_pos = (x_max - optionLength) / 2; // 计算居中位置

    if (isComputerSelected == (i == 0)) {
      attron(A_REVERSE); // 反转颜色以突出显示选中项
    }

    mvprintw(y_pos + i * 2, x_pos, "%s",
             optionText.c_str()); // 居中打印每个选项

    if (isComputerSelected == (i == 0)) {
      attroff(A_REVERSE); // 关闭反转颜色
    }
  }
  refresh(); // 刷新屏幕以显示菜单
}

/**
 * @brief 清除屏幕上方的行数
 */
void clearLinesAbove(int numLines) {
  for (int i = 0; i < numLines; ++i) {
    // Move the cursor up
    std::cout << "\033[A";
    // Erase the line
    std::cout << "\033[K";
  }
}

/**
 * @brief 选择游戏模式
 */
void chooseMode(bool &isComputerSelected) {
  // Display the logo
  displayLogo();

  // Display the menu
  displayMenu(isComputerSelected);

  int ch;
  while ((ch = getch()) != ENTER_KEY) { // 循环直到按下ENTER键
    switch (ch) {
    case KEY_UP:
    case 'w': // 可选: 添加字母键支持
    case 'W':
      if (!isComputerSelected) { // 如果当前选中"Online"，切换到"Computer"
        isComputerSelected = true;
        displayMenu(isComputerSelected);
      }
      break;
    case KEY_DOWN:
    case 's': // 可选: 添加字母键支持
    case 'S':
      if (isComputerSelected) { // 如果当前选中"Computer"，切换到"Online"
        isComputerSelected = false;
        displayMenu(isComputerSelected);
      }
      break;
    default:
      break; // 忽略其他按键
    }
  }
}

int main(int argc, char *argv[]) {
  // 初始化 ncurses
  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  curs_set(0); // 隐藏光标

  // Default to computer mode
  bool isComputerSelected = true;

  // choose game mode
  chooseMode(isComputerSelected);

  // Start the game
  if (isComputerSelected) {
    // 打印信息
    printw("\nStarting Game With Computer...\n");
    refresh();
    sleep(1); // Delay for demonstration purposes
    // 结束 ncurses模式
    endwin();

    Game battleshipGame = Game();
    battleshipGame.start();
  } else {
    printw("\nStarting Online Game...\n");
    refresh();
    sleep(1); // Delay for demonstration purposes
    // 结束 ncurses模式
    endwin();
    // 匹配成功
    ClientGame battleshipGame = ClientGame(DEFAULT_IP);
    battleshipGame.start();
    battleshipGame.stop();
  }

  return 0;
}