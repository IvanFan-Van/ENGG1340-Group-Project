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
1.  Entering the game, content will pop up and the player needs to choose the game mode. Using the arrow keys to navigate the mode, press Enter to select.
2.  If you select Man-Machine mode, skip to Step 3. If the player battle mode is selected, both players need to enter the same room number (eg.1111) to enter the same room to play the battle game.
3.  Players should use the "WASD" or arrow keys on the keyboard to move your ships and press the [ spacebar ] to change ship's orientation.Finally press the Enter key to place these ships(Note: upperleft corner will be fixed during rotation.)
4.  After placing the ship, the game begins and the player enters coordinates in a "row column" format to select the location of the strike (e.g. "A5"). The game provides instructions and hints for each player's turn.