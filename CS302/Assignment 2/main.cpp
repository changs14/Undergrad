/* Name: Stephaney Chang
   NSHEID: 2001508920
   Class: CS 302
   Assignment: 2
   Description: This program will get input from a user of a crossword board and a list of words. Using recursion,
                the program will solve the crossword puzzle by irst checking the vacancy of the crossword and fitting the current
                word into the vacant spots until the entire crossword has no more empty spaces to fill.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "functions.h"

using namespace std;

int main()
{
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
        if(!inFile.is_open())
        {
            cout<<"Invalid file."<<endl;
        }

    }while(inFile.fail());

    cout<<endl;
    
    //Read in file, assign to variables as needed
    //First ten lines will be assigned to the crossword variable
    for (int i = 0; i < 10; i++)
    {
        inFile>>line;
        crossword.push_back(line);
    }

    //The the words in the list
    inFile.ignore(1000, '\n');  //Ignore the space between grid and words

    //Get the words
    for(int i = 0; i < 4; i++)
    {
        inFile>>line;   //Get current word in the line
        words.push_back(line);
    }

    //Close the file
    inFile.close();

    //Print the solved cross word
    if(solveCrossword(crossword, words))
    {
        for(int i = 0; i < 10; i++)
        {
            cout<<crossword[i]<<endl;
        }
    }
    
    //End program
  return 0;
  
}

