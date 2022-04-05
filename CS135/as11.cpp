/* Name: Stephaney Chang, 2001508920, CS1351002, Assignment 11
 * Description: This program will take in a US coastal guard csv database of ships (AIS).
 * It will get all the data and store it in a struct. Then prompt the user for a keyword
 * to find ship, then print the results. Ask user for ship to find the distance
 * the ship travelled for that day. End the program when the user answer 'q'
 * Input: CSV file, name of ship to search
 * Output: All ship data that user searched for
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

// Structure to hold item data
struct AISType{
    string MMSI;                // 0 
    string baseDateTime;        // 1
    double  lattitude;          // 2
    double longitude;           // 3
    double sog;                 // 4
    double cog;                 // 5
    double heading;             // 6
    string vesselName;          // 7
    string imo;                 // 8
    string callSign;            // 9
    string vesselType;          // 10
    string status;              // 11
    double length;              // 12
    double width;               // 13
    double draft;               // 14
    string cargo;               // 15
    string transceiverClass;    // 16
};

// Prototypes for functions
void readFile( ifstream & inFile, vector<AISType> &item, int& count);
bool openInputFile(ifstream & inFile); 
string makeStringUpper(string s); 
int searchForVesselByName( vector<AISType> & dataBase,  string vesselName, vector<string> & s);
void printRecord(AISType & item); 
bool getNextField(string &line, int &index, string &subString);
double stringConvert(string); 
int findLastOccurrance(string mmsi, vector<AISType> &d);
int findFirstOccurrance(string mmsi, vector<AISType> &d);
void addUniqueString( vector<string> &s, string value);
void saveField(int fieldNumber, string subString,  AISType &tempItem);      
double distanceTraveled(vector<AISType> & dataBase, int first, int last); 

int main(){
	// number of records read into the dataBase
	int count=0;		

	// the dataBase 
	// vector type is used because it's too big for an array.
	// (on my computer anyway)
	vector<AISType> dataBase;
    vector<string> mmsi;

	// input file 
	ifstream inFile;

	// temporary strings
	string temp;
    string ansYN;

    int found=0;
    string stars="";
    int first =0, last =0;

	// open the input file
	if (openInputFile(inFile)){
	       cout << "File opened correctly "<<endl;
	}
	else{
		cout << "Error opening file"<< endl << "Exiting...." << endl;
		return 0;
	}

	// read the entire file into the dataBase 
	readFile(inFile, dataBase, count);

	cout << count << " records read "<<endl;

    cin.ignore(40, '\n');

    // user interaction loop
    do{

        // prompt the user for the input to search for.  q to quit
        temp.clear();
        mmsi.clear();

        cout << "Enter vessel name: ";

        // read the user input.  getline is used so that spaces may be
        // included in the input
        getline(cin, temp, '\n');

        // check to see if the user wants to exit the program. 
        // If not exiting, output the search string.
        if ( temp != "q" or temp == "Q" ){
            cout << endl<< "Searching for records with"
                            " names containing \"" 
                 << temp << "\"" << endl;
        }
        else{
            return 0;
        }

        // search for the number of items that contain the name/phrase
        // All names in the vessel dataBase are upper case, so make 
        // the search string upper.  MMSI is built by the function
        // and contains the vector of unique vessels that contain
        // the name searched for. 
        found = searchForVesselByName( dataBase,  
                                makeStringUpper(temp), mmsi );

        // Let the user know if any ships were found with the name
        if(found <= 0) {
            cout << "Vessel \"" << temp << "\" not found" << endl;
            continue;
        }
        else{
            // output the results of the search
            cout << stars << endl;
            cout << found << " records found with name containing \"" 
                          << temp << "\", ";
            cout <<  "Unique vessels: " <<  mmsi.size()  << endl;
            cout << stars << endl;

            // ships were found, see if the user wants to display them
            cout << mmsi.size() << " vessels found. Would you"
                                   " like to see their"
                                << " first records? [y/n] " ;
            cin >> ansYN;

            if (ansYN =="y" or ansYN == "Y"){

                // print all the first records for the ships found
                for (unsigned int i=0; i<mmsi.size(); i++){

                    // find the vessels using MMSI and print 
                    // the records
                    int index = findFirstOccurrance( mmsi[i],
                                                 dataBase );

                    // verify that a valid record was found, 
                    // print the record
                    if ( index != -1)
                     printRecord( dataBase[index]);
                }
            
                    // Ask user if they want to calculate the 
                    // distance traveled for the vessel.
                    cout << "Would you like to find the distance"
                            " traveled for a vessel?"
                            " [y/n] " ;
                    cin >> ansYN;
                    if(ansYN == "y" or ansYN == "Y"){
                        do{
                            cout <<  "MMSI for vessel/(q-quit): " ;
                            cin >> temp;
                            if ( temp == "Q" or temp == "q")
                                break;
                            cout << stars << endl;

                            // locate the index value of the first and
                            // last record
                            first = findFirstOccurrance( temp, dataBase);
                            last = findLastOccurrance( temp, dataBase);
                            distanceTraveled(dataBase, first, last);
                            cout << endl;

                        }while( true );
                    }
            }
        }
        cin.ignore( 40, '\n');

    }  while ( true );

}

/* Using the first instance of the ship and last instance of the ship
 * lattitude and longitude, caluclate the distance it travelled using formula
 * and print the results.
 * dataBase - vector struct that holds all ship data
 * first - index of the first instance of ship MMSI
 * last - index of the last instance of ship MMSI
 */
