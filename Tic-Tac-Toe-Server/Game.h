#ifndef Game_h
#define Game_h
#include <iostream>

/* ---------------------------------------------------------------------
 * CLASS NAME: Game
 * ---------------------------------------------------------------------
 * @brief Handles the gaming logic for a Tic-Tac-Toe game.
 *
 * The Game class provides functions for initializing the game board,
 * displaying the current state of the board, and determining the winner.
 * ---------------------------------------------------------------------
 *
 */
class Game {
  public:
    Game();
    std::string DisplayGameBoard();
    bool IsMoveValid(const int row, const int column);
    void InsertMove(const int row, const int column, const char letter);
    bool IsWinner(const char letter);
  
  private:
    const int BOARD_SIZE = 3;
    char game_board[3][3];
};
#endif /* Game_h */
