#include "battleship/game.h"
#include "client/client_game.h"
#include "common/color.h"
#include <chrono>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <sys/ioctl.h>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <vector>
#include <fstream>

#define KEY_UP 65
#define KEY_DOWN 66
#define ENTER_KEY 10

using namespace std;

struct termios orig_termios;

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
  // Progress bar width
  int barWidth = 70;

  // Calculate progress percentage
  float progress = static_cast<float>(current) / total;

  // Get terminal width
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int terminalWidth = w.ws_col;

  // Calculate padding
  int padding = (terminalWidth - barWidth) / 2;

  cout << "\r\033[K"; // Clear current line

  // Print padding
  std::cout << std::string(padding, ' ');

  // Print progress bar
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
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  std::istringstream artStream(art);
  std::vector<std::string> lines;
  std::string line;
  // 将LOGO分割成行
  while (std::getline(artStream, line)) {
    lines.push_back(line);
  }

  // Find the maximum line length to use for padding
  size_t max_length = 0;
  for (const auto &line : lines) {
    if (line.length() > max_length) {
      max_length = line.length();
    }
  }

  // 逐行打印LOGO
  int pos_x;
  // Get terminal width
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int terminalWidth = w.ws_col;

  for (size_t col = 0; col <= max_length; ++col) {
    for (const auto &line : lines) {
      // 计算光标位置
      pos_x = (terminalWidth - line.length()) / 2;
      // 移动光标
      std::cout << "\033[" << pos_x << "C";
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
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  std::string line1 = "Select Game Mode:";
  std::string line2 =
      (isComputerSelected ? YELLOW + "=> Computer <=" + RESET_COLOR
                          : "   Computer   ");
  std::string line3 =
      (!isComputerSelected ? YELLOW + "=> Online   <=" + RESET_COLOR
                           : "   Online   ");
  std::string line4 =
      "(Using the arrow keys to navigate, press Enter to select)\n";

  // Calculate padding and print each line
  int padding1 = (w.ws_col / 2 - line1.length() / 2);
  cout << "\033[" << padding1 << "C";
  cout << line1 << endl;

  int padding2 = (w.ws_col / 2 - strlen("=> Computer <=") / 2);
  cout << "\033[" << padding2 << "C";
  cout << line2 << endl;

  int padding3 = (w.ws_col / 2 - strlen("=>  Online  <=") / 2);
  cout << "\033[" << padding3 << "C";
  cout << line3 << endl;

  int padding4 = (w.ws_col / 2 - line4.length() / 2);
  cout << "\033[" << padding4 << "C";
  cout << line4 << endl;
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
    clearLinesAbove(5);
    displayMenu(isComputerSelected);
  }
}

bool start() {
  // Disable standard input buffering
  enableRawMode();
  // clear screen
  clearScreen();
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

  return isComputerSelected;
}

int main(int argc, char *argv[]) {
  while (true) {
    // Start the gameofstream fout;
    ifstream fin;//这里读取存档
    if (start()) {
      cout << "Starting Game With Computer...\n";
      sleep(1); // Delay for demonstration purposes
      Game battleshipGame = Game();
      ifstream fout;
      fout.open("record_game.txt");//open the file that will read the user's boards.
      battleshipGame.start();
      //这里存入存档
      for(int i =0; i<BOARD_SIZE; i++){
        for(int j =0; j<BOARD_SIZE; j++){
          fout<<
        }
      }
      

    } else {
      cout << "Starting Online Game...\n";
      sleep(1); // Delay for demonstration purposes
      string DEFAULT_IP = "43.143.114.119";
      // 匹配成功
      ClientGame battleshipGame = ClientGame(DEFAULT_IP);
      battleshipGame.start();

      cout << "Closing Game...\n";
      battleshipGame.stop();
    }
    sleep(1);
  }

  return 0;
}