/* Name: Stephaney Chang, 2001508920, CS135-1002, Assignment 3
 * Description: Get input for crate and space length, width and height. Then calculate the
 * volume, area, diagonal, and number of crates that can fit in the space and print as a table.
 * Input: Crate legnth width and height, space length width and height.
 * Output: Table with crate and space length, width, height volume,
 * area, diagonal and how many crates can fit in the space.

*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(){
	//Variables for space
	double spaceW=0.0;
	double spaceH=0.0;
	double spaceL=0.0;

	//Variables for crate
	double crateW=0.0;
	double crateH=0.0;
	double crateL=0.0;

	string str ="+-------+---------+--------+--------+------------+--------------+----------+";

	//Ask user for input for shipping crate
	cout<<"SHIPPING CRATE"<<endl;

	cout<<"Enter length of the shipping crate\n**";
	cin>>crateL;
	cout<<endl;

	cout<<"Enter width of the shipping crate\n**";
	cin>>crateW;
	cout<<endl;

	cout<<"Enter height of the shipping crate\n**";
	cin>>crateH;
	cout<<endl;

	//Calculations for crate
	double volumeCrate = crateW * crateH * crateL;
	double areaCrate = 2*(crateW*crateL+crateH*crateL+crateH*crateW);
	double diagonalCrate = sqrt(pow(crateL,2)*pow(crateW,2)*pow(crateH,2));

	//Ask user input for storage space
	cout<<"\nSTORAGE SPACE"<<endl;

	cout<<"Enter length of storage space\n**";
	cin>>spaceL;
	cout<<endl;

	cout<<"Enter width of storage space\n**";
	cin>>spaceW;
	cout<<endl;

	cout<<"Enter height of the storage space\n**";
	cin>>spaceH;
	cout<<endl;
	
	//Calculations for space
	double volumeSpace = spaceW * spaceH * spaceL;
	double areaSpace= 2*(spaceW*spaceL+spaceH*spaceL+spaceH*spaceW);
	double diagonalSpace = sqrt(pow(spaceL,2)*pow(spaceW,2)*pow(spaceH,2));
	
	//Print the chart with input and calculations

	//Print the first row
	cout<<str<<endl;
	cout<<"| TYPE  | LENGTH  | WIDTH  | HEIGHT | VOLUME     | SURFACE AREA | DIAGONAL |"<<endl;

    cout<<fixed<<showpoint<<setprecision(1);

	//Print crate row
	cout<<str<<endl;
	cout<<"| Crate |";
	cout<<setw(9) << crateL<<"|";
	cout<<setw(8)<<crateW<<"|";
	cout<<setw(8)<<crateH<<"|";
	cout<<setw(12)<<volumeCrate<<"|";
	cout<<setw(14)<<areaCrate<<"|";
	cout<<setw(10)<<diagonalCrate<<"|"<<endl;

	//Print space row
	cout<<str<<endl;
	cout<<"| Space |";
	cout<<setw(9) << spaceL<<"|";
	cout<<setw(8)<<spaceW<<"|";
	cout<<setw(8)<<spaceH<<"|";
	cout<<setw(12)<<volumeSpace<<"|";
	cout<<setw(14)<<areaSpace<<"|";
	cout<<setw(10)<<diagonalSpace<<"|"<<endl;
	cout<<str<<endl;

	//Print num of crates that fit in the storage space
	cout<<"\n"<<floor(spaceL/crateL)*floor(spaceW/crateW)*floor(spaceH/crateH)<<" crates can fit in the storage space."<<endl;

    return 0;

}
