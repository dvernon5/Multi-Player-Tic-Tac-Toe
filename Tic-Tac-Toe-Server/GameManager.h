#ifndef GameManager_h
#define GameManager_h
#include "Game.h"
#include "Status.h"
#include "PromptingUser.h"

/* ----------------------------------------------------------------------------
 * CLASS NAME: GameManager
 * ----------------------------------------------------------------------------
 * @brief Controls the real-time flow of a Tic-Tac-Toe Game.
 *
 * The GameManager class offically updates the game board after checking
 * conditions to determine the validity of a move. Additionally, it updates the
 * statuses of the game including, status_code, game_board, and player_symbol
 *
 * @note To better understand the tasks of each variable, please refer to the
 *       documentation for the Status structure.
 * ----------------------------------------------------------------------------
 */
class GameManager {
  public:
    Status MakeMove(const int row, const int column, const char letter, int count_move);
  
  private:
    Game game;
};  
#endif /* GameManager_h */
