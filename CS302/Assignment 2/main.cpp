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

bool checkRow(vector<string>, int, int, string);
vector<string> enterRow(vector<string>, int, int, string);
vector<string> enterColumn(vector<string>, int, int, string);
bool checkColumn(vector<string>, int, int, string);
void clearRow(vector<string>, int, int);
void clearColumn(vector<string>, int, int);
bool solveCrossword(vector<string>, vector<string>, int);


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
    solveCrossword(crossword, words, 0);

    for(int i =0;i<10;i++){
        cout<<crossword[i]<<endl;
    }
  return 0;
  
}


bool checkRow(vector<string> board, int row, int col, string word){


}

vector<string> enterRow(vector<string> board, int row, int col, string word){

}

vector<string> enterColumn(vector<string> board, int row, int col, string word){

}

bool checkColumn(vector<string> board, int row, int col, string word){

}

void clearRow(vector<string>, int row, int col){

}

void clearColumn(vector<string> board, int row, int col){

}

bool solveCrossword(vector<string> board, vector<string> wordList, int index){

}
