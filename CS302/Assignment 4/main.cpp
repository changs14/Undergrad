/* Name: Stephaney Chang
   NSHEID: 2001508920
   Class: CS 302
   Assignment: 3
   Description: 
*/

#include <iostream>
#include <string>
#include<fstream>
#include "func.h"

int main(){
    //File variables
    std::string line; 
    std::string filename;
    std::ifstream inFile;

    do{
        std::cout<<"Enter filename: \n";
        std::cin>>filename;

        inFile.open(filename.c_str());

        if(!inFile.is_open()){
            std::cout<<"Invalid file. \n";
        }
    }while(inFile.fail());


    return 0;
}
