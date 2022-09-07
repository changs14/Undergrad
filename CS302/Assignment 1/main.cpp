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

using namespace std;

struct Node{
  int data;
  Node * prev, *next;
};

void traverse(Node*);
bool find(Node*, int);

int main(){
  //Variables to get file
  string line;
  string filename;
  ifstream inFile;

  //Node variables
  Node * head;

  //Get user input for file and open file
  do{
    //Display prompt to enter file
    cout<<"Enter a file name: ";
    cin>>filename;

    //Open the file
    inFile.open(filename.c_str());

    //Display error message if file could not be opened
    if(!inFile.is_open()){
      cout<<"File invalid."<<endl;
    }
  }while(inFile.fail());

  cout<<endl;

  //Read in contents and store it in the linked list
  traverse(head);
  //Cocktail sort dat bih

  //End program or something
    return 0;
}

/************************ FUNCTIONS ****************************/

void traverse(Node * r){
  if(r==NULL){
    return;
  }

  cout<<r->data<<endl;

  traverse(r->link);
}

bool find(Node * r, int s){
  if(r==NULL){
    return false;
  }
  else if(r->data == s){
    return true;
  }

  return find(r->link, s);
}