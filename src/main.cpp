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

#define KEY_UP 65
#define KEY_DOWN 66
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

  cout << "\r\033[K"; // 清空当前行

  std::cout << "[";
  int pos = static_cast<int>(barWidth * progress);
  for (int i = 0; i < barWidth; ++i) {
    if (i < pos)
      std::cout << "=";
    else if (i == pos)
      std::cout << ">";
    else
      std::cout << " ";
  }
  std::cout << "] " << int(progress * 100.0) << " %" << std::flush;
}

/**
 * @brief 显示游戏的Logo
 */
void displayLogo() {
  const string art = R"(
        ____  ___  ______________    ___________ __  __________ 
       / __ )/   |/_  __/_  __/ /   / ____/ ___// / / /  _/ __ \
      / __  / /| | / /   / / / /   / __/  \__ \/ /_/ // // /_/ /
     / /_/ / ___ |/ /   / / / /___/ /___ ___/ / __  // // ____/ 
    /_____/_/  |_/_/   /_/ /_____/_____//____/_/ /_/___/_/      
                                                              
      )";

  // Split the art into lines
  std::istringstream iss(art);
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(iss, line)) {
    lines.push_back(line);
  }

  // Find the maximum line length to use for padding
  size_t max_length = 0;
  for (const auto &line : lines) {
    if (line.length() > max_length) {
      max_length = line.length();
    }
  }

  for (size_t col = 0; col <= max_length; ++col) {
    for (const auto &line : lines) {
      std::cout << line.substr(0, col) << std::endl;
    }

    // Print the progress bar at the bottom.
    printProgressBar(col, max_length);

    // Delay for demonstration purposes.
    std::this_thread::sleep_for(std::chrono::milliseconds(25));

    // Move the cursor back to the top.
    std::cout << "\033[" << lines.size() << "A";
  }
  // After the final iteration, move the cursor below the art and progress bar
  std::cout << "\033[" << lines.size() + 1 << "B" << std::endl;

  this_thread::sleep_for(
      chrono::milliseconds(500)); // Delay for demonstration purposes
}

/**
 * @brief 显示游戏菜单
 */
void displayMenu(bool isComputerSelected) {
  cout << "Select Game Mode:\n";
  cout << (isComputerSelected ? YELLOW + "=> Computer <=" + RESET_COLOR
                              : "  Computer  ")
       << endl;
  cout << (!isComputerSelected ? YELLOW + "=> Online <=" + RESET_COLOR
                               : "  Online  ")
       << endl;

  cout << "(Using the arrow keys to navigate, press Enter to select)\n";
  cout.flush();
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
  while (true) {
    char c;
    if (read(STDIN_FILENO, &c, 1) == -1) {
      perror("read");
      exit(1);
    }

    if (c == '\033') { // Arrow keys are preceded by an escape sequence \033[
      read(STDIN_FILENO, &c, 1); // Skip the [
      read(STDIN_FILENO, &c, 1);
      if (c == KEY_UP || c == KEY_DOWN) {
        isComputerSelected = !isComputerSelected; // Toggle the selection
      }
    } else if (c == ENTER_KEY) {
      break;
    }
    clearLinesAbove(4);
    displayMenu(isComputerSelected);
  }
}

int main(int argc, char *argv[]) {
  // Disable standard input buffering
  enableRawMode();
  // Display the logo
  displayLogo();
  // Default to computer mode
  bool isComputerSelected = true;
  // Display the menu
  displayMenu(isComputerSelected);
  // choose game mode
  chooseMode(isComputerSelected);
  // Restore terminal settings
  disableRawMode();

  // Start the game
  if (isComputerSelected) {
    cout << "Starting Game With Computer...\n";
    sleep(1); // Delay for demonstration purposes
    Game battleshipGame = Game();
    battleshipGame.start();
  } else {
    cout << "Starting Online Game...\n";
    sleep(1); // Delay for demonstration purposes
    // 匹配成功
    ClientGame battleshipGame = ClientGame(DEFAULT_IP);
    battleshipGame.start();
    cout << "Closing Game...\n";
    battleshipGame.stop();
  }

  return 0;
}