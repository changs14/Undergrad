/* Name: Stephaney Chang, 2001508920, CS1351002, Assignment 8
 * Description: Using functions
 * Input: User choice and text file
 * Output: Crate output file - crate input & calculations
           Storage output file - storage input & calculations
           Total output file - All input data, volume, and total costs
*/

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

const double MIN_CRATE = 1;	 // Minimum size a shipping crate can be (in feet)
const double MAX_CRATE = 5;	 // Maximum size a shipping crate can be (in feet)
const double MIN_ROOM = 10;	 // Minimum size a storage room can be (in feet)
const double MAX_ROOM = 100; // Maximum size a storage room can be (in feet)

const double S_CRATE_RATE = 2.5; // Cost to ship crate 1-40 cubic feet
const double M_CRATE_RATE = 3.0; // Cost to ship crate 40-80 cubic feet
const double L_CRATE_RATE = 3.5; // Cost to ship crate 80+ cubic feet
const double S_ROOM_RATE = 0.12; // Cost to ship in room 1,000-250,000 cubic feet
const double M_ROOM_RATE = 0.09; // Cost to ship in room 250,000-500,000 cubic feet
const double L_ROOM_RATE = 0.07; // Cost to ship in room 500,000-750,000 cubic feet
const double XL_ROOM_RATE = 0.05; // Cost to ship in room 750,000+ cubic feet

const string str = "------------+------------+------------+------------+------------+------------+------------+------------+";

void showMenu(void);
bool check_string(string str);

void crateCalculations(void);
void storageSpaceCalculations(void);
void totalVolumeAndCostCalculations(void);
void displayFile(string line);

double CrateVolume(double crateLength, double crateWidth, double crateHeight);
double CrateSurfaceArea(double crateLength, double crateWidth, double crateHeight);
double CrateDiagonal(double crateLength, double crateWidth, double crateHeight);

double StorageVolume(double storageLength, double storageWidth, double storageHeight);
double StorageSurfaceArea(double storageLength, double storageWidth, double storageHeight);
double StorageDiagonal(double storageLength, double storageWidth, double storageHeight);

double TotalCrates(double crateLength, double crateWidth, double crateHeight, double storageLength, double storageWidth, double storageHeight);
double CrateMultiplier(double crateVolume);
double storageMultiplier(double storageVolume);
double crateCost(double total_crates, double crate_multiplier);
double storageCost(double storageVolume, double storage_multiplier);

int main(){
	string crates_file;
	bool repeat=true;
	char selection;
	
	do{
		showMenu(); //Display options for user
		cin>>selection;

		switch (selection){
		case 'D':
		case 'd':
			cout << "You selected D" << endl;
			do{
			    cout<<"Enter file name: ";
        	    cin>>crates_file;
        	    displayFile(crates_file);
			}while(cin.fail());
			break;
		case 'C':
		case 'c':
			cout << "You selected C" << endl;
			crateCalculations();
			break;
		case 'S':
		case 's':
			cout << "You selected S" << endl;
			storageSpaceCalculations();
			break;
		case 'T':
		case 't':
			cout << "You selected T" << endl;
			totalVolumeAndCostCalculations();
			break;
		case 'Q':
		case 'q':
			cout << "You selected to quit the program" << endl;
			repeat=false;
			break;
		default:
			cout << "Invalid selection" << endl;
			break;
		} //switch structure close
		
		continue; 
		
	} while (repeat);

	return 0;
}

/* Function checks file input and returns string value or error if not a num.
 * @param str 
 * @return bool - true or false
 */
bool check_string(string str){
	bool ret = true;

	for (unsigned int i = 0; i < str.length(); i++){
		if ((str[i] >= 48 && str[i] <= 57) ||
			(str[i] == 46)){
			continue;
		}
		else{
			ret = false;
		}
	}

	return ret;
}

void showMenu(){
		cout<<"***************************************"<<endl;
        cout<<"\nD/d - Display file data\nC/c - Crate calculations\nS/s - Storage space calculations";
        cout<<"\nT/t - Total Volume and Cost Calculations\nQ/q - Quit the program"<<endl;
        cout<<"\n***************************************"<<endl;
}

/* Opens user inputted file and prints it in a new file
 * @param line 
 */
void displayFile(string line){
    ifstream inFile;
    ofstream outFile;
    
    inFile.open(line.c_str()); //Open file
    	    
    if (inFile.is_open()){
        cout<<"File opened successfully!"<<endl;
        	        
        while(!inFile.eof()){
            getline(inFile, line); //Read txt
            cout<<line<<endl;
        }
    }
}

