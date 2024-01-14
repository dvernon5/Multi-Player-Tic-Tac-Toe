#include "ResponseManager.h"
#include <iostream>

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
int ResponseManager::GetValidatedUserInput(int& user_input, const int low, const int high, const char letter) {
  while (!(std::cin >> user_input) || user_input < low || user_input > high) {
    if (letter == 'R') {
      prompting.ForInputValidationError(low, high, letter);
    } else {
      prompting.ForInputValidationError(low, high, letter);
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  
  return user_input;
}
