#ifndef RequestManager_h
#define RequestManager_h
#include "GameManager.h"
#include "Player.h"
#include "IRequestManager.h"
#include "Game.h"

namespace Request_Manager {
/* ------------------------------------------------------------------
 * CLASS NAME: RequestManager
 * ------------------------------------------------------------------
 * @brief Get User input for row and column.
 *
 * The Request Manager class implements the IRequestManager interface
 * to create an interface with IRequestManager. It is responsible for
 * getting a validated user input for row and column number during a
 * Tic-Tac-Toe game.
 * ------------------------------------------------------------------
 */
  class RequestManager : public IRequestManager {
    public:
      RequestManager() = default;
      int GetValidatedUserInput(int& user_input, const int row, const int column, const char letter);
      ~RequestManager();
    
    private:
      GameManager game_manager;
      IRequestManager *ptr;
  };
}
#endif /* RequestManager_h */
