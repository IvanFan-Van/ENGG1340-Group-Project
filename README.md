# ENGG1340-Group-Project
HKU ENGG1340 Group Project
Battleship Game!!!!!

This is a console-based implementation of the classic game Battleship, written in C++.  The game allows two players to compete against each other in a strategic naval battle.

Game Rules:
1.  Each player has a fleet of ships placed on a 10x10 grid.
2.  The ship consists of one aircraft carrier (4 units), two battleships (3 units), three cruisers (2 units), and four submarines (1 unit).
3.  Players take turns guessing the coordinates to target their opponent's ships.
4.  The grid is marked with hits ('X') and misses ('O') to keep track of the shots.
5.  When all cells of a ship are hit, it is considered sunk.
6.  The first player to sink all of their opponent's ships wins the game.

Installation:
1.  Use FileZilla(note that you need to open the HKU vpn) to copy the "main" file to the HKU server.
2.  Enter the command:"chmod 777 main". in the terminal to obtain the document permission.
3.  Enter the run instruction:"./main".You can start your fun game!

Feature!!!:
1.  The game has two modes, one is the man-machine mode, the other is the player online mode. The game allows players to play against each other remotely, which promotes fun and interactivity!!!
2.  Final exam is coming, in the annoying review time may wish to open our game with friends to a happy battle of wits and courage to relax!!!!

Controls:
1.  Entering the game, content will pop up and the player needs to choose the game mode. Using "WASD" or the arrow keys to navigate the mode, press Enter to select.
2.  If you select Man-Machine mode, skip to Step 3. If the player battle mode is selected, both players need to enter the same room number (eg.1111) to enter the same room to play the battle game.
3.  Players should use the "WASD" or arrow keys on the keyboard to move your ships and press the [ spacebar ] to change ship's orientation. Finally press the Enter key to place these ships(Note: upperleft corner will be fixed during rotation.)
4.  After placing the ship, the game begins and the player uses the "WASD" on the keyboard to select the location of the attack and the "ENTER" key to strike.

The list of features:
1. In the man-machine battle mode of our game, the computer side uses the generation of random game sets or events to randomly place ships and randomly bomb the map.
2. In the game code we use two 2-layer arrays, namely board[][] and hit[][], which can be used to store whether the square has a piece and whether it has been hit.
3. In the game code we use dynamic memory management, such as "main.cpp","ship.h","board.h", etc., which include <vector>.
4. In "Keyboard.cpp" we implemented the code to receive the player's positioning with the keyboard, and in "game.cpp" we wrote the code to quit the game midway and save the game to prevent the player from accidentally losing the game data during the game.
5. The game's code is divided into sections such as "board.cpp","game.cpp","keyboard.cpp", and client_game.cpp", which are then combined with its header file using a makefile to form a complete game.
6. The code of the game has some comments to explain the function of the code, so that people can see at a glance, the function is conducive to team cooperation, but also help others to understand the operation of the code.

Team Members:
1. 3036223426 Wang PuiYuk: board.cpp; board.h; README; constants.h 
2. 3036267692 Liu Mingyao: game.cpp; game.h; client_game.cpp; client_game.h; And some small change in game_logic.cpp
3. 3036128066 Shi Wenqing: Realize keyboard-monitored control and colored interface [keyboard.cpp; game_logic.cpp; some functions in board.cpp and utilities.cpp]; server_game.cpp 
4. 3036264547 Fan Xieyi: Implement game online version, fix and refactor team's bug and code. Complete the template framework for project
5. 3036253689 Xiao Jingzhe: Responsible for game UI, including start menu and animations. Combined offline game mode and online game mode. Responsible for video making. 