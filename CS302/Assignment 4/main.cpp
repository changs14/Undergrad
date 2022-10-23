/* Name: Stephaney Chang
   NSHEID: 2001508920
   Class: CS 302
   Assignment: 3
   Description:
*/

#include "func.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  // Initialize vector of binTree nodes
  std::vector<binTree *> forest;
  binTree * firstNode = new binTree();
  forest.push_back(firstNode);

  // File variables
  std::string line;
  std::string filename;
  std::ifstream inFile;

  int num = 0;
  int freq = 0; //Temp var to store the frequency

  do {
    std::cout << "Enter filename: ";
    std::cin >> filename;

    inFile.open(filename.c_str());

    if (!inFile.is_open()) {
      std::cout << "Invalid file. \n";
    }
  } while (inFile.fail());

  std::cout << "\n";

  //Get info from file and store into binary tree
  for(int i=0; i<30; i++){
    //Get the letter number
    inFile>>line;
    num = std::stoi(line); //Convert number to ascii
    char let = char(num);
    std::cout<<let<<"\n";
    
    //Get the frequency
    inFile>>line;
    freq = std::stoi(line);

    //Create bintree
    binTree * tempTree = new binTree(tempTree, );

    binTree * previousTree = tempTree;
    

    
    
    }

  return 0;
}
