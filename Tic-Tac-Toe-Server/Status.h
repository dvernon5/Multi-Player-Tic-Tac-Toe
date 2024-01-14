#ifndef Status_h
#define Status_h
#include <iostream>

/* -------------------------------------------------------------------------------------
 * STRUCT NAME: Status
 * -------------------------------------------------------------------------------------
 * @brief Holds variables for status code, game_board and player's symbol.
 *
 * The Status struct is used to keep track of the status of the game, including
 * the status code, current state of the game board, and the player symbol ('X' or 'O').
 * -------------------------------------------------------------------------------------
 */
struct Status {
  std::string status_code;
  std::string game_board;
  char letter;
};
#endif /* Status_h */
