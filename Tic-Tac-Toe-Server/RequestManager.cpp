#include <iostream>
#include "RequestManager.h"
namespace Request_Manager {
  /* ----------------------------------------------------------------------
   * FUNCTION NAME: GetValidatedUserInput
   * ----------------------------------------------------------------------
   * @brief Validates and returns user input within a specified range
   *
   * @details This function prompts the user for input, validates it to
   *          ensure it falls within the specified range [low, high],
   *          and handles input errors. If an invalid input is detected,
   *          it prompts the user to enter a valid value until successful.
   *
   * @param user_input  [out] Reference to store the validated user input.
   * @param low         [in]  The minimum valid input value.
   * @param high        [in]  The maximum valid input number.
   * @param letter      [in]  A character ('R' or 'C') to indicate whether
                              the user is selecting a row or column.
   *
   * @return Returns the validated user input.
   * ----------------------------------------------------------------------
   */
  int RequestManager::GetValidatedUserInput(int& user_input, const int low, const int high, const char letter) {
    PromptingUser prompting;
    while (!(std::cin >> user_input) || user_input < low || user_input > high) {
      if (letter == 'R') {
        prompting.UserForInputValidationError(low, high, letter);
      } else {
        prompting.UserForInputValidationError(low, high, letter);
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    return user_input;
  }
  
  /* ----------------------------------------------------------------------
   * DESTRUCTOR NAME: ~RequestManager
   * ----------------------------------------------------------------------
   * @brief Destructor for the RequestManager class.
   *
   * @details This destructor is responsible for releasing the resources
   *          associated with the RequestManager object. It deletes the
   *          dynamically allocated memory pointed to by the 'ptr' member.
   *
   * @note    This destructor is automatically called when an instance of
   *          the RequestManager class goes out of scope.
   *
   * @see     IRequestManager
   *
   * ----------------------------------------------------------------------
   */
  RequestManager::~RequestManager() {
    delete ptr;
  }
}