/* Calculates the volume of crate using length width and height
 * @param crateLength @param crateWidth @param crateHeight 
 * @return double 
 */
double CrateVolume(double crateLength, double crateWidth, double crateHeight){
    double volumeCrate = crateLength * crateWidth * crateHeight;
	return volumeCrate;  
}

/* Calculates surface area of crate using length width and height
 * @param crateLength @param crateWidth @param crateHeight 
 * @return double 
 */
double CrateSurfaceArea(double crateLength, double crateWidth, double crateHeight){
    double areaCrate = 2*(crateWidth*crateLength+crateHeight*crateLength+crateHeight*crateWidth);
	return areaCrate;  
}

/* Calculates the diagonal of crate using length width and height
 * @param crateLength @param crateWidth @param crateHeight 
 * @return double 
 */
double CrateDiagonal(double crateLength, double crateWidth, double crateHeight){
    double diagonalCrate = sqrt(pow(crateLength,2)+pow(crateWidth,2)+pow(crateHeight,2));
	return diagonalCrate; 
}

/* Calculate the storage's volume using its length width and height
 * @param storageLength @param storageWidth @param storageHeight 
 * @return double 
 */
double StorageVolume(double storageLength, double storageWidth, double storageHeight){
    double volumeStorage= storageLength * storageHeight * storageWidth;
	return volumeStorage;  
}

/* Calculate the surfae area of the storage space using length width and height 
 * @param storageLength @param storageWidth @param storageHeight 
 * @return double 
 */
double StorageSurfaceArea(double storageLength, double storageWidth, double storageHeight){
    double areaStorage = 2*(storageWidth*storageLength+storageHeight*storageLength+storageHeight*storageWidth);
	return areaStorage; 
}

/* Calculate the diagonal of storage space using its length width and height
 * @param storageLength @param storageWidth @param storageHeight 
 * @return double 
 */
double StorageDiagonal(double storageLength, double storageWidth, double storageHeight){
    double diagonalStorage = sqrt(pow(storageLength,2)+pow(storageWidth,2)+pow(storageHeight,2));
	return diagonalStorage; 
}

/* Calculate the total amount of crate that can fit in storage space
 * @param crateLength @param crateWidth @param crateHeight 
 * @param storageLength @param storageWidth @param storageHeight 
 * @return double 
 */
double TotalCrates(double crateLength, double crateWidth, double crateHeight, double storageLength, double storageWidth, double storageHeight){
    double totalCrate = floor(storageLength/crateLength)*floor(storageWidth/crateWidth)*floor(storageHeight/crateHeight);
	return totalCrate;
}

/* Calculate the rate of shipping based on the volume of crate 
 * @param crateVolume 
 * @return double 
 */
double CrateMultiplier(double crateVolume){
    double crateRate = 0.0;
    if(crateVolume>=1 && crateVolume<=40){
        crateRate = S_CRATE_RATE;
    }
    else if (crateVolume>=40 && crateVolume<=80){
        crateRate =M_CRATE_RATE;
    }
    else{
        crateRate = L_CRATE_RATE;
    };
    
	return crateRate; 
}

/* Calculate the rate of shipping based on volume of storage
 * @param storageVolume 
 * @return double 
 */
double StorageMultiplier(double storageVolume){
    double storageRate = 0.0;
    if(storageVolume>=1000 && storageVolume<=250000){
	    storageRate = S_ROOM_RATE;
    }
    else if (storageVolume>=250000 && storageVolume<=500000){
        storageRate = M_ROOM_RATE;
    }
    else if(storageVolume>=500000 && storageVolume<=750000){
        storageRate = L_ROOM_RATE;
    }
    else{
        storageRate = XL_ROOM_RATE;
    };
    
	return storageRate; 
}

/* Calculate the total cost of the crates based on rate and amount of crates
 * @param total_crates @param crate_multiplier 
 * @return double 
 */
double CrateCost(double total_crates, double crate_multiplier){
    double totalCrateCost = total_crates * crate_multiplier;
	return totalCrateCost; 
}

/* Calculate the total cost of storage space based on rate and volume of space
 * @param storageVolume @param storage_multiplier 
 * @return double 
 */
double StorageCost(double storageVolume, double storage_multiplier){
    double totalStorageCost = storageVolume * storage_multiplier;
	return totalStorageCost; 
}

