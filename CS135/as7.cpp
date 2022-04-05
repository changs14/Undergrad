/* Name: Stephaney Chang, 2001508920, CS1351002, Assignment 7
 * Description: This program gets user inputted option of either reading a txt file or calculate its contents into a chart.
 * Input: Option text input, text file
 * Output: Raw text file or shipping crate calculations using text filels
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

const int MIN_CRATE = 1; //Minimum size a shipping crate can be in ft
const int MAX_CRATE = 5; //Max size a shipping crate can be in ft
const int MIN_ROOM = 10; //Minimum size a storage room can be in ft
const int MAX_ROOM = 100; //Max size a storage room can be in ft

const double S_CRATE_RATE = 2.5; //Cost to ship a crate 1-4 cubic ft
const double M_CRATE_RATE = 3.0; //Cost to ship a crate 40-80 cubic ft
const double L_CRATE_RATE = 3.5; //Cost to ship a crate 80+ cubic ft
const double S_ROOM_RATE = 0.12; //Cost to ship in a room 1000-250000 cubic ft
const double M_ROOM_RATE = 0.09; //Cost to ship in room 250000-500000 cubic ft
const double L_ROOM_RATE = 0.07; //Cost to ship in room 500000-750000 cubic ft
const double XL_ROOM_RATE =0.05; // Cost to ship in room 750000+ cubic ft

int main(){
	double spaceW=0.0; //Space width
	double spaceH=0.0; //Space height
	double spaceL=0.0; //Space length

	double crateW=0.0; //Crate width
	double crateH=0.0; //Crate height
	double crateL=0.0; //Crate length
	
	double priceCrate=0.0; //Total price for crates
	double priceSpace=0.0; //Total price of spaces
	
	double crateRate = 0.0; //Crate price based on volume
	double spaceRate = 0.0; //Space price based on volume 
	
	//File variables
	string str = "------------+------------+------------+------------+------------+------------+------------+------------+";
	int count = 1;
	string answer;
	
    string line;
	string filename; //Will be used to get the input file
	ifstream inFile; //Input file
	ofstream outFile; //Outputfile
	
	//Main Loop
    do{
        cout<<"***************************************"<<endl;
        cout<<"\nD/d - Display file data\nF/f - File read\nQ/q - Quit program"<<endl;
        cout<<"\n***************************************"<<endl;
        cin>>answer;
        
		//Repeat until input is valid
        while(cin.fail()||(answer!="q"&&answer!="Q"&&answer!="f"&&answer!="F"&&answer!="d"&&answer!="D")){
            cin>>answer;
        }
        
        //OPTION D - read text file only
    	while (answer == "D" || answer == "d"){
    	    cout<<"Enter file name: ";
    	    cin>>filename;
    	    inFile.open(filename.c_str());
    	    
			//Open file and read txt
    	    if (inFile.is_open()){
    	        cout<<"File opened successfully!"<<endl;
    	        outFile.open("outfile.txt");
    	        
    	        while(!inFile.eof()){
    	            getline(inFile, line);
    	            outFile<<line<<endl;
    	        }
    	        
    	        break;
    	    }
    	    else{
    	        cout<<"Error please try again."<<endl;
    	    }
    	}

        //OPTION F - Read the file and calculate all inputs
    	while(answer == "F" || answer == "f"){
    	    cout<<"Enter file name: ";
    	    cin>>filename;
    	    inFile.open(filename.c_str());
    	    
			//Open the file and read inputs in txt file
    	    if (inFile.is_open()){
    	        cout<<"File opened successfully!"<<endl;
    	        outFile.open("output.txt");
    	        
    	        while(!inFile.eof()){
    	            getline(inFile,line);
    	            
					//Print the first row
    	            outFile<<"Dataset: "<<count<<endl;
    	            count++;
    	            outFile<<fixed<<showpoint<<setprecision(1)<<setfill(' ');
    	            outFile<<"LC"<<setw(10)<<"WC"<<setw(10)<<"HC"<<setw(10)<<"LS"<<setw(10)<<"WS"<<setw(10)<<"HS"<<setw(10)<<"CV";
    	            outFile<<setw(10)<<"CS"<<setw(10)<<"CD"<<setw(10)<<"SV"<<setw(10)<<"SS"<<setw(10)<<"SD"<<setw(20)<<"Total Crate"<<endl;
    	        
    	            //Get crate length
    	            inFile>>crateL;
    	            outFile<<crateL;
    	            //Errors for crate length
    	            if (inFile.fail()){
    	                inFile.clear();
    	                inFile.ignore();
                		outFile<<setw(35)<<"Error - Invalid crate length!\n"<<str<<"\n"<<endl;
    	                continue;
    	            }
                    if (crateL<MIN_CRATE || crateL>MAX_CRATE){
                		outFile<<setw(35)<<"Error - Invalid crate length!\n"<<str<<"\n"<<endl;
    	                continue;
                	}
                	
                	//Get crate width
                	inFile>>crateW;
                	outFile<<setw(10)<<crateW;
                	//Errors for crate width
                	if (inFile.fail()){
                	    inFile.clear();
    	                inFile.ignore(1000,'\n');
                		outFile<<setw(35)<<"Error - Invalid crate width!\n"<<str<<"\n"<<endl;
    	                continue;
                	}
                	if(crateW<MIN_CRATE || crateW>MAX_CRATE){
                		outFile<<setw(35)<<"Error - Invalid crate width!\n"<<str<<"\n"<<endl;
    	                continue;
                	}
                	
                	//Get crate height
                	inFile>>crateH;
                	outFile<<setw(10)<<crateH;
                	//Errors for crate height
                	if (inFile.fail()){
                	    inFile.clear();
    	                inFile.ignore(1000, '\n');
                		outFile<<setw(35)<<"Error - Invalid crate height!\n"<<str<<"\n"<<endl;
    	                continue;
                	}
                	if (crateH<MIN_CRATE || crateH>MAX_CRATE){
                		outFile<<setw(35)<<"Error - Invalid crate height!\n"<<str<<"\n"<<endl;
    	                continue;
                	}
                	
                	//Get space length
                	inFile>>spaceL;
                	outFile<<setw(10)<<spaceL;
                	//Errors for space length
                	if (inFile.fail()){
                	    inFile.clear();
    	                inFile.ignore(1000, '\n');
                	    outFile<<setw(35)<<"Error - Invalid space length!\n"<<str<<"\n"<<endl;
    	                continue;
                	}
                	if(spaceL<MIN_ROOM || spaceL>MAX_ROOM){
                		outFile<<setw(35)<<"Error - Invalid space length!\n"<<str<<"\n"<<endl;
    	                continue;
                	}
                
                	//Get space width
                	inFile>>spaceW;
                	outFile<<setw(10)<<spaceW;
                	//Error for space width
                	if (inFile.fail()){
                	    inFile.clear();
    	                inFile.ignore();
                	    outFile<<setw(35)<<"Error - Invalid space width!\n"<<str<<"\n"<<endl;
    	                continue;
                	}
                	if (spaceW<MIN_ROOM || spaceW>MAX_ROOM){
                		outFile<<setw(35)<<"Error - Invalid space width!\n"<<str<<"\n"<<endl;
    	                continue;
                	}
                	
                	//Get space height
                	inFile>>spaceH;
                	outFile<<setw(10)<<spaceH;
                	//Errors for space height
                    if (inFile.fail()){
                        inFile.clear();
    	                inFile.ignore();
                        outFile<<setw(35)<<"Error - Invalid space height!\n"<<str<<"\n"<<endl;
    	                continue;
                    }
                    if(spaceH<MIN_ROOM || spaceH>MAX_ROOM){
                		outFile<<setw(35)<<"Error - Invalid space height!\n"<<str<<"\n"<<endl;
    	                continue;
                	}
                	
                	//Calculations for crate volume, area, and diagonal
                	double volumeCrate = crateW * crateH * crateL;
                	double areaCrate = 2*(crateW*crateL+crateH*crateL+crateH*crateW);
                	double diagonalCrate = sqrt(pow(crateL,2)+pow(crateW,2)+pow(crateH,2));
        
                	//Calculations for space volume, area, and diagonal
                    double volumeSpace = spaceW * spaceH * spaceL;
                    double areaSpace= 2*(spaceW*spaceL+spaceH*spaceL+spaceH*spaceW);
                    double diagonalSpace = sqrt(pow(spaceL,2)+pow(spaceW,2)+pow(spaceH,2));
                
                	//Calculate the total amount of crates that can fit in storage space
                	double totalCrate = floor(spaceL/crateL)*floor(spaceW/crateW)*floor(spaceH/crateH);
                	
                	//PRICING CRATE
                	if(volumeCrate>=1 && volumeCrate<=40){
                		priceCrate = totalCrate*S_CRATE_RATE;
                		crateRate = S_CRATE_RATE;
                	}
                	else if (volumeCrate>=40 && volumeCrate<=80){
                		priceCrate = totalCrate*M_CRATE_RATE;
                		crateRate =M_CRATE_RATE;
                	}
                	else{
                		priceCrate = totalCrate*L_CRATE_RATE;
                		crateRate = L_CRATE_RATE;
                	};

					//PRICING SPACE
                	if(volumeSpace>=1000 && volumeSpace<=250000){
		                priceSpace = volumeSpace*S_ROOM_RATE;
		                spaceRate = S_ROOM_RATE;
                	}
                	else if (volumeSpace>=250000 && volumeSpace<=500000){
                		priceSpace = volumeSpace*M_ROOM_RATE;
                		spaceRate = M_ROOM_RATE;
                	}
                	else if(volumeSpace>=500000 && volumeSpace<=750000){
                		priceSpace = volumeSpace*L_ROOM_RATE;
                		spaceRate = L_ROOM_RATE;
                	}
                	else{
                		priceSpace = volumeSpace*XL_ROOM_RATE;
                		spaceRate = XL_ROOM_RATE;
                	};
	
					//Print the calculations for crate and space
                    outFile<<setw(10)<<volumeCrate<<setw(10)<<areaCrate<<setw(10)<<diagonalCrate<<setw(10)<<volumeSpace;
        	       outFile<<setw(10)<<areaSpace<<setw(10)<<diagonalSpace<<setw(20)<<totalCrate<<endl<<str<<endl;
        	        
					//Print the all the costs for crate, space, and total
        	       outFile<<setfill('.');
        	       outFile<<"Crate volume "<<setprecision(6)<<volumeCrate<<" and cost per crate"<<setw(15)<<setprecision(2)<<"$"<<crateRate<<endl;
        	       outFile<<"Price to ship "<<setprecision(0)<<totalCrate<<" crates"<<setw(15)<<setprecision(2)<<"$"<<priceCrate<<endl;
        	       outFile<<"Storage volume "<<setprecision(6)<<volumeSpace<<" and cost"<<setw(25)<<setprecision(2)<<"$"<<spaceRate<<endl;
        	       outFile<<setprecision(6)<<areaSpace<<" cubic feet room cost"<<setw(25)<<setprecision(2)<<"$"<<priceSpace<<endl;
        	       outFile<<"Total cost "<<setw(50)<<"$"<<priceSpace+priceCrate<<endl;
        	       outFile<<str<<"\n"<<endl;
    	        }
    	        
    	        break;
    	    }
    	    else{
				//Repeat loop if txt file is not valid
    	       cout<<"Error please try again"<<endl;
    	    }  
        }
        
		//OPTION Q - Quit the program
        if (answer == "Q" || answer == "q"){
    	    return 0;
    	}
    	
    }while(inFile.fail());
    
    inFile.close();
    outFile.close();
    
    return 0;
}