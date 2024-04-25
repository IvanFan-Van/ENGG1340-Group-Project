#ifndef SERVERGAME_H
#define SERVERGAME_H

#include "battleship/action.h"
#include "battleship/board.h"
#include <string>
#include <unordered_map>

using namespace std;

class ServerGame {
private:
  unordered_map<int, Board> boards;
  int currentPlayer; // A flag indicating whether it is the player's turn.
  unordered_map<int, bool>
      playerTurns; // mapping from player fd to bool indicating whether it is
                   // the player's turn
  int player1;
  int player2;

  void handleInitAction(const Action &action, int client_fd);

  void handleStartAction(const Action &action, int fd);

  void handleShootAction(const Action &action, int client_fd);

  void handleCheckWinAction(const Action &action, int client_fd);

  void handleGetGameStatusAction(const Action &action, int client_fd);

public:
  /**
   * @brief Executes the player's move.
   *
   * This function is called when it is the player's turn to make a move.
   */
  void playerMove();

  void handlePlayerAction(const Action &action, size_t bytes, int fd);

  void updateBoard(int client_fd, Board board);

  /**
   * @brief Default constructor for the ServerGame class.
   */
  ServerGame();

  /**
   * @brief Constructor for online playing
   */
  ServerGame(int fd1, int fd2);

  ~ServerGame();

  /**
   * @brief Starts the game.
   *
   * This function starts the game by initializing the boards, placing the
   * ships, and executing the turns until the game is over.
   */
  void start();

  bool fullyInitialized();

  void notifyPlayerTurn(int client_fd);

  void switchTurn();
};

#endif // SERVERGAME_H