double distanceTraveled( vector<AISType> & dataBase, int first, int last ){
    double R = 3958.8; //Radius of the earth in miles
    double PI = 3.14159; //Value of pi

    //Convert lat and long to degrees
    double a1 = dataBase[first].lattitude*PI/180; //First lattitude as a radian
    double a2 = dataBase[last].lattitude*PI/180; //Last lattitude as a radian
    double a3 = dataBase[first].longitude*PI/180; //First longitude as a radian
    double a4 = dataBase[last].longitude*PI/180; //Last longitude as a radian

    double differenceLat = a1-a2; //Difference of the lattitudes
    double differenceLong = a3-a4; //Difference of the longitudes

    //Calculate distance using the haversine formula

    //Calculate a for harversine formula c
    double a = (sin(differenceLat/2)*sin(differenceLat/2))+cos(a1)*cos(a2)*(sin(differenceLong/2)*sin(differenceLong/2));

    //Take a and calculate using haversine formula
    double c = 2*(atan2(sqrt(a),sqrt(1-a)));

    double distance = R *c; //Calculate the distance in miles
    
    //Condition if the user input is invalid, otherwise print the results
    int invalidMMSI = dataBase.size()+1;
    if(first==invalidMMSI){
        cout<<"Distance Travelled: Error, invalid record number."<<endl;
    }
    else{
    cout<<"Vessel: "<<dataBase[first].vesselName<<" MMSI: "<<dataBase[first].MMSI<<" Trip Starting Time: ";
    cout<<dataBase[first].baseDateTime<<endl;
    cout<<"Distance Travelled From: ("<<dataBase[first].lattitude<<", ";
    cout<<dataBase[first].longitude<<") to ("<<dataBase[last].lattitude<<", "<<dataBase[last].longitude<<") ";
    cout<<distance<<" Miles"<<endl;
    }

    return distance;
}

/* Match the MMSI of a vessel and check for the last occurence
 * Once found, break out of the loop and return the index value
 * mmsi - mmsi index to look for
 * d - vector with ship data items
 */
int findLastOccurrance(string mmsi, vector<AISType> &d){
    int foundIndex = 0; //Index of last occurring ship
    int size = d.size();//Starting index at the end

    //Loop through the vector
    for(int i=size; i>0;i--){
        if(d[i].MMSI == mmsi){
            foundIndex = i;
            break; //Break out of loop
        }
    }
  
    return foundIndex;
}
/* Match the MMSI of vessel and check for the first occurence.
 * Once found, break out of the loop and return the index
 * mmsi - mmsi to look for
 * d - vector of data to loop through for mmsi
*/
int findFirstOccurrance(string mmsi, vector<AISType> &d){
    int foundIndex = 0; //Index of the first instance
    bool found = false;
    int size = d.size();

    //Sets the condition if the user inputted mmsi is not valid
    for(int i=0;i<size; i++){
        //Search for the string in mmsi member of struct
        if(d[i].MMSI.find(mmsi) != std::string::npos){
            found = true;
        }
    }

    //Loop through vector if it is a valid mmsi
    if(found==true){
        for(int i=0; i<size; i++){
            if(d[i].MMSI == mmsi){
                foundIndex = i;
                break; //Break out of loop
            }
        }
    }
    else{
        //Set a random number beyond the size of the struct
        foundIndex=d.size()+1;
    }

    return foundIndex;
}

