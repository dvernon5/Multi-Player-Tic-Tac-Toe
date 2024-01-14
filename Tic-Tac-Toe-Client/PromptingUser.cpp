#include "PromptingUser.h"
#include <iostream>

void PromptingUser::PlayerTurn(const char letter) {
  std::cout << "Player " << letter << " it is your move." << std::endl;
}

void PromptingUser::UserForRowNumber() {
  std::cout << "Please enter a row number(1-3): ";
}

void PromptingUser::UserForColumnNumber() {
  std::cout << "Please enter a column number(1-3): ";
}

void PromptingUser::ForInputValidationError(const int low, const int high, const char letter) {
  if (letter == 'R') {
    std::cerr << "Invalid selection. Please enter a row number from " << low
              << " to " << high << ": ";
  } else {
    std::cerr << "Invalid selection. Please enter a column number from " << low
              << " to " << high << ": ";
  }
}
