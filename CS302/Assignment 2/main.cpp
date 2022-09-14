/* Name: Stephaney Chang
   NSHEID: 2001508920
   Class: CS 302
   Assignment: 1
   Description: This program will get input from a user of a crossword board and a list of words. Using the backtrack algorithm,
                the program will solve the crossword puzzle.
*/

#include <iostream>
#include <fstream>

using namespace std;

int findEmptyBox(char);
int findNextBox(char, int, int);
bool solveCrossword(char);


int main(){
    char crossword[10][10]; //Crossword board
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

    //Close the file
    inFile.close();

    //Call functions

    //Print the solved crossword puzzle


  return 0;
  
}