/* Using user inputted name to search, loop through vector AISType for any ship names
 * that contain vesselName. If found, store the mmsi of said vesselName to vector s to
 * add as a unique value.
 * dataBase - struct containing all ship data
 * vesselName - name of ship to look for in struct
 * s - vector of string containing mmsi
 */
int searchForVesselByName( vector<AISType> & dataBase, string vesselName, vector<string> &s){
    int numberFound = 0; //Number of lines of data read
    string value; //placeholder for found MMSI
    int size = dataBase.size();

    for(int i=0;i<size; i++){
        //Search for the string in vesselName member of struct
        if(dataBase[i].vesselName.find(vesselName) != std::string::npos){
            numberFound++; //Increment if found
            value = dataBase[i].MMSI; //Assign value
            addUniqueString(s, value);
        }
    }
    
    return numberFound;
}

/* From the searchForVesselByName function, get the current value and compare to the
 * strings in the vector s. If there is none of the value in the vector, continue
 * else if found, mark bool found as true. If the bool value is found, don't do anything
 * otherwise, add value to the vector s
 * s - vector containing a unique MMSI
 * value - MMSI to compare against s
 */
void addUniqueString(vector<string> &s, string value){
    bool found = false; //boolean if a string is unique to vector
    int stringSize = s.size();

    //Search through the vector if there is a duplicate or not
   for(int i=0;i<stringSize;i++){
       if(s[i] == value){
           found = true; //True if there is a duplicate
       }
       else{
           continue;
       }
   }

   if (found == true){
       //Do nothing to the vector
   }
   else{
       s.push_back(value); //Add new MMSI to vector
   }
}

/* Using sstring library, converts the variable s to a double.
 * s - string to be converted to double data type
 * Return s as a double
*/
double stringConvert(string s){
    double convertDbl = 0.0; //Double value of string
    stringstream str; //String stream

    //Convert the string
    str<<s;
    str>>convertDbl;
   
    return convertDbl;
}

/* printRecord will take a piece of data from struct type variable and print what is stored
 * item - struct data type containing data related to searched ship
*/
void printRecord(AISType &item){
    string stars = "************************"; //Formatting

    //Print the data neatly
    cout<<stars<<endl;
    cout<<"MMSI: "<<item.MMSI<<endl;
    cout<<"Base Date Time: "<<item.baseDateTime<<endl;
    cout<<"Lattitude: "<<item.lattitude<<" Longitude: "<<item.longitude<<endl;
    cout<<"SOG: "<<item.sog<<endl;
    cout<<"COG: "<<item.cog<<endl;
    cout<<"Heading: "<<item.heading<<endl;
    cout<<"Vessel Name: "<<item.vesselName<<endl;
    cout<<"imo: "<<item.imo<<endl;
    cout<<"Call Sign: "<<item.callSign<<endl;
    cout<<"Vessel Type: "<<item.vesselType<<endl;
    cout<<"Status: "<<item.status<<endl;
    cout<<"Length: "<<item.length<<endl;
    cout<<"Width: "<<item.width<<endl;
    cout<<"Draft: "<<item.draft<<endl;
    cout<<"Cargo: "<<item.cargo<<endl;
    cout<<"Transceiver Class: "<<item.transceiverClass<<endl;
    cout<<stars<<endl;
}

