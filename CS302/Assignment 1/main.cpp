 /* Name: Stephaney Chang
   NSHEID: 2001508920
   Class: CS 302
   Assignment: 1
   Description: This program will get a linked list and sort the elements in ascending order.Doubly linked l ist and iterators 
                will be used to manipulate the list. 
*/
 
#include "LL.h"
#include <iostream>
#include <fstream>


int main(){
  //Variables to get file
  string line;
  string filename;
  ifstream inFile;

  //Get user input for file and open file
  do{
    cout<<"Enter a file name: ";
    cin>>filename;
    inFile.open(filename.c_str());

    if(!inFile.is_open()){
      cout<<"File invalid."<<endl;
    }
  }while(inFile.fail());

  cout<<endl;

  //Read in contents and store it in the linked list

  //Cocktail sort dat bih

  //End program or something
    return 0;
}