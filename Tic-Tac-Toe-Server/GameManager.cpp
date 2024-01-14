#include "GameManager.h"
#include <iostream>

/* ------------------------------------------------------------------------------------
 * FUNCTION NAME: MakeMove
 * ------------------------------------------------------------------------------------
 * @brief Validates and processes a player's move in the Tic-Tac-Toe game.
 *
 * This function checks if the move is valid, updates the game board, and
 * determines the game status (win, tie, or ongoing).
 *
 * @param row The row index of the move.
 * @param column The column index of the move.
 * @param letter The player's symbol ('X' or 'O').
 * @param move_counter The current move count.
 * @return Status object containing game information (status code, game board, letter).
 * ------------------------------------------------------------------------------------
 */
Status GameManager::MakeMove(const int row, const int column, const char letter, int move_counter) {
  Status status;
  const int maximum_move = 9;  // Maximum move to make in a Tic-Tac-Toe game.
  if (game.IsMoveValid(row, column)) {
    game.InsertMove(row, column, letter);
    bool is_winner = game.IsWinner(letter);
    if (is_winner || move_counter == maximum_move) {
      if (!is_winner && move_counter == maximum_move) {
        // Tie Game
        status.status_code = "Gameover";
        status.game_board = game.DisplayGameBoard();
        status.letter = 'T';  // Letter T represent Tie Game.
      } else {
        // Winner is found.
        status.status_code = "Gameover";
        status.game_board = game.DisplayGameBoard();
        status.letter = letter;
      }
    } else {
      // No winner is found. Game continues.
      status.status_code = "Update";
      status.game_board = game.DisplayGameBoard();
      status.letter = letter;
    }
  } else {
    // Invalid move.
    status.status_code = "Error";
    status.game_board = game.DisplayGameBoard();
    status.letter = letter;
  }
  
  return status;
}