/* Calculates and prints the total cost of crate and volume based on file Dataset */
void totalVolumeAndCostCalculations(void){
    ofstream outFile;
    ifstream inFile;
    
    string line;
    string filename;
    string crateL, crateW, crateH, spaceL, spaceW, spaceH; //Store data from input file
    
    bool retValue; //Stores bool value if file data is num
    
    int count =1; //Stores current line program is reading
    
    do{
	    cout<<"Enter file name: "; //Get user inputted file
        cin>>filename;
        inFile.open(filename.c_str());
        	    
        //Open file and read txt
        if (inFile.is_open()){
            cout<<"#################################\nFile opened successfully!\n#################################"<<endl;
            outFile.open("total_volume_cost_output.txt");
                    	        
            while(!inFile.eof()){
                //Print the first row
                outFile<<"Dataset: "<<count<<endl;
                count++;
                outFile<<fixed<<showpoint<<setprecision(1)<<setfill(' ');
                outFile<<"LC"<<setw(10)<<"WC"<<setw(10)<<"HC"<<setw(10)<<"LS"<<setw(10)<<"WS"<<setw(10)<<"HS"<<setw(10)<<"CV";
                outFile<<setw(10)<<"CS"<<setw(10)<<"CD"<<setw(10)<<"SV"<<setw(10)<<"SS"<<setw(10)<<"SD"<<setw(15)<<"Total Crate"<<endl;
                
    	       getline(inFile, line);
    	       inFile>>crateL; //Get crate length
    	       
    	       //Errors for crate length
    	       retValue = check_string(crateL);
    	       if (retValue == true){
    	           outFile<<stod(crateL);
    	       }
    	       else{
    	           outFile<<0.0<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
    	           continue;
    	       }
                if (stod(crateL)<MIN_CRATE || stod(crateL)>MAX_CRATE){
                    outFile<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
                    continue;
                }
                
                inFile>>crateW; //Get crate width
                
                //Errors for crate width
                retValue = check_string(crateW);
    	       if (retValue == true){
    	           outFile<<setw(10)<<stod(crateW);
    	       }
    	       else{
    	           inFile.ignore(100, '\n');
    	           outFile<<setw(10)<<0.0<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
    	           continue;
    	       }
                if(stod(crateW)<MIN_CRATE || stod(crateW)>MAX_CRATE){
                	outFile<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
                	continue;
                }
                
                inFile>>crateH; //Get crate height
                
                 //Errors for crate height
                retValue = check_string(crateH);
    	       if (retValue == true){
    	           outFile<<setw(10)<<stod(crateH);
    	       }
    	       else{
    	           outFile<<setw(10)<<0.0<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
    	           continue;
    	       }
                if (stod(crateH)<MIN_CRATE || stod(crateH)>MAX_CRATE){
                    outFile<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
                    continue;
                }

                inFile>>spaceL; //Get space length
                
                //Errors for space length
               retValue = check_string(spaceL);
    	       if (retValue == true){
    	           outFile<<setw(10)<<stod(spaceL);
    	       }
    	       else{
    	           outFile<<setw(10)<<0.0<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
    	           continue;
    	       }
                if(stod(spaceL)<MIN_ROOM || stod(spaceL)>MAX_ROOM){
                	outFile<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
                	continue;
                }
                
                inFile>>spaceW; //Get space width
                
                //Errors for space width
                retValue = check_string(spaceW);
                if (retValue == true){
    	           outFile<<setw(10)<<stod(spaceW);
    	       }
    	       else{
    	           outFile<<setw(10)<<0.0<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
    	           continue;
    	       }
    	       if (stod(spaceW)<MIN_ROOM || stod(spaceW)>MAX_ROOM){
                    outFile<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
    	           continue;
                }
                	
                inFile>>spaceH; //Get space height
                
                //Errors for space height
                retValue = check_string(spaceH);
                if (retValue == true){
    	           outFile<<setw(10)<<stod(spaceH);
    	       }
    	       else{
    	           outFile<<setw(10)<<0.0<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
    	           continue;
    	       }
                if(stod(spaceH)<MIN_ROOM || stod(spaceH)>MAX_ROOM){
                	outFile<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
                	continue;
                }
                
                //Calculate: crate volume, area, rate, total, cost, diagonal
                double crateV = CrateVolume(stod(crateL), stod(crateW), stod(crateH));
                double crateA = CrateSurfaceArea(stod(crateL), stod(crateW), stod(crateH));
                double crateR = CrateMultiplier(crateV);
                double crateT = TotalCrates(stod(crateL), stod(crateW), stod(crateH), stod(spaceL), stod(spaceW), stod(spaceH));
                double crateC = CrateCost(crateT, crateR);
                double crateD = CrateDiagonal(stod(crateL), stod(crateW), stod(crateH));
                
                //Calculate: storage volume, area, rate, cost, diagonal
                double spaceV = StorageVolume(stod(spaceL), stod(spaceW), stod(spaceH));
                double spaceA = StorageSurfaceArea(stod(spaceL), stod(spaceW), stod(spaceH));
                double spaceR = StorageMultiplier(spaceV);
                double spaceC = StorageCost(spaceV, spaceR);
                double spaceD = StorageDiagonal(stod(spaceL), stod(spaceW), stod(spaceH));
                
                //Output the calculations in chart
                outFile<<setw(10)<<crateV<<setw(10)<<crateA<<setw(10)<<crateD<<setw(10)<<spaceV<<setw(10)<<spaceA<<setw(10)<<spaceD<<setw(10)<<crateT;
                outFile<<endl;
                
                outFile<<str<<setfill('.')<<endl;
                //Print all calcualtions of crate and storage space
                outFile<<"Crate volume "<<setprecision(6)<<crateV<<" and cost per crate"<<setw(15)<<setprecision(2)<<"$"<<crateR<<endl;
                outFile<<"Price to ship "<<static_cast<int>(crateT)<<" crates"<<setw(15)<<setprecision(2)<<"$"<<crateC<<endl;
                outFile<<"Storage volume "<<setprecision(6)<<spaceV<<" and cost"<<setw(25)<<setprecision(2)<<"$"<<spaceR<<endl;
                outFile<<setprecision(6)<<spaceA<<" cubic feet room cost"<<setw(25)<<setprecision(2)<<"$"<<spaceC<<endl;
                outFile<<"Total cost "<<setw(50)<<"$"<<crateC + spaceC<<"\n"<<str<<endl;
            }
            
            inFile.close();
        	outFile.close();
        }
	}while(cin.fail());
}

