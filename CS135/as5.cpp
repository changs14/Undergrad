/* Name: Stephaney Chang, 200150892, CS1351002, Assignment 5 
 * Description: This program will calculate the price to ship crates based on the country the user wants to ship to, the number of crates
 * to be sent and the type of crate (of three types). Taking the total volume of each chosen type of crate, determine the variable costs
 * and the number of cargo needed, and calculate the total cost of the service. 
 * Input: Designated country, number of crates to be sent, type of crate to be sent 
 * Output: A neatly formatted chart with number of times the user picked a type of crate, number of crates needed to ship, the volume of the 
 * crate, and its total cost.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;
const double A_VOLUME = 24.0; //Volume size of crate type a
const double B_VOLUME = 125.0; //Volume size of crate type b 
const double C_VOLUME = 30.0; //Volume size of crate type c

int main(){
	//This variable will store the user's selected country
	string country;

	//These variables will hold the prices per cubic foot for different continents
	double minCost = 0.0;
	double medCost = 0.0;
	double maxCost = 0.0;

	//This variable will get the number of crates the user wants to ship
	int iterationNum = 0;

	//This variable will store the type of crate the user wants to send
	char typeCrate = '\0';
	
	//This variable store the number of times a user chooses crate type a/b/c
	int numA = 0;
	int numB = 0;
	int numC = 0;
	
	//These variables will store total calculations
	double totalCost = 0.0;
	double totalVolume = 0.0;
	double cargoShip = 0.0;

	//-----------------------------------------------------------------------------------------------------

	//Get the input from the user to select a country
	cout<<"Please select the destination continent:\n";
	cout<<"Africa"<<setw(20)<<"(Af/af)\n"<<"Asia"<<setw(22)<<"(As/as)\n";
	cout<<"Austrailia"<<setw(16)<<"(Au/au)\n"<<"Europe"<<setw(20)<<"(Eu/eu)\n";
	cout<<"The Americas"<<setw(14)<<"(Am/am)\n"<<"Quit"<<setw(20)<<"(Q/q)\n"<<endl;

	cin>>country;
	
	//Determine which country the user selected and assign the min, med, and max pricing (which will be determined by volume).
	if(country=="Af" || country=="af"){
		cout<<"Welcome to Africa cargo shipping program."<<endl;
		minCost = 4.0;
		medCost = 5.5;
		maxCost = 8.0;
	}
	else if (country=="As" || country=="as"){
		cout<<"Welcome to Asia cargo shipping program."<<endl;
		minCost = 4.0;
		medCost = 5.5;
		maxCost = 8.0;
	}
	else if (country=="Au" || country=="au"){
		cout<<"Welcome to Austrailia cargo shipping program."<<endl;
		minCost = 7.8;
		medCost = 5.7;
		maxCost = 10.0;

	}
	else if (country=="Eu" || country=="eu"){
		cout<<"Welcome to Europe cargo shipping program."<<endl;
		minCost = 7.8;
		medCost = 5.7;
		maxCost = 10.0;
	}
	else if (country=="Am" || country=="am"){
		cout<<"Welcome to The Americas cargo shipping program."<<endl;
		minCost = 2.5;
		medCost = 3.5;
		maxCost = 6.0;
	}
	else if (country=="Q" || country=="q"){
		cout<<"Thank you for using this program. Goodbye! :)"<<endl;
		return 0;
	}
	else{
		cout<<"Error, invalid input. Please try again and select a correct value.\n"<<endl;\
		return 0;
	};

	//-----------------------------------------------------------------------------------------------------

    //Ask user for how many crates they want to send. This will be used to loop how many times the user wants to choose a crate type.
    cout<<"\nHow many crates will be sent?"<<endl;
    cin>>iterationNum;
    cout<<endl;

    //If the input is not a number, loop the question until input is correct.
    while(cin.fail()){
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Enter a number please. How many crates will be sent?"<<endl;
        cin>>iterationNum;
        cout<<endl;
    }
    
    //-----------------------------------------------------------------------------------------------------

	//Ask user what type of crate they want to send using the number of crates that they want to send in iterationNum
    for(int i = 0; i<iterationNum; i++){
	    cout<<"What type of crate do you want to send? (a/b/c) just the first character will be accepted."<<endl;
    	cin>>typeCrate;
	    cout<<endl;
	    
	    //If input not a/b/c, loop the question until the input is correct.
	    while(typeCrate!='a' && typeCrate!='b' && typeCrate!='c'){
	        if(typeCrate!='a' && typeCrate!='b' && typeCrate!='c'){
	            cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Error, the selected crate type is unavailable. What type of crate do you want to send? (a/b/c) just the first characters will be accepted"<<endl;
                cin>>typeCrate;
                cout<<endl;
	        }
	        else{
	            break;
	        };
	  	}
	   
	   //Determine based on the typeCrate, how many times the user chooses a/b/c and store in num variables.
	   switch(typeCrate){
	       case 'a':
	            numA+=1;
	            break;
	       case 'b':
	            numB+=1;
	            break;
	       case 'c':
	            numC+=1;
	            break;
	       default:
	            cout<<"Error."<<endl;
	    }; 
	}
	
	//-----------------------------------------------------------------------------------------------------

    //Calculate the total volume using fixed volume rate and number of a/b/c crates the user picked.
    totalVolume = (numA*A_VOLUME)+(numB*B_VOLUME)+(numC*C_VOLUME);
    
    //Calculate the total cargo ships needed and round to the nearest whole number
    cargoShip = round(totalVolume/300);
   
    //Determine the pricing of the cargo ship by multiplying totalVolume, variable cost, $200, and adding number of cargo.
    if(totalVolume<=40){
        totalCost = totalVolume*minCost+cargoShip*200;
    }
    else if(totalVolume>40 && totalVolume<=80){
        totalCost = totalVolume*medCost+cargoShip*200;
    }
    else{
        totalCost=totalVolume*maxCost+cargoShip*200;
    };
	   
	//-----------------------------------------------------------------------------------------------------

	//Format and print the chart
	
	string str = "+--------------+--------+ ";
	
	if(cargoShip>=10){
	    cout<<"Error. Number of cargo ships exceed what is available."<<endl; //Cannot send out more than 10 cargo
	}
	else{
	cout<<str<<endl;
	cout<<"|# TYPE"<<setw(9)<<"a |"<<setw(2)<<numA<<setw(7)<<"|"<<endl;
	cout<<str<<endl;
	cout<<"|# TYPE"<<setw(9)<<"b |"<<setw(2)<<numB<<setw(7)<<"|"<<endl;
	cout<<str<<endl;
	cout<<"|# TYPE"<<setw(9)<<"c |"<<setw(2)<<numC<<setw(7)<<"|"<<endl;
	cout<<str<<endl;
	cout<<"|# Cargo Ships |"<<setw(2)<<cargoShip<<setw(7)<<"|"<<endl;
	cout<<str<<endl;
	cout<<"| Total Volume |"<<setw(7)<<fixed<<showpoint<<setprecision(1)<<totalVolume<<setw(2)<<"|"<<endl;
	cout<<str<<endl;
	cout<<"| Total Costs  |"<<setw(7)<<fixed<<showpoint<<setprecision(1)<<totalCost<<setw(2)<<"|"<<endl;
	cout<<str<<endl;
	};

	return 0;
	
}
