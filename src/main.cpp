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

void displayLogo() {
  const string art = R"(
      ____  ___  ______________    ___________ __  __________ 
     / __ )/   |/_  __/_  __/ /   / ____/ ___// / / /  _/ __ \
    / __  / /| | / /   / / / /   / __/  \__ \/ /_/ // // /_/ /
   / /_/ / ___ |/ /   / / / /___/ /___ ___/ / __  // // ____/ 
  /_____/_/  |_/_/   /_/ /_____/_____//____/_/ /_/___/_/      
                                                              
      )";

  // Split the art into lines
  istringstream iss(art);
  vector<string> lines;
  string line;
  while (getline(iss, line)) {
    lines.push_back(line);
  }

  // Find the maximum line length to use for padding
  size_t max_length = 0;
  for (const auto &line : lines) {
    if (line.length() > max_length) {
      max_length = line.length();
    }
  }

  // Loop through each column of characters
  for (size_t col = 0; col < max_length; ++col) {
    // Loop through each line
    for (const auto &line : lines) {
      // Print the substring that starts at index 0 and has length of col + 1
      // characters
      if (col < line.size()) {
        std::cout << line.substr(0, col + 1);
      }
      // Fill the rest of the line with spaces if needed
      else {
        std::cout << line;
      }
      // Move to the next line
      std::cout << std::endl;
    }
    // Wait for 50ms
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    // Move the cursor back to the beginning of the lines
    std::cout << "\033[" << lines.size() << "A";
  }

  // After the final iteration, move the cursor below the art
  std::cout << "\033[" << lines.size() << "B";
}

void displayMenu() {
  displayLogo();
  cout << YELLOW << "Welcome to BattleShip Game!" << RESET_COLOR << endl;

  cout << "> Computer" << endl;
  cout << "> Online" << endl;
  cout << "Enter your choice: ";
}

int main(int argc, char *argv[]) {
  displayMenu();

  int choice;
  cin >> choice;
  while (choice != 0 && choice != 1) {
    cout << "Wrong Input, Please Enter 0 or 1..." << endl;
    cout << "Enter your choice: ";
    cin >> choice;
  }

  cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Add this line
  if (choice == 0) {
    Game battleshipGame = Game();
    battleshipGame.start();
  } else if (choice == 1) {
    string DEFAULT_IP = "43.143.114.119";

    // 匹配成功
    ClientGame battleshipGame = ClientGame(DEFAULT_IP);
    battleshipGame.start();

    cout << "Closing Game...\n";
    battleshipGame.stop();
  }

  return 0;
}