/* Takes only the storage data and calculates volume, area, diagonal and print neatly */
void storageSpaceCalculations(void){
    ofstream outFile;
    ifstream inFile;
    
    string line;
    string filename;
    string spaceL, spaceW, spaceH, crateL, crateW, crateH; //Stores file data as a string
    
    bool retValue; //Stores bool value if file data is a num
    
    int count = 1; //Current line program is reading
    
    do{
	    cout<<"Enter file name: ";
        cin>>filename;
        inFile.open(filename.c_str());
        	    
        //Open file and read txt
        if (inFile.is_open()){
            cout<<"#################################\nFile opened successfully!\n#################################"<<endl;
            outFile.open("storage_space_output.txt");
            
            while(!inFile.eof()){
                //Print storage space data and calculations
            	outFile<<"Dataset: "<<count<<endl;
            	count++;
                outFile<<fixed<<showpoint<<setprecision(1);
                outFile<<"LS"<<setw(10)<<"WS"<<setw(10)<<"HS"<<setw(10)<<"SV"<<setw(10)<<"SS"<<setw(10)<<"SD"<<endl;
                
                getline(inFile, line);
                inFile>>crateL>>crateW>>crateH; //Read first three values and ignore
    
                inFile>>spaceL; //Get space length
                
                //Errors for space length
                retValue = check_string(spaceL);
                if (retValue == true){
    	           outFile<<stod(spaceL);
                }
                else{
    	           inFile.clear();
    	           inFile.ignore(100, '\n');
    	           outFile<<setw(10)<<0.0<<setw(35)<<"Error - Invalid space length!\n"<<str<<endl;
    	           continue;
                }
                if(stod(spaceL)<MIN_ROOM || stod(spaceL)>MAX_ROOM){
                    outFile<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
                	continue;
                }
                
                inFile>>spaceW; //Get space width
                
                //Errors for space width
                retValue = check_string(spaceW);
                if (retValue == true){
    	           outFile<<setw(10)<<stod(spaceW);
    	       }
    	       else{
    	           outFile<<setw(10)<<0.0<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
    	           continue;
    	       }
    	       if (stod(spaceW)<MIN_ROOM || stod(spaceW)>MAX_ROOM){
                    outFile<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
    	           continue;
                }
                
                inFile>>spaceH; //Get space height
                
                //Errors for space height
                retValue = check_string(spaceH);
    	       if (retValue == true){
    	           outFile<<setw(10)<<stod(spaceH);
    	       }
    	       else{
    	           outFile<<setw(10)<<0.0<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
    	           continue;
    	       }
                if(stod(spaceH)<MIN_ROOM || stod(spaceH)>MAX_ROOM){
                    outFile<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
                    continue;
                }
                
                //Calculate storage space volume, area, diagonal
                double spaceV = StorageVolume(stod(spaceL), stod(spaceW), stod(spaceH));
                double spaceA = StorageSurfaceArea(stod(spaceL), stod(spaceW), stod(spaceH));
                double spaceD = StorageDiagonal(stod(spaceL), stod(spaceW), stod(spaceH));
                
                //Output input and calculations in chart
                outFile<<setw(10)<<spaceV<<setw(10)<<spaceA<<setw(10)<<spaceD<<"\n"<<str<<endl;
            }
            
            inFile.close();
        	outFile.close();
        }
	}while(cin.fail());
}

