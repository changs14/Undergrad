/* Name: Stephaney Chang
   NSHEID: 2001508920
   Class: CS 302
   Assignment: 2
   Description: Function file for main.cpp - solving crossword puzzle
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Row functions
bool checkRow(vector<string>&, int, int, string);
void enterRow(vector<string>&, int, int, string);
void clearRow(vector<string>&, int, int, string);

//Column functions
void enterColumn(vector<string>&, int, int, string);
bool checkColumn(vector<string>&, int, int, string);
void clearColumn(vector<string>&, int, int, string);

//Solve function
bool solveCrossword(vector<string>&, vector<string>);

/* checkRow will check if the crossword has any empty spaces that the word can fit into.
   If the length of the word equals to the number of consequtive '-' then the word can be fit into the row and return true.
   Otherwise, word cannot fit into the crossword - so return false.
*/
bool checkRow(vector<string> &board, int row, int col, string word)
{
    int numOfLetters=0; //Number of letters that can be placed in the row
    int filledSpaces = 0;    //Variable to store the number of conscequtive empty spaces '-'

    //Check if the current index is '+' or not an empty box to place a letter in
    if(board[row][col-1] != '+')
    {
        //Check if the previous index has the first letter of the current word
        if(board[row][col-1] == word[0])
        {
            numOfLetters = 1; //First letter of the word has been placed so there is at least one letter
            filledSpaces = 1; //There is one filled space
        }
        else
        {
            return false;   //Word has not been placed yet
        }
    }

    //Check if the length of the word matches the number of '-' in a row
    for(int i = col; i < 10; i++)
    {
        if(numOfLetters<word.length())
        {
           if(board[row][i] == word[numOfLetters] || board[row][i] == '-')
           {
            //Check if the letter has been placed already 
            filledSpaces++;
            }   
        }
        numOfLetters++; //Get the position of the next letter in the word
    }

    //Check if the length of the word and the amount of '-' in a row fit
    if(filledSpaces == word.length())
    {
        return true;
    }

    return false;   //Length of the word and '-' do not match
}

/* enterRow will take a crossword puzzle and the current word and enter the letters into the row.
*/
void enterRow(vector<string>& board, int row, int col, string word)
{
    int firstLetter; //Current count of letters in the board (first letter)

    if(board[row][col-1] == word[0])
    {
        firstLetter = 1;  //There is a first letter
    }
    else
    {
        firstLetter = 0; //There is no first letter
    }

    //Enter the remaining letters into the crossword
    for(int i = firstLetter; i < word.length(); i++)
    {
        board[row][col] = word[i];  //Enter letter
        col++; //Update column
    }
}

/*clearRow will take the empty spaces in the crossword puzzle of the length of the word and clear it, replacing the letters with '-'
*/
void clearRow(vector<string>& board, int row, int col, string word)
{
    int firstLetter;

    //Check if there is the word's first letter in index
    if(board[row][col-1] == word[0])
    {
        firstLetter = 1; //There is first letter
    }
    else{
        firstLetter = 0; //No first letter
    }

    //For the length of the word, clear out the letters and replace with '-'
    for(int i = firstLetter; i < word.length(); i++)
    {
        board[row][col] = '-'; //Replace letter with empty space
        col++; //Update column
    }
}

/* checkColumn will check the number of empty spaces '-' to the number of letters in the current word
*/
bool checkColumn(vector<string> &board, int row, int col, string word)
{
    int numOfLetters = 0; //Number of letters in the crossword
    int filledSpaces = 0; //Number of spaces that have been filled with letters

    //Check if the previous row is not the first row or is not an empty space
    if(row-1 > 0 && board[row-1][col] != '+')
    {
        //Check if first letter has been placed
        if(board[row-1][col] == word[0])
        {
            numOfLetters = 1;   //First letter has been placed
            filledSpaces = 1; //There is an empty space
        }
        else
        {
            return false; //Word does not fit
        }
    }

    //Check for the number of letters and the number of spaces
    for(int i = row; i < 10; i++)
    {
        //Check if the number of letters equals the total number of letters in the word
        if(numOfLetters < word.length())
        {
            //Check if an empty space or if there is a letter in the space
            if(board[i][col] == '-' || board[i][col] == word[i])
            {
                filledSpaces++;
            }
        }

        numOfLetters++; //Increment letter index

    }

    //Check if the number of empty spaces equal the length of the word
    if(filledSpaces == word.length())
    {
        return true;
    }

    return false;
}

