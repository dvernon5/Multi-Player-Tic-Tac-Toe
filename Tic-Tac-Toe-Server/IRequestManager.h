#ifndef IRequestManager_h
#define IRequestManager_h

/* -----------------------------------------------------------------------------------
 * CLASS NAME: IRequestManager
 * -----------------------------------------------------------------------------------
 * @brief Interface for handling user input in a Tic-Tac-Toe game.
 *
 * The IRequesManager interface declares a method for getting validated
 * user input and column numbers during a game. Classes that implements
 * this interface should provide their implementation of the GetUserValidatedUserInput
 * method.
 * -----------------------------------------------------------------------------------
 */

class IRequestManager {
  public:
    virtual int GetValidatedUserInput(int& user_input, const int row, const int column, const char letter) = 0;
    virtual ~IRequestManager() {}
};
#endif /* IRequestManager_h */