/* Takes crate data only, calculates volume, area, and diagonal, and prints neatly as a chart */
void crateCalculations(void){
    ofstream outFile;
    ifstream inFile;
    
    string line;
    string filename;
    string crateL, crateW, crateH; //Stores first three data of file
    
    bool retValue; //Determines if crate data is a num
    
    int count = 1; //Current line program is reading
    
    do{
	    cout<<"Enter file name: "; //Get user input
        cin>>filename;
        inFile.open(filename.c_str());
        	    
        //Open file and read txt
        if (inFile.is_open()){
            cout<<"#################################\nFile opened successfully!\n#################################"<<endl;
            outFile.open("crate_output.txt");
                    	        
            while(!inFile.eof()){
                //Print the first row
                outFile<<"Dataset: "<<count<<endl;
                count++;
                outFile<<fixed<<showpoint<<setprecision(1);
                outFile<<"LC"<<setw(10)<<"WC"<<setw(10)<<"HC"<<setw(10)<<"CV"<<setw(10)<<"CS"<<setw(10)<<"CD"<<endl;
                
                getline(inFile, line);
                inFile>>crateL; //Get crate length
    	        
    	       //Errors for crate length
    	       retValue = check_string(crateL); 
    	       if (retValue == true){
    	           outFile<<stod(crateL);
    	       }
    	       else{
    	           outFile<<0.0<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
    	           continue;
    	       }
                if (stod(crateL)<MIN_CRATE || stod(crateL)>MAX_CRATE){
                    outFile<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
                    continue;
                }
                
                inFile>>crateW;//Get crate width
                
                //Errors for crate width
                retValue = check_string(crateW);
                if (retValue == true){
    	           outFile<<setw(10)<<stod(crateW);
    	       }
    	       else{
    	           inFile.clear();
    	           inFile.ignore(100, '\n');
    	           outFile<<setw(10)<<0.0<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
    	           continue;
    	       }
    	       if (stod(crateW)<MIN_CRATE || stod(crateW)>MAX_CRATE){
                    outFile<<setw(10)<<0.0<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
                    continue;
    	       }
 
                inFile>>crateH; //Get crate height
                
                //Errors for crate height
                retValue = check_string(crateH);
                if (retValue == true){
    	           outFile<<setw(10)<<stod(crateH);
    	       }
    	       else{
    	           outFile<<setw(10)<<0.0<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
    	           continue;
    	       }
    	       if (stod(crateH)<MIN_CRATE || stod(crateH)>MAX_CRATE){
                    outFile<<setw(35)<<"-> Error, invalid crate length!\n"<<str<<endl;
        	        continue;
    	       }
                
                //Calculate crate volume, area, diagonal
                double crateV = CrateVolume(stod(crateL), stod(crateW), stod(crateH));
                double crateA = CrateSurfaceArea(stod(crateL), stod(crateW), stod(crateH));
                double crateD = CrateDiagonal(stod(crateL), stod(crateW), stod(crateH));
                    
                //Print all crate data and calculations in a chart
                outFile<<setw(10)<<crateV<<setw(10)<<crateA<<setw(10)<<crateD<<"\n"<<str<<endl;
            }
            
            inFile.close();
        	outFile.close();
        }
	}while(cin.fail());
}