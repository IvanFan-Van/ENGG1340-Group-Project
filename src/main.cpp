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
vector<string> options = {
    "Computer", "Online", "Continue", "Help", "Exit",
};
const int NUM_OPTIONS = options.size();

// 获取终端的宽度
int getTerminalWidth() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}

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
  int terminalWidth = getTerminalWidth();

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
  int terminalWidth = getTerminalWidth();
  for (size_t col = 0; col <= max_length; ++col) {
    for (const auto &line : lines) {
      printCentered(line.substr(0, col), terminalWidth);
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
void displayMenu(int selectedOption) {
  int terminalWidth = getTerminalWidth();

  std::string line1 = "Select Option:";
  std::string line4 =
      "(Using the arrow keys to navigate, press Enter to select)\n";

  for (size_t i = 0; i < options.size(); ++i) {
    string optionLine =
        (i == selectedOption ? YELLOW + "=> " + options[i] + " <=" + RESET_COLOR
                             : "   " + options[i] + "   ");
    int padding = (terminalWidth - strlen("=> Computer <=")) / 2;
    cout << string(padding, ' ') << optionLine << endl;
  }

  // Calculate padding and print the instruction line
  int padding4 = (terminalWidth - line4.length()) / 2;
  cout << string(padding4, ' ') << line4 << endl;

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
void chooseMode(int &selectedOption) {

  while (true) {
    char c;
    if (read(STDIN_FILENO, &c, 1) == -1) {
      perror("read");
      exit(1);
    }

    if (c == '\033') { // Arrow keys are preceded by an escape sequence \033[
      read(STDIN_FILENO, &c, 1); // Skip the [
      read(STDIN_FILENO, &c, 1);
      if (c == KEY_UP) {
        if (selectedOption > 0) {
          selectedOption--;
        } else {
          selectedOption = NUM_OPTIONS - 1;
        }
      }
    } else if (c == KEY_DOWN) {
      if (selectedOption < NUM_OPTIONS - 1) {
        selectedOption++;
      } else {
        selectedOption = 0;
      }
    } else if (c == ENTER_KEY) {
      break;
    } else if (c == 'w') {
      if (selectedOption > 0) {
        selectedOption--;
      } else {
        selectedOption = NUM_OPTIONS - 1;
      }
    } else if (c == 's') {
      if (selectedOption < NUM_OPTIONS - 1) {
        selectedOption++;
      } else {
        selectedOption = 0;
      }
    } else if (c == ENTER_KEY) {
      break;
    }
    clearLinesAbove(NUM_OPTIONS + 2);
    displayMenu(selectedOption);
  }
}

int start() {
  // Disable standard input buffering
  enableRawMode();
  // clear screen
  clearScreen();
  // Display the logo
  displayLogo();
  // Default to computer mode
  int selectedOption = 0;
  // Display the menu
  displayMenu(selectedOption);
  // choose game mode
  chooseMode(selectedOption);
  // Restore terminal settings
  disableRawMode();

  return selectedOption;
}

int main(int argc, char *argv[]) {
  while (true) {
    // Start the game
    int option = start();
    cout << "option: " << option << endl;
    switch (option) {
    case 0: {
      printCentered("Starting Game With Computer...", getTerminalWidth());
      sleep(1); // Delay for demonstration purposes
      Game offlineGame = Game();
      offlineGame.start();
      offlineGame.saveGame();

      break;
    }
    case 1: {
      printCentered("Starting Game With People...", getTerminalWidth());
      sleep(1); // Delay for demonstration purposes
      string DEFAULT_IP = "43.143.114.119";
      // 匹配成功
      ClientGame onlineGame = ClientGame(DEFAULT_IP);
      onlineGame.start();

      cout << "Closing Game...\n";
      onlineGame.stop();
      break;
    }
    case 2: {
      Game offlineGame = Game();
      string filePath;
      cout << "Please enter the file path to load the game from: (default "
              "is 'savegame.txt')"
           << endl;
      getline(cin, filePath);
      if (filePath.empty()) {
        filePath = "savegame.txt";
      }
      offlineGame.loadGame(filePath);

      break;
    }
    case 3: {
      cout << "展示文档";
      cout << "按任意键继续";
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      break;
    }
    case 4: {
      cout << "Thank You for Playing Battleship!\n";
      return 0;
    }
    default: {
      cout << "Invalid Option\n";
    }
    }

    sleep(1);
  }

  return 0;
}