#include <iostream>
#include <string>
const int ROWS_AND_COLUMNS = 3;
void DisplayGameBoard(const char[][ROWS_AND_COLUMNS]);
void Player(char[][ROWS_AND_COLUMNS], const char);
int InputValidation(int, const int, const int);
bool CheckIfWinner(const char[][ROWS_AND_COLUMNS], const char, std::string&);
bool CheckIfWinnerAcross(const char[][ROWS_AND_COLUMNS], const char, std::string&);
bool CheckIfWinnerDown(const char[][ROWS_AND_COLUMNS], const char, std::string&);
bool CheckIfWinnerLeftToRightDiagonal(const char[][ROWS_AND_COLUMNS], const char, std::string&);
bool CheckIfWinnerRightToLeftDiagonal(const char[][ROWS_AND_COLUMNS], const char, std::string&);

int main(void) {
  char game_board[ROWS_AND_COLUMNS][ROWS_AND_COLUMNS] = {
    { '*', '*', '*'},
    { '*', '*', '*'},
    { '*', '*', '*'}
  };
  std::string game_winner = "";
  DisplayGameBoard(game_board);
  Player(game_board, 'X');
  DisplayGameBoard(game_board);
  for (size_t itr = 0; itr < 4; ++itr) {
    Player(game_board, 'O');
    DisplayGameBoard(game_board);
    if (CheckIfWinner(game_board, 'O', game_winner) == true) {
      break;
    }
    Player(game_board, 'X');
    DisplayGameBoard(game_board);
    if (CheckIfWinner(game_board, 'X', game_winner) == true) {
      break;
    }
  }
  
  std::cout << "Game winner: " << game_winner << std::endl;
  
  return 0;
}

void DisplayGameBoard(const char game_board[][ROWS_AND_COLUMNS]) {
  std::cout << std::endl;
  for (size_t row = 0; row < ROWS_AND_COLUMNS; ++row) {
    for (size_t column = 0; column < ROWS_AND_COLUMNS; ++column) {
      std::cout << game_board[row][column] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void Player(char game_board[][ROWS_AND_COLUMNS], const char letter) {
  std::cout << "Select a location to place " << letter << std::endl;
  int row = 0;
  int column = 0;
  bool space_occupied = false;
  do {
    std::cout << "Enter a row (Enter a number between 1 and 3): ";
    row = InputValidation(row, 1, 3);
    std::cout << "Enter a column: (Enter a number between 1 and 3): ";
    column = InputValidation(column, 1, 3);
    if (game_board[row - 1][column - 1] == '*') {
      game_board[row - 1][column - 1] = letter;
      space_occupied = true;
    } else {
      std::cerr << "Sorry space is taken. Please try again." << std::endl;;
    }
  } while (space_occupied == false);
}

int InputValidation(int user_input, const int lowest, const int highest) {
  while (!(std::cin >> user_input) || (user_input < lowest) || (user_input > highest)) {
    std::cerr << "Invalid! Enter a number between " << lowest << " and " << highest << ": ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  
  return user_input;
}

bool CheckIfWinner(const char game_board[][ROWS_AND_COLUMNS], const char letter, std::string& game_winner) {
  if (CheckIfWinnerAcross(game_board, letter, game_winner) == true) {
    return true;
  } else if (CheckIfWinnerDown(game_board, letter, game_winner) == true) {
    return true;
  } else if (CheckIfWinnerLeftToRightDiagonal(game_board, letter, game_winner) == true) {
    return true;
  } else if (CheckIfWinnerRightToLeftDiagonal(game_board, letter, game_winner) == true) {
    return true;
  } else {
    game_winner = "TIE";
  }
  
  return false;
}

bool CheckIfWinnerAcross(const char game_board[][ROWS_AND_COLUMNS], const char letter, std::string& game_winner) {
  int letter_across = 0;
  bool winner = false;
  for (size_t row = 0; row < ROWS_AND_COLUMNS; ++row) {
    for (size_t column = 0; column < ROWS_AND_COLUMNS; ++column) {
      if (game_board[row][column] == letter) {
        ++letter_across;
      }
    }
    if (letter_across == 3) {
      if (letter == 'X') {
        game_winner = "Player1";
      } else if (letter == 'O') {
        game_winner = "Player2";
      }
      winner = true;
      break;
    } else {
      letter_across = 0;
    }
  }
  
  return winner;
}

bool CheckIfWinnerDown(const char game_board[][ROWS_AND_COLUMNS], const char letter, std::string& game_winner) {
  int letter_down = 0;
  bool winner = false;
  for (size_t row = 0; row < ROWS_AND_COLUMNS; ++row) {
    for (size_t column = 0; column < ROWS_AND_COLUMNS; ++column) {
      if (game_board[column][row] == letter) {
        ++letter_down;
      }
    }
    if (letter_down == 3) {
      if (letter == 'X') {
        game_winner = "Player1";
      } else if (letter == 'O') {
        game_winner = "Player2";
      }
      winner = true;
      break;
    } else {
      letter_down = 0;
    }
  }
  
  return winner;
}

bool CheckIfWinnerLeftToRightDiagonal(const char game_board[][ROWS_AND_COLUMNS], const char letter, std::string& game_winner) {
  int letter_diagonal = 0;
  bool winner = false;
  for (size_t current_index = 0; current_index < ROWS_AND_COLUMNS; ++current_index) {
    if (game_board[current_index][current_index] == letter) {
      ++letter_diagonal;
    }
  }
  if (letter_diagonal == 3) {
    if (letter == 'X') {
      game_winner = "Player1";
    } else if (letter == 'O') {
      game_winner = "Player2";
    }
    winner = true;
  }
  
  return winner;
}

bool CheckIfWinnerRightToLeftDiagonal(const char game_board[][ROWS_AND_COLUMNS], const char letter, std::string& game_winner) {
  int letter_diagonal = 0;
  bool winner = false;
  for (size_t row = 0; row < ROWS_AND_COLUMNS; ++row) {
    auto column = ROWS_AND_COLUMNS - row - 1;
    if (game_board[row][column] == letter) {
      ++letter_diagonal;
    }
  }
  if (letter_diagonal == 3) {
    if (letter == 'X') {
      game_winner = "Player1";
    } else if (letter == 'O') {
      game_winner = "Player2";
    }
    winner = true;
  }
  
  return winner;
}
