#ifndef PromptingUser_h
#define PromptingUser_h
/* ------------------------------------------------------------------------------------
 * CLASS NAME: PromptingUser
 * ------------------------------------------------------------------------------------
 * @brief: Ask the user to fulfill a command.
 *
 * The PromptingUser class provides methods for prompting the user with different tasks
 * such as notifying them of their turn, requesting input for row and column numbers
 * and validating user input errors.
 * ------------------------------------------------------------------------------------
 */
class PromptingUser {
  public:
    void PlayerTurn(const char letter);
    void UserForRowNumber();
    void UserForColumnNumber();
    void ForInputValidationError(const int low, const int high, const char letter);
};
#endif /* PromptingUser_h */
