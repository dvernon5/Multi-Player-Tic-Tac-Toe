#ifndef ResponseManager_h
#define ResponseManager_h
#include "PromptingUser.h"
/* -------------------------------------------------------
 * CLASS NAME: ResponseManager
 * -------------------------------------------------------
 * @brief Get User input for row and column.
 *
 * The Request Manager class is responsible for getting a
 * validated user input for row and column number during a
 * Tic-Tac-Toe game.
 * -------------------------------------------------------
 */
class ResponseManager {
  public:
    ResponseManager() = default;
    int GetValidatedUserInput(int& user_input, const int row, const int column, const char letter);
  
  private:
    PromptingUser prompting;
};
#endif /* ResponseManager_h */