/* openInputFile will prompt the user for a csv file name and open it if it is valid.
 * If invalid, then the function will continue to loop until a file is opened.
 * inFile - ifstream variable for user inputted file
*/
bool openInputFile( ifstream & inFile ){
    string filename; //User input file 

    //Prompt user for a file
    do{
        if(inFile.fail()){
            inFile.clear();
            inFile.ignore(100, '\n');
        }

        cout<<"Enter file name: "<<endl;
        cin>>filename;

        inFile.open(filename.c_str());

        if(!inFile.is_open()){
            cout<<"Error, file not found."<<endl;
            return false;
        }

    }while(inFile.fail());

  return true;
}

/* readFile - takes a previously opened file and read in the data to a temporary struct, then
 * using pushback(), take the data from temporary struct and store in the vector called item
 * inFile - ifstream variable for opened file
 * item - struct type vector that will store all ship data
 * count - number lines in a file
 */
void readFile( ifstream & inFile, vector<AISType> &item, int& count){
    string line;
    int index = 0;
    int fieldNumber =0;
    string substr;
    bool notEof = true;

    AISType currRecord;

    count =0;

    while(getline(inFile, line)){
        while(notEof){
            substr.clear();
            notEof = getNextField(line, index, substr);
            saveField(fieldNumber, substr, currRecord);
            fieldNumber++;
        }
        
        count++;
        notEof = true;
        index = 0;
        fieldNumber = 0;
        item.push_back(currRecord);

    }
    
    cout<<"----------------------"<<endl;
    cout<<"--- End of file reached --- Items read: "<<count<<endl;
}

/* saveFile will save the data to a temporary struct during a loop in function readFile
 * Depending on the field number, assign the data to its appropriate member
 * fieldNumber - current placement of the data
 * subString - actual data of ship from csv file
 * tempItem - temporary struct to hold subString data
 * 
*/
void saveField( int fieldNumber, string subString,  AISType &tempItem ){
    double converted =0.0;        
    switch(fieldNumber){
        case 0:
            tempItem.MMSI = subString;
            break;
        case 1:
            tempItem.baseDateTime = subString;
            break;
        case 2:
            converted = stringConvert(subString);
            tempItem.lattitude = converted;
            break;
        case 3:
            converted = stringConvert(subString);
            tempItem.longitude = converted;
            break;
        case 4:
            converted = stringConvert(subString);
            tempItem.sog = converted;
            break;
        case 5:
            converted = stringConvert(subString);
            tempItem.cog = converted;
            break;
        case 6:
            converted = stringConvert(subString);
            tempItem.heading = converted;
            break;
        case 7:
            tempItem.vesselName = subString;
            break;
        case 8:
            tempItem.imo = subString;
            break;
        case 9:
            tempItem.callSign = subString;
            break;
        case 10:
            tempItem.vesselType = subString;
            break;
        case 11:
            tempItem.status = subString;
            break;
        case 12:
            converted = stringConvert(subString);
            tempItem.length = converted;
            break;
        case 13:
            converted = stringConvert(subString);
            tempItem.width = converted;
            break;
        case 14:
            converted = stringConvert(subString);
            tempItem.draft = converted;
            break;
        case 15:
            tempItem.cargo = subString;
            break;
        case 16:
            tempItem.transceiverClass = subString;
            break;
        default:
            cout<<"Error"<<endl;
    }
}

/* Taking line from getline in readData function, parse the data by comma and store
 * the string in temporary variable subString.
 * Return false if not end of line, else return true if it is end of line
 * line - line to parse
 * index - current index of line to parse
 * subString - temporary hold of the current data being parsed.
*/
bool getNextField(string &line, int &index, string &subString){
    int lineLength = line.length();

    //Parse the line if it is not a , or end of the line
    while((index<=lineLength) && (line[index] != ',')){
        subString += line[index]; //Get single data
        index++; //New index
    }

    index++;

    if (lineLength<=index){
        return false;
    }
    else{
        return true;
    }
}

/* Takes a string variable and converts it to an upper by turining string
 * into an array of char and upper casing each char.
 * s - string to be upper cased
 * Return s as upper case
*/
string makeStringUpper(string s){
    int stringLength = s.length();
    //Go through all chars in string and convert to upper case
    for(int i=0; i<stringLength;i++){
        s[i] = toupper(s[i]);
    }
    
    return s;
}
