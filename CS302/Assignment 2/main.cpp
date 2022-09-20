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

bool checkRow(vector<string>&, int, int, string);
void enterRow(vector<string>&, int, int, string);
void enterColumn(vector<string>&, int, int, string);
bool checkColumn(vector<string>&, int, int, string);
void clearRow(vector<string>&, int, int, string);
void clearColumn(vector<string>&, int, int, string);
bool solveCrossword(vector<string>&, vector<string>);


int main(){
    vector<string> crossword; //Crossword board
    vector<string> words;

    //File variables
    string line;
    string filename;
    ifstream inFile;

    bool puzzleSolved = false;
    
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
        words.push_back(line);
    }

    //Close the file
    inFile.close();

    //Call functions
    puzzleSolved = solveCrossword(crossword, words);

        for(int i=0;i<10;i++){
            cout<<crossword[i]<<endl;
        }

  return 0;
  
}


bool checkRow(vector<string> &board, int row, int col, string word){
    int a=0;
    int b=0;
    if(col-1 >=0){
        if(board[row][col-1] != '+'){
            if(board[row][col-1] == word[0]){
                a = 1;
                b = 1;
            }
            else{
                return false;
            }
        }
    }

    for(int i = col;i<10 && a<word.length();i++, a++){

        if(board[row][i] == '-'){
            b+=1;
        }
        else if(board[row][i] == word[a]){
            b+=1;
        }
    }

    if(b==word.length()){
        return true;
    }

    return false;

}

void enterRow(vector<string>& board, int row, int col, string word){

    int a = 0;
    if(row-1>=0){
        if(board[row][col-1] == word[0]){
            a = 1;
            
        }
    }

    for(int i = a; i<word.length(); i++){
        board[row][col] = word[i];
        col++;
    }
}

void enterColumn(vector<string> &board, int row, int col, string word){
    int a = 0;
    if(row-1>=0){
        if(board[row-1][col] == word[0]){
            a = 1;
        }
    }

    for(int i = a; i<word.length(); i++){
        board[row][col] = word[i];
        row++;
    }
}

bool checkColumn(vector<string> &board, int row, int col, string word){
    int a=0;
    int b=0;
    if(row-1 >=0){
        if(board[row-1][col] != '+'){
            if(board[row-1][col] == word[0]){
                a = 1;
                b=1;
            }
            else{
                return false;
            }
        }
    }

    for(int i = row;i<10 && a<word.length();i++, a++){

        if(board[i][col] == '-'){
            b+=1;
        }
        else if(board[i][col] == word[a]){
            b+=1;
        }
        
    }

    if(b==word.length()){
        return true;
    }

    return false;
}

void clearRow(vector<string>& board, int row, int col, string word){
    int a = 0;

    if(col>=1){
        if(board[row][col] == word[0]){
            a = 1;
        }
    }

    for(int i=a; i<word.length();i++){
        board[row][col] = '-'; 
        col++;
    }
}

void clearColumn(vector<string>& board, int row, int col, string word){
    int a = 0;

    if(row >= 1){
        if(board[row][col] == word[0]){
            a = 1;
        }
    }

    for(int i=a; i<word.length();i++){
        board[row][col] = '-';
        row++;
    }
}

bool solveCrossword(vector<string> &board, vector<string> wordList){
    int row = 0;
    int col = 0;

    bool empty = false;
    string word;

    for(int i = 0; i<10; i++){
        for(int j=0; j<10; j++){
            if(board[i][j] == '-'){
                row = i;
                col = j;
                empty = true;
                break;
            }
            if(empty){
                break;
            }
        }
    }

    if(!empty){
        return true;
    }

    for(int i=0; i<wordList.size(); i++){
        word = wordList[i];

        if(checkRow(board, row, col, word)){
            enterRow(board, row, col, word);
            if(solveCrossword(board, wordList)){
                return true;
            }
            clearRow(board, row, col, word);
        }

        if(checkColumn(board, row, col, word)){
            enterColumn(board, row, col, word);
            if(solveCrossword(board, wordList)){
                return true;
            }

            clearColumn(board, row, col, word);
        }
    }

    return false;
}