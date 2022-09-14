/* Name: Stephaney Chang
   NSHEID: 2001508920
   Class: CS 302
   Assignment: 1
   Description: This program will get input from a user of a crossword board and a list of words. Using the backtrack algorithm,
                the program will solve the crossword puzzle.
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> enterRows(char[10][10], int, int, string);
void enterColumn(char[10][10], int, int, string);
bool emptyCrossWord(char [10][10]);
bool solveCrossword(char [10][10], vector<string>);


int main(){
    vector<string> crossword; //Crossword board
    vector<string> words;

    //File variables
    string line;
    string filename;
    ifstream inFile;
    
    //Get user input file
    do{
        cout<<"Enter file name: ";
        cin>>filename;

        //Open file
        inFile.open(filename.c_str());

        //Error messages if file fails to open
        if(!inFile.is_open()){
            cout<<"Invalid file."<<endl;
        }

    }while(inFile.fail());

    cout<<endl;
    
    //Read in file, assign to variables as needed
    //First ten lines will be assigned to the crossword variable
    for (int i = 0; i < 10; i++){
        inFile>>line;
        crossword.push_back(line);
    }

    //The the words in the list
    inFile.ignore(1000, '\n');  //Ignore the space between grid and words

    //Get the words
    for(int i = 0; i<4; i++){
        inFile>>line;   //Get current word in the line
        words.push_back(line); //Add to the words list
    }

    //Close the file
    inFile.close();

    //Call functions
    solveCrossword(crossword, words);
    
    //Print the solved crossword puzzle

    for(int i=0; i<10;i++){
        cout<<crossword[i]<<endl;
    }

  return 0;
  
}

 enterRows(char board[10][10], int row, int column, string currWord){
    //Find a free position of the cross word represented by '-'
    for(int i=0; i<currWord.length();i++){
        if(board[row+i][column] == '-' || board[row+i][column] == currWord[i]){
            board[row+i][column] = currWord[i];
        }
        else{
            board[0][0] = 'x';
        }
    }

}

void enterColumn(char board[10][10], int row, int column, string currWord){
    //Find a free position in the columns represented by '-'
    for(int i=0; i<currWord.length();i++){
        if(board[row][column+i] == '-' || board[row+i][column] == currWord[i]){
            board[row][column+i] = currWord[i];
        }
        else{
            board[0][0] = 'x';
        }

    }   
}

bool emptyCrossWord(char board[10][10]){
    for(int i=0; i<10;i++){
        for(int j =0; j<10;j++){
            if(board[i][j] == '-'){
                return false;
            }
        }
    }
    return true;
}

bool solveCrossword(char board[10][10], vector<string> wordList){
    //Solve the crossword puzzle using the backtracking algorithm and recursion

    string current;
    bool empty = emptyCrossWord(board);

    if (empty == false){
        return true;
    }

    for(int k=0; k<4;k++){
        current = wordList[k];
        
        for(int i=0; i<10;i++){
            //Check the vertical rows
            for(int j=0;j<current.length();j++){
                enterRows(board, j, i, current);
                enterColumn(board, i, j, current);

                if (board[0][0] != 'x'){
                        solveCrossword(board, wordList);
                }

            }
        }
            
    }
        return false;
    
}