/* Name: Stephaney Chang, 2001508920, CS125-1002, Assignment 6
 * Description: This program will get user input by file. It will read the file and 
 * use numbers to calculate length, height, width, volume, area, diagonal, and total volume
 * of all values and print it in a neatly formatted chart. Loop the program until user quits.
 * Input: User input file
 * Output: Chart
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

int main(){
	const int maxCrate = 5; //Minimum dimensions for crate
	const int minCrate = 1; //Maximum dimensions for crate
	const int minRoom = 10; //Minimum dimensions for shipping room
	const int maxRoom = 100; //Maximum dimensions for shipping maxRoom
	
	string ans;
	string type;

	//Variables for shipping space dimensions
	double length = 0.0; 
	double height = 0.0; 
	double width = 0.0; 

	//General calculations for each line
	double volume = 0.0;
	double area = 0.0;
	double diagonal = 0.0;
	
	//Calculations for the total volume of crate and space
	double volumetotalCrate = 0.0;
	double volumetotalSpace = 0.0;
	
	//File variables
    string line;
	string filename; 

	//Input file
	ifstream inFile;
	
	string str = "+-------+---------+--------+--------+------------+--------------+----------+";
	
	//----------------------------------------MAIN BODY LOOP----------------------------------------------------------
   while(true){

    	//Prompt user for input file and print message if sucessful or fail
    	do{
    		cout<<"Please enter the input file name: ";
    		cin>>filename;
    		inFile.open(filename.c_str());

    		//Print message if input file opens successfully
    		if(inFile.is_open()){
    			cout<<"\nFile opened successfully!"<<endl;
    		}
    		else{
    		    cout<<"\nFile not found, please try again"<<endl;
    		};
    	}while(inFile.fail());

    	//Print the first row of the chart
    	cout<<"\n"<<str<<endl;
    	cout<<"| Type"<<setw(10)<<"| Length"<<setw(9)<<"| Width"<<setw(10)<<"| Height";
    	cout<<setw(9)<<"| Volume"<<setw(20)<<"| Surface Area "<<setw(10)<<"| Diagonal |"<<endl;
    	cout<<str<<endl;
    	
    	//INPUT FILE LOOP
    	while(!inFile.eof()){
    		getline(inFile, line);
    		inFile>>type>>length>>width>>height;
    		
    		//Get calculations based on the current input
    		volume = width * height * length;
    	    area = 2*(width*length+height*length+height*width);
    	    diagonal = sqrt(pow(length,2)+pow(width,2)+pow(height,2));
    		
            //Format the column    
            cout<<right<<fixed<<showpoint<<setprecision(1)<<setfill(' ');

            cout<<"| "<<type;
            
            //Determine if the values for length, width, height are valid and print invalid for all rows if not
            if((type=="C") && ((length,width,height<minCrate) || (length,width,height>maxCrate))){
                cout<<setw(10)<<"| Inv";//Length
                cout<<setw(10)<<"| Inv";//Width
                cout<<setw(9)<<"| Inv";//height
                cout<<setw(9)<<"| Inv";//volume
                cout<<setw(13)<<"| Inv";//area
                cout<<setw(15)<<"| Inv"<<setw(7)<<"|"<<endl;//Diagonal
                continue;
            }
            else if((type=="S") && ((length,width,height<=minRoom) || (length,width,height>=maxRoom))){
                cout<<setw(10)<<"| Inv";//length
                cout<<setw(10)<<"| Inv";//width
                cout<<setw(9)<<"| Inv";//height
                cout<<setw(9)<<"| Inv";//volume
                cout<<setw(13)<<"| Inv";//area
                cout<<setw(15)<<"| Inv"<<setw(7)<<"|"<<endl;//Diagonal
                continue;
            }
            else{
                cout<<setw(7)<<"| "<<length;
            };
            
            //Formatting for width column based on number of digits
            if(width<10){
                cout<<setw(7)<<"| " <<width;
            }
            else if(width<100){
                cout<<setw(6)<<"| "<<width;
            }
            else{
                cout<<setw(5)<<"| "<<width;
            };
            
            //Formatting for height column based on number of digits
            if(height<10){
                cout<<setw(6)<<"| "<<height;
            }
            else if(height<100){
                cout<<setw(5)<<"| "<<height;
            }
            else{
                cout<<setw(4)<<"| "<<height;
            };
            
            //Formatting for volume based on number of digits
            if(volume<100){
                cout<<setw(6)<<"| "<<volume;
            }
            else if(volume<=999999){
                cout<<setw(5)<<"| "<<volume;
            }
            else{
                cout<<setw(4)<<"| "<<volume;
            };
            
            //Formatting for area based on number of digits
            if(area<1000){
                cout<<setw(9)<<"| "<<area;
            }
            else if(area<=99999){
                cout<<setw(5)<<"| "<<area;
            }
            else{
                cout<<setw(3)<<"| "<<area;
            };
            
            //Formatting for diagonal based on number of digits
            if (area>100 && diagonal<10){
    	        cout<<setw(10)<<"| "<<diagonal<<setw(7)<<"|"<<endl;
            }
            else if(diagonal<10){
                cout<<setw(11)<<"| "<<diagonal<<setw(7)<<"|"<<endl;
            }
            else if (diagonal<100){
                cout<<setw(9)<<"| "<<diagonal<<setw(7)<<"|"<<endl;
            }
            else{
                cout<<setw(8)<<"| "<<diagonal<<setw(5)<<"|"<<endl;
            };
            
            //Calculate the total volume depending if crate or space
            if(type=="C"){
                volumetotalCrate += volume;
            }
            else if (type=="S"){
                volumetotalSpace += volume;
            };
    	} //END OF FILE LOOP
    	
    	//Print last lines of the chart
    	cout<<str<<endl;

    	//Print the total volume of all inputted volume for crate and storage
    	cout<<"The total crate volume is: "<<right<<setfill('.')<<setw(35)<<volumetotalCrate<<endl;
    	cout<<"The total storage volume is: "<<right<<setfill('.')<<setw(35)<<volumetotalSpace<<endl;

    	inFile.close();

        //Condition to loop the program again.
        do{
            cout<<"Do you want to continue? (Y/N): ";
            cin>>ans;
            
            //Continue if fail, end program if "N"
            if (cin.fail()){
                continue;
            }
            else if(ans=="n" || ans=="N"){
                return 0;
            };
            
            //Break loop if ans is yes
            if(ans=="y" || ans=="Y"){
                break;
            };

        }while(ans!="y" || ans!="Y");
            
        //Loop to the beginning with ans value
        if(ans=="y" || ans=="Y"){
            continue;  
        };
    }
    //----------------------------------------END OF MAIN LOOP---------------------------------------------------------
    
    return 0;
}