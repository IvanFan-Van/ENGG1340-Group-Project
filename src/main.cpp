#include "battleship/color.h"
#include "battleship/game.h"
#include "client/client_game.h"
#include <chrono>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <thread>

using namespace std;
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
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Move the cursor back to the top.
    std::cout << "\033[" << lines.size() << "A";
  }

  // After the final iteration, move the cursor below the art and progress bar
  std::cout << "\033[" << lines.size() + 1 << "B" << std::endl;
}

/**
 * @brief 显示游戏菜单
 */
void displayMenu() {
  displayLogo();
  cout << YELLOW << "Welcome to BattleShip Game!" << RESET_COLOR << endl;

  cout << "> Computer" << endl;
  cout << "> Online" << endl;
  cout << "Enter your choice: ";
}

int main(int argc, char *argv[]) {
  displayMenu();

  string choice;
  cin >> choice;
  while (choice != "0" && choice != "1") {
    cout << "Wrong Input, Please Enter 0 or 1..." << endl;
    cout << "Enter your choice: ";
    cin >> choice;
  }

  cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Add this line
  if (choice == "0") {
    Game battleshipGame = Game();
    battleshipGame.start();
  } else if (choice == "1") {
    string DEFAULT_IP = "43.143.114.119";

    // 匹配成功
    ClientGame battleshipGame = ClientGame(DEFAULT_IP);
    battleshipGame.start();

    cout << "Closing Game...\n";
    battleshipGame.stop();
  }

  return 0;
}