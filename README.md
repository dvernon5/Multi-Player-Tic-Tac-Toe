# Tic-Tac-Toe Game

## Overview
This C++ Tic-Tac-Toe game implements a client-server architecture, allowing two players to engage in real-time gameplay. The server manages the game logic, while the client facilitates user interactions. The documentation covers both server-side and client-side components. 

## Server-Side Application
### GameManager Class  
The Game Manager class orchestrates the Tic-Tac-Toe game's server-side functionality.  

* **MakeMove Function:**
  * Validates and processes a player's move
  * Checks for move validity, updates the game board and determines the game status (win, tie, or ongoing).

## How to Play

1. **Compilation**: To compile the code, use a C++ compiler such as g++. Open a terminal and navigate to the directory containing the source code file ('tic_tac_toe.cpp'). Use the following command to compile the code:

```shell
  g++ -O2 -std=c++11 main.cpp -o tic_tac_toe -Wall
```
2. **Running** the Game: After compilation, you can run the game using the following command:

```shell
  ./tic_tac_toe
```
3. **Game Rules**: The game is played on a 3 x 3 grid. Players take turns placing their markers on the grid. The goal is to get three of their markers in a row, either horizontally, vertically, or diagonally, before the opponent does.
4. **Player input**: Players are prompted to enter the row and column numbers where they want to place their marker. Input is validated to ensure it's within valid range (1 to 3) and the chosen spot is not already occupied.
5. **Winning and Tying**: The game continues until a player wins or the board is completely filled (a tie). The game will display the winner's name or "TIE" if there's no winner.

## Code Structure

The code is structured as follows:

* displayGameBoard: Display the current state of the game board.
* player: Handles the input from players and places their markers on the board.
* checkIfWinnerLeftToRightDiagonal: These functions check if there's a winner based on rows, columns, and diagonals.
* checkIfWinner: Calls the above functions to determine if there's a winner or a tie.
* inputValidate: Validates user input to ensure it's within the specified range.

The main function initializes the game board, displays the initial board, and manages the player turns. It alternates between player X and player O, checking for a winner or a tie after each move. 
