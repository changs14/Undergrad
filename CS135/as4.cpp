/* Name: Stephaney Chang, 2001508920, CS135-1002, Assignment 4
 * Description: This program will get input for crate and space length, width and height and, 
 * print an error message for invalid inputs. Calculate area, volume, diagonal and num of crates that 
 * can fit in space. Then calculate the pricing based on the volume range for both crate and space.
 * Input: Crate length width and height, space length width and height.
 * Output: Table with input data and calculations, and pricing of crate and space
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

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
	//Variables for space width, height, and length
	double spaceW=0.0;
	double spaceH=0.0;
	double spaceL=0.0;

	//Variables for crate width, height, and length
	double crateW=0.0;
	double crateH=0.0;
	double crateL=0.0;

	//Variables for the crate and space pricing
	double priceCrate=0.0;
	double priceSpace=0.0;

	//GET INPUT FOR SHIPPING CRATE

	cout<<"SHIPPING CRATE"<<endl;

	//Prompt user for length of crate
	cout<<"Enter length of the shipping crate\n**";
	cin>>crateL;

	//Print error message if user input is not a double or bigger than min or max.
	if (cin.fail() || crateL<MIN_CRATE || crateL>MAX_CRATE){
		cout<<"Error - Invalid shipping crate length!"<<endl;
		return 0;
	}
	else{
	    cout<<endl;
	};

	//Prompt user for width of crate
	cout<<"Enter width of the shipping crate\n**";
	cin>>crateW;

	//Print error message if input is invalid
	if (cin.fail() || crateW<MIN_CRATE || crateW>MAX_CRATE){
		cout<<"Error - Invalid shipping crate width!"<<endl;
		return 0;
	}
	else{
		cout<<endl;
	};

	//Prompt user for height of crate
	cout<<"Enter height of the shipping crate\n**";
	cin>>crateH;

	//Print error message if input is invalid
	if (cin.fail() || crateH<MIN_CRATE || crateH>MAX_CRATE){
		cout<<"Error - Invalid shipping crate height!"<<endl;
		return 0;
	}
	else{
		cout<<endl;
	};

	//Calculations for crate volume, area, and diagonal
	double volumeCrate = crateW * crateH * crateL;
	double areaCrate = 2*(crateW*crateL+crateH*crateL+crateH*crateW);
	double diagonalCrate = sqrt(pow(crateL,2)*pow(crateW,2)*pow(crateH,2));

	//GET INPUT FOR STORAGE SPACE

	cout<<"\nSTORAGE SPACE"<<endl;

	//Prompt user for storage length 
	cout<<"Enter length of storage space\n**";
	cin>>spaceL;

	//Print error message if input is invalid
	if (cin.fail() || spaceL<MIN_ROOM || spaceL>MAX_ROOM){
		cout<<"Error - Invalid shipping space length!"<<endl;
		return 0;
	}
	else{
		cout<<endl;
	};
 
 	//Prompt user for storage width
	cout<<"Enter width of storage space\n**";
	cin>>spaceW;

	//Print error message if input is invalid
	if (cin.fail() || spaceW<MIN_ROOM || spaceW>MAX_ROOM){
		cout<<"Error - Invalid shipping space width!"<<endl;
		return 0;
	}
	else{
		cout<<endl;
	};

	//Prompt user for storage height
	cout<<"Enter height of the storage space\n**";
	cin>>spaceH;

	//Print error message if input is invalid
	if (cin.fail() || spaceH<MIN_ROOM || spaceH>MAX_ROOM){
		cout<<"Error - Invalid shipping space height!"<<endl;
		return 0;
	}
	else{
		cout<<endl;
	};
	
	//Calculations for space volume, area, and diagonal
	double volumeSpace = spaceW * spaceH * spaceL;
	double areaSpace= 2*(spaceW*spaceL+spaceH*spaceL+spaceH*spaceW);
	double diagonalSpace = sqrt(pow(spaceL,2)*pow(spaceW,2)*pow(spaceH,2));

	//Calculate the total amount of crates that can fit in storage space
	int totalCrate = floor(spaceL/crateL)*floor(spaceW/crateW)*floor(spaceH/crateH);

	//PRINT THE CHART

	//Variable stores the chart outline
	string str = "+-------+---------+--------+--------+------------+--------------+----------+";

	//Print the first row
	cout<<str<<endl;
	cout<<"| TYPE  | LENGTH  | WIDTH  | HEIGHT | VOLUME     | SURFACE AREA | DIAGONAL |"<<endl;

	//Formatting for subsequent rows
    cout<<left<<fixed<<showpoint<<setprecision(1);

	//Print second (crate) row
	cout<<str<<endl;
	cout<<"| Crate | ";
	cout<<setw(8) << crateL<<"| ";
	cout<<setw(7)<<crateW<<"| ";
	cout<<setw(7)<<crateH<<"| ";
	cout<<setw(11)<<volumeCrate<<"| ";
	cout<<setw(13)<<areaCrate<<"| ";
	cout<<setw(9)<<diagonalCrate<<"|"<<endl;

	//Print third (space) row
	cout<<"| Space | ";
	cout<<setw(8) << spaceL<<"| ";
	cout<<setw(7)<<spaceW<<"| ";
	cout<<setw(7)<<spaceH<<"| ";
	cout<<setw(11)<<volumeSpace<<"| ";
	cout<<setw(13)<<areaSpace<<"| ";
	cout<<setw(9)<<diagonalSpace<<"|"<<endl;
	cout<<str<<endl;

	//Print number of crates that fit in the storage space
	cout<<"\n"<<totalCrate<<" crates can fit in the storage space.\n"<<endl;

	//PRICING OF CRATE AND SPACE

    //Formatting to print the pricing for crate and space.
    cout<<right<<fixed<<showpoint<<setfill('.');

	//PRICING FOR CRATE

	//Determine the rate of crate based on the volume and print the shipping rate for crate
	if(volumeCrate>=1 && volumeCrate<=40){
		priceCrate = totalCrate*S_CRATE_RATE;
		cout<<"Crate volume "<<setprecision(6)<<volumeCrate<<" cost";
	    
	    //Check the num of digits in volumeCrate and format setw based on it
	    if (volumeCrate<=9){
	        cout<<setprecision(2)<<setw(24)<<"$"<<S_CRATE_RATE<<" per crate"<<endl;
	    }
	    else{
	        cout<<setprecision(2)<<setw(23)<<"$"<<S_CRATE_RATE<<" per crate"<<endl;
	    };
	}
	else if (volumeCrate>=40 && volumeCrate<=80){
		priceCrate = totalCrate*M_CRATE_RATE;
		cout<<"Crate volume "<<setprecision(6)<<volumeCrate<<" cost";
		cout<<setprecision(2)<<setw(23)<<"$"<<M_CRATE_RATE<<" per crate"<<endl;
	}
	else{
		priceCrate = totalCrate*L_CRATE_RATE;
		cout<<"Crate volume "<<setprecision(6)<<volumeCrate<<" cost ";
		
		//Check num of digits to determine which setw to use
	    if(volumeCrate<100){
	        cout<<setprecision(2)<<setw(22)<<"$"<<S_CRATE_RATE<<" per crate"<<endl;
	    }
	    else{
		    cout<<setprecision(2)<<setw(21)<<"$"<<S_CRATE_RATE<<" per crate"<<endl;
	    };

	};
	
	//Determine setw based on number of digits in variable totalCrate and print the price of shipping
	if(totalCrate<=9){
	    cout<<"Price to ship "<<totalCrate<<" crates"<<setprecision(2)<<setw(28)<<"$"<<priceCrate<<endl;
	}
	else if(totalCrate>=10 && totalCrate<=99){
	    cout<<"Price to ship "<<totalCrate<<" crates"<<setprecision(2)<<setw(27)<<"$"<<priceCrate<<endl;
	}
	else if(totalCrate>=100 && totalCrate<=999){
	    cout<<"Price to ship "<<totalCrate<<" crates"<<setprecision(2)<<setw(26)<<"$"<<priceCrate<<endl;
	}
	else if(totalCrate>=1000 && totalCrate<=9999){
	    cout<<"Price to ship "<<totalCrate<<" crates"<<setprecision(2)<<setw(25)<<"$"<<priceCrate<<endl;
	}
	else if(totalCrate>=10000 && totalCrate<=99999){
	    cout<<"Price to ship "<<totalCrate<<" crates"<<setprecision(2)<<setw(24)<<"$"<<priceCrate<<endl;
	}
	else{
	    cout<<"Price to ship "<<totalCrate<<" crates"<<setprecision(2)<<setw(22)<<"$"<<priceCrate<<endl;
	};

	//PRICING FOR SPACE
	
	//Determine the rate for shipping space based on its volume and print the shipping rate
	if(volumeSpace>=1000 && volumeSpace<=250000){
		priceSpace = volumeSpace*S_ROOM_RATE;
		
		//Check num of digits in volumeSpace to determine how far to setw
		if(volumeSpace<=9999){
		    cout<<"\nStorage room with volume "<<setprecision(6)<<volumeSpace<<" cost";
		    cout<<setprecision(2)<<setw(9)<<"$"<<S_ROOM_RATE<<" per cubic foot"<<endl;
		}
		else if(volumeSpace>=10000 && volumeSpace<=99999){
		    cout<<"\nStorage room with volume "<<setprecision(6)<<volumeSpace<<" cost";
		    cout<<setprecision(2)<<setw(8)<<"$"<<S_ROOM_RATE<<" per cubic foot"<<endl;
		}
		else{
		    cout<<"\nStorage room with volume "<<setprecision(6)<<volumeSpace<<" cost";
		    cout<<setprecision(2)<<setw(7)<<"$"<<S_ROOM_RATE<<" per cubic foot"<<endl;
		};
		
	}
	else if (volumeSpace>=250000 && volumeSpace<=500000){
		priceSpace = volumeSpace*M_ROOM_RATE;
		cout<<"\nStorage room with volume "<<setprecision(6)<<volumeSpace<<" cost ";
		cout<<setprecision(2)<<setw(9)<<"$"<<M_ROOM_RATE<<" per cubic foot"<<endl;
	}
	else if(volumeSpace>=500000 && volumeSpace<=750000){
		priceSpace = volumeSpace*L_ROOM_RATE;
		cout<<"\nStorage room with volume "<<setprecision(6)<<volumeSpace<<" cost";
		cout<<setprecision(2)<<setw(9)<<"$"<<L_ROOM_RATE<<" per cubic foot"<<endl;
	}
	else{
		priceSpace = volumeSpace*XL_ROOM_RATE;
		cout<<"\nStorage room with volume "<<setprecision(6)<<volumeSpace<<" cost";
		cout<<setprecision(2)<<setw(6)<<"$"<<XL_ROOM_RATE<<" per cubic foot"<<endl;
	};
	
	//Determine how far to setw based on the number of digits in variable areaSpace and print the pricing for space
	if(areaSpace<=999){
	    cout<<setprecision(6)<<areaSpace<<" cubic feet storage room cost"<<setprecision(2)<<setw(11)<<"$"<<priceSpace<<endl;
	}
	else if(areaSpace>=1000 && areaSpace<=9999){
	    cout<<setprecision(6)<<areaSpace<<" cubic feet storage room cost"<<setprecision(2)<<setw(10)<<"$"<<priceSpace<<endl;
	}
	else{
	    cout<<setprecision(6)<<areaSpace<<" cubic feet storage room cost"<<setprecision(2)<<setw(9)<<"$"<<priceSpace<<endl;
	};

	//Print the total cost of shipment.
	cout<<"\nTotal Cost"<<setw(40)<<"$"<<priceSpace+priceCrate<<endl;

    return 0;

}