/* enterColumn will take a crossword puzzle and the current word and enter the letters into the column
*/
void enterColumn(vector<string> &board, int row, int col, string word)
{
    int firstLetter; //Number of letters in the column

    //Check if the row is not the first row or has the first letter of the word
    if(row-1 > 0 && board[row-1][col] == word[0])
    {
        firstLetter = 1; //First letter has been entered
    }
    else
    {
        firstLetter = 0; //No first letter
    }

    //Enter the remaining letters into the crossword
    for(int i = firstLetter; i < word.length(); i++)
    {
        board[row][col] = word[i];  //Enter word
        row++; //Update row
    }
}

/* clearColumn will take a crossword puzzle and an  index in the vector and clear out the crossword where the word is
*/
void clearColumn(vector<string>& board, int row, int col, string word)
{
    int firstLetter;

    //Check if the row has the first letter of the word
    if(row-1 >= 0)
    {
        if(board[row-1][col] == word[0]){
            firstLetter = 1; //There is letter
        }
    }
    else
    {
        firstLetter = 0; //There is no letter
    }

    //Clear the column and replace the letter with an empty space
    for(int i = firstLetter; i < word.length(); i++)
    {
        board[row][col] = '-'; //Clear letter
        row++; //Update row index
    }
}

/* solveCrossword is a recursive function that will cycle through a word list and a crossword board. The function will first check
   if the crossword is empty (meaning not solved). If it is empty, then it will take the words and insert attempt them into the crossword
   vertically and horizontally until the entire board is filled.
*/
bool solveCrossword(vector<string> &board, vector<string> wordList)
{
    int row = 0;    //Initialize row
    int col = 0;    //Initialize column

    vector<string> usedWords = wordList; //Save the currentd

    bool empty = false;

    //i = rows
    //j = columns
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(board[i][j] == '-')
            {
                //There is an empty space to place a letter
                row = i;    //Store the row index
                col = j;    //Store the column index
                empty = true;   //There is an empty space
                break;
            }
        }

        //Check if an empty space has been found
        if(empty == true)
        {  
            //Empty space has been found so break loop early
            break;
        }
    }

    if(empty == false || wordList.empty())
    {
        //No more empty spaces means the crossword has been solved
        return true;
    }

    //Solve the crossword puzzle for the length of the word list
    for(int i = 0; i < wordList.size(); i++)
    {
        //Check if the word can fit into the crossword horizontally
        if(checkRow(board, row, col, wordList[i]))
        {
            //Enter the word into the row
            enterRow(board, row, col, wordList[i]);

            wordList.erase(wordList.begin()+i);

            //Check if the crossword has been solved
            if(solveCrossword(board, wordList))
            {
                return true; //Crossword has been solved
            }
            else{
                //Crossword not solved so clear the current row
                wordList = usedWords;
                clearRow(board, row, col, wordList[i]);
            }
        }

        //Check if the word can fit into the crossword vertically
        if(checkColumn(board, row, col, wordList[i]))
        {
            //Enter the word into the column
            enterColumn(board, row, col, wordList[i]);

            wordList.erase(wordList.begin()+i);

            //Check if the crossword has been solved
            if(solveCrossword(board, wordList))
            {
                return true; //Crossword has been solved
            }
            else{
                //Crossword not solved so clear the current column
                wordList = usedWords;
                clearColumn(board, row, col, wordList[i]);
            }
        }
    }

    return false; //Crossword has not been solved yet
}