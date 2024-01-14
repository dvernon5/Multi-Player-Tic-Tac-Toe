#include <iostream>
#include "Game.h"
/*
 * ---------------------------------------------------------------------
 * CONSTRUCTOR NAME: GAME
 * ---------------------------------------------------------------------
 * @brief Constructs a game board for Tic-Tac-Toe.
 *
 * This constructor initializes a 3X3 game board for Tic-Tac-Toe.
 * Where each cell is initially marked with an asterisk (*).
 *
 * @details The game board is represented as a 2D array of cells.
 * The initial state of the board is:
 *   | * | * | * |
 *   | * | * | * |
 *   | * | * | * |
 *
 * @note This constructor sets up the initial state of the game board.
 * The players can make moves on this board to play Tic-Tac-Toe.
 * ---------------------------------------------------------------------
 */
Game::Game() {
  for (size_t row = 0; row < BOARD_SIZE; ++row) {
    for (size_t column = 0; column < BOARD_SIZE; ++column) {
      game_board[row][column] = '*';
    }
  }
}

std::string Game::DisplayGameBoard() {
  std::string result;
  for (size_t row = 0; row < BOARD_SIZE; ++row) {
    for (size_t column = 0; column < BOARD_SIZE; ++column) {
      result += game_board[row][column];
    }
    result += '\n';
  }
  
  return result;
}

bool Game::IsMoveValid(const int row, const int column) {
  return game_board[row - 1][column - 1] == '*';
}

void Game::InsertMove(const int row, const int column, const char letter) {
  game_board[row - 1][column - 1] = letter;
}

bool Game::IsWinner(const char letter) {
  char winner = '*';
  
  /* Checking for Winner Across. */
  for (size_t row = 0; row < BOARD_SIZE; ++row) {
    if (game_board[row][0] == game_board[row][1] &&
        game_board[row][1] == game_board[row][2] &&
        game_board[row][0] != '*') {
      winner = game_board[row][0];
      break;
    }
  }
  
  /* Checking for Winner Vertically. */
  for (size_t column = 0; column < BOARD_SIZE; ++column) {
    if (game_board[0][column] == game_board[1][column] &&
        game_board[1][column] == game_board[2][column] &&
        game_board[0][column] != '*') {
      winner = game_board[0][column];
    }
  }
  
  /* Checking for winner left to right diagonal. */
  /* Checking for winner right to left diagonal. */
  if ((game_board[0][0] == game_board[1][1] &&
      game_board[1][1] == game_board[2][2] &&
      game_board[0][0] != '*') ||
      (game_board[0][2] == game_board[1][1] &&
       game_board[1][1] == game_board[2][0] &&
       game_board[0][2] != '*')) {
    winner = game_board[1][1];
  }

  if (winner != '*') {
    return letter == winner;
  }
  
  return false;  /* No winner has been declared. */
}
