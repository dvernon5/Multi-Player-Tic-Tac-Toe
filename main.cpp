#include<iostream>
#include<string>
using namespace std;

const int ROW_AND_COLUMN = 3;

void displayGameBoard(char array[][ROW_AND_COLUMN]);

void player(char array[][ROW_AND_COLUMN], char);

bool checkIfWinnerAcross(const char array[][ROW_AND_COLUMN], const char, string&);

bool checkIfWinnerDown(const char array[][ROW_AND_COLUMN], const char, string&);

bool checkIfWinnerLeftToRightDiagonal(const char array[][ROW_AND_COLUMN], const char, string&);

bool checkIfWinnerRightToLeftDiagonal(const char array[][ROW_AND_COLUMN], const char, string&);

bool checkIfWinner(const char array[][ROW_AND_COLUMN], const char, string&);

int inputValidate(int, int, int);

int main(void)
{
    char gameBoard[][ROW_AND_COLUMN] = { { '*', '*', '*' },
                                         { '*', '*', '*' },
                                         { '*', '*', '*' } };
    string gameWinner = "";
    
    displayGameBoard(gameBoard);
    
    player(gameBoard, 'X');
    displayGameBoard(gameBoard);
    
    for (int i = 0; i < 4; i++)
    {
        player(gameBoard, 'O');
        displayGameBoard(gameBoard);
        
        if (checkIfWinner(gameBoard, 'O', gameWinner) == true)
        {
            break;
        }
        
        player(gameBoard, 'X');
        displayGameBoard(gameBoard);
        
        if (checkIfWinner(gameBoard, 'X', gameWinner) == true)
        {
            break;
        }
    }
    
    cout << "Game winner: " << gameWinner << endl;
    
    return 0;
}

void displayGameBoard(char array[][ROW_AND_COLUMN])
{
    cout << endl;
    
    for (int row = 0; row < ROW_AND_COLUMN; row++)
    {
        for (int column = 0; column < ROW_AND_COLUMN; column++)
        {
            cout << array[row][column] << " ";
        }
        cout << endl;
    }
    
    cout << endl;
}

void player(char array[][ROW_AND_COLUMN], char letter)
{
    cout << "Select a location to place an " << letter << ": " << endl;
    
    int row = 0, column = 0;
    bool spaceOccupied = false;
    
    do
    {
        cout << "Which row? (Enter a number between 1 and 3): ";
        row = inputValidate(row, 1, 3);
        
        cout << "Which column? (Enter a number between 1 and 3): ";
        column = inputValidate(column, 1, 3);
        
        if (array[(row - 1)][(column - 1)] == '*')
        {
            array[(row - 1)][(column - 1)] = letter;
            spaceOccupied = true;
        }
        else
        {
            cout << "Sorry! spot is taken." << endl;
            spaceOccupied = false;
        }
    } while (spaceOccupied == false);
}

int inputValidate(int userInput, int lowest, int highest)
{
    while (!(cin >> userInput) || (userInput < lowest) || (userInput > highest))
    {
        cout << "Error. Enter number between " << lowest << " to " << highest << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    return userInput;
}

bool checkIfWinner(const char array[][ROW_AND_COLUMN], const char letter, string& gameWinner)
{
    bool winner = false;
    
    if (checkIfWinnerAcross(array, letter, gameWinner) == true)
    {
        winner = true;
    }
    else if (checkIfWinnerDown(array, letter, gameWinner) == true)
    {
        winner = true;
    }
    else if (checkIfWinnerLeftToRightDiagonal(array, letter, gameWinner) == true)
    {
        winner = true;
    }
    else if (checkIfWinnerRightToLeftDiagonal(array, letter, gameWinner) == true)
    {
        winner = true;
    }
    else
    {
        gameWinner = "TIE";
        winner = false;
    }
    
    return winner;
}

bool checkIfWinnerAcross(const char array[][ROW_AND_COLUMN], const char letter, string& gameWinner)
{
    int letterAcross = 0;
    bool winner = false;
    
    for (int row = 0; row < ROW_AND_COLUMN; row++)
    {
        for (int column = 0; column < ROW_AND_COLUMN; column++)
        {
            if (array[row][column] == letter)
            {
                letterAcross++;
            }
        }
        
        if (letterAcross == 3)
        {
            if (letter == 'X')
            {
                gameWinner = "Player1";
            }
            else if (letter == 'O')
            {
                gameWinner = "Player2";
            }
            
            winner = true;
            break;
        }
        else
        {
            winner = false;
            letterAcross = 0;
        }
    }
    
    return winner;
}

bool checkIfWinnerDown(const char array[][ROW_AND_COLUMN], const char letter, string& gameWinner)
{
    int letterDown = 0;
    bool winner = false;
    
    for (int row = 0; row < ROW_AND_COLUMN; row++)
    {
        for (int column = 0; column < ROW_AND_COLUMN; column++)
        {
            if (array[row][column] == letter)
            {
                letterDown++;
            }
        }
        
        if (letterDown == 3)
        {
            if (letter == 'X')
            {
                gameWinner = "Player1";
            }
            else if (letter == 'O')
            {
                gameWinner = "Player2";
            }
            
            winner = true;
            break;
        }
        else
        {
            winner = false;
            letterDown = 0;
        }
    }
    
    return winner;
}

bool checkIfWinnerLeftToRightDiagonal(const char array[][ROW_AND_COLUMN], const char letter, string& gameWinner)
{
    int letterDiagonal = 0;
    bool winner = false;
    
    for (int i = 0; i < ROW_AND_COLUMN; i++)
    {
        if (array[i][i] == letter)
        {
            letterDiagonal++;
        }
    }
    
    if (letterDiagonal == 3)
    {
        if (letter == 'X')
        {
            gameWinner = "Player1";
        }
        else if (letter == 'O')
        {
            gameWinner = "Player2";
        }
        
        winner = true;
    }
    else
    {
        winner = false;
    }
    
    return winner;
}

bool checkIfWinnerRightToLeftDiagonal(const char array[][ROW_AND_COLUMN], const char letter, string& gameWinner)
{
    int letterDiagonal = 0;
    int winner = false;
    
    for (int row = 0, column = ROW_AND_COLUMN - 1; row < ROW_AND_COLUMN; row++, column--)
    {
        if (array[row][column] == letter)
        {
            letterDiagonal++;
        }
    }
    
    if (letterDiagonal == 3)
    {
        if (letter == 'X')
        {
            gameWinner = "Player1";
        }
        else if (letter == 'O')
        {
            gameWinner = "Player2";
        }
        
        winner = true;
    }
    else
    {
        winner = false;
    }
    
    return winner;
}
