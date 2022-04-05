/* Stephaney Chang, 2001508920, CS135-1002, Assignment 2
 * Description: The program will prompt the user to input three values: width,
 * height, and length of the ship. Then it will calculate the volume and surface,
 * area and print the results.
 * Input: Width, height, and length
 * Output: Sea surface area and ship volume
 
*/

#include <iostream>

using namespace std;
const double PI=3.14159265358; //use pi as a global var 

int main(){
	cout<<" ***********\nShip Calculator\n ***********\n"<<endl;

	//These variables will be used to get the area and volume.
	double width=0.0; 
	double height=0.0;
	double length=0.0;

	//These variables will calculate the volume and area.
	double volumeShip=0.0;
	double areaSea=0.0;

	//Prompt user to input width, length, and height.
	cout<<"Enter the width of the ship: "; 
	cin>>width; 
	
	cout<<"Enter the length of the ship: "; 
	cin>>length; 

	cout<<"Enter the height of the ship: "; 
	cin>>height; 

	volumeShip = 4.0/3.0*PI*width*length*height; //formula for ship volume
	areaSea = PI*width*length; //formula for sea area

	//Print calculation results.
	cout<<"\nResults:"<<endl;
	cout<<"Calculations for ship "<<width<<"W "<<length<<"L "<<height<<"H"<<endl;
	cout<<"Sea surface area: "<<areaSea<<" square feet"<<endl;
	cout<<"Volume is: "<<volumeShip<<" cubic feet"<<endl;
	cout<<"\nThank you for using the ship calculator"<<endl;

	return 0;	
}