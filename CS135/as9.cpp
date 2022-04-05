/* Name: Stephaney Chang, 2001508920, CS1351002, Assignment 9 
 * Description: This program will get a user inputted csv file containing fish data and prompt them to filter
 * out the resuls based on fish attributes. Then, based on filters, print out fish data.
 * Input: Fish csv file, user menu choice, user value search
 * Output: List of fish and its common name, scientific name, tolerable salinity, tolerable temperature,
 * tank volume and depth
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const int LENGTH= 100; //Store length of arrays

void PrintMenu(void);
void CasefoldString(string &);
void PrintResults(string, string, double, double, double, double, double, double, double);
void FilterNotString(bool[], string [], int, string, int&);
void FilterLessValue(bool [], double [],int, double, int&);
void FilterGreaterValue(bool [], double [], int, double, int&);
void FilterOutRange(bool [], double [], double [], int, double, int&);


int main(){
    //FILE VARIABLES
    string line;
    string filename;
    ifstream inFile;

    //MENU ANSWER VARIABLES
    char firstAnswer; //First menu answer
    char secondAnswer; //Second menu answer

    //COUNTERS
    int numOfElements = 0; //Keep unfiltered elements
    int tempElement = 0; //Keeps the last number of unfiltered elements
    int count = LENGTH; //Loop until end of array

    //FILTER VARIABLES
    string name; //Gets string input for names
    double min = 0.0; //Gets double input for min
    double max = 0.0; //Gets double input for max

    //ARRAYS
    string commonName[LENGTH]; //Store fish common name
    string scientificName[LENGTH]; //Store fish scientific name
    double length[LENGTH]; //store fish length
    double minSalinity[LENGTH]; //store minimum salinity
    double maxSalinity[LENGTH]; //store maximum salinity
    double minTemp [LENGTH]; //store minimum temperature
    double maxTemp[LENGTH]; //store maxiumum temperature
    double minVolume[LENGTH]; //store minimum volume
    double minDepth[LENGTH]; //store minimum depth

    bool arrayFiltered[LENGTH]; //Stores all bool filter trackers in general
    double copyFilter[LENGTH]; //Copies the index of unfiltered elements

    //INDIVIDUAL ARRAY ELEMENTS TO PRINT
    string nameCommon;
    string nameScience;
    double fishLength;
    double minSalin;
    double maxSalin;
    double minTemperature;
    double maxTemperature;
    double volume;
    double depth;
    

    //-------------------------------------------GET INPUT FILE----------------------------------------------------
    do{
        cout<<"Open Fish Database (CSV): ";
        cin>>filename;
        inFile.open(filename.c_str());
        
        //Print error message if not open
        if(!inFile.is_open()){
            cout<<"Invalid file format."<<endl;
        }
    }while(inFile.fail());

    cout<<endl;

    //Ignore the first line of file
    getline(inFile, line);
    inFile.ignore(1000, '\n');

    //Get the data in the file
    for(int i=0; i<LENGTH;i++){
        getline(inFile, commonName[i], ',');
        getline(inFile, scientificName[i], ',');

        if(inFile.fail()){
            inFile.clear();
            inFile.ignore(100, ',');
        }

        inFile>>length[i];
        inFile.ignore(100, ',');
        inFile>>minSalinity[i];
        inFile.ignore(100, ',');
        inFile>>maxSalinity[i];
        inFile.ignore(100,',');
        inFile>>minTemp[i];
        inFile.ignore(100, ',');
        inFile>>maxTemp[i];
        inFile.ignore(100, ',');
        inFile>>minVolume[i];
        inFile.ignore(100,',');
        inFile>>minDepth[i];
        inFile.ignore(100,'\n');

        arrayFiltered[i] = false; //Default all elements filtered as false

        numOfElements++;
        
    }

    //Print how many fishes in the record
    cout<<"\n"<<numOfElements<<" fish records loaded."<<endl;

    //-------------------------------------------GET INPUT FIRST MENU INPUT------------------------------------------------
do{
    do{
        //Get user input
        PrintMenu(); //Print the menu
        cin>>firstAnswer;

    }while(cin.fail() && (firstAnswer!='F'&& 'f'&& 'P'&&'p'&&'R'&&'r'&&'Q'&&'q'));


    //-------------------------------------------ANSWER F------------------------------------------------

    //Get user input filter if answer is a valid char
    if(firstAnswer=='f' ||firstAnswer=='F'){
        do{
            cout<<"\nFilter by..."<<endl;
            cout<<"[C]ommon Name\nSci[e]ntific Name\n[L]ength\n[S]alinity\n[T]emperature\n[V]olume\n[D]epth\nChoice: ";
            cin>>secondAnswer;

            if(secondAnswer=='c'||'C'||'e'||'e'||'l'||'L'||'s'||'S'||'t'||'T'||'v'||'V'||'D'||'d'){
            //Filter the fishes by common name 
                if(secondAnswer=='c' || secondAnswer== 'C'){
                    do{
                        cout<<"\nSearch For: ";
                        cin>>name;
                    }while(cin.fail());

                    //Convert input to lower case
                    CasefoldString(name);

                    //Convert common name arrays to lowercase
                    for(int i=0; i<LENGTH; i++){
                        CasefoldString(commonName[i]);
                    }
                    
                    //Filter through the array and copy index and set found element as true
                    int counter = 0;
                    for(int i=0; i<LENGTH; i++){
                        if(commonName[i].find(name,0) != std::string::npos){
                            arrayFiltered[i] = true;
                            copyFilter[counter] = i;
                            counter++;
                        }
                    }
                        
                    //Print the number of elements that contain user inputted value
                    FilterNotString(arrayFiltered, commonName, count, name, numOfElements);
                     
                    break; //Loop back to main menu
                }
                    
                //Filter fish by scientific name
                if(secondAnswer=='e' || secondAnswer == 'E'){   
                    do{
                        cout<<"\nSearch for: ";
                        cin>>name;
                        if(cin.fail()){
                            cin.clear();
                            cin.ignore(100, '\n');
                        }
                    }while(cin.fail());

                    //Convert input to lower case
                    CasefoldString(name);
                    
                    //Convert scientific name to lower case
                    for(int i=0; i<LENGTH; i++){
                        CasefoldString(scientificName[i]);
                    }   

                    //Print how many results have  input value
                    FilterNotString(arrayFiltered, scientificName, count, name, numOfElements);

                    //Check if names match and set to true and store the index of found element
                    int counter = 0;
                    for(int i=0; i<LENGTH; i++){
                        if(scientificName[i].find(name,0) != std::string::npos){
                            arrayFiltered[i] = true;
                            copyFilter[counter] = i;
                            counter++;
                        }
                    }

                    break; //Loop back to main menu       
                }

                //Filter fish by length
                if(secondAnswer=='L' || secondAnswer =='l'){
                    //Get user input
                    cout<<"\nMinimumum Size: ";
                    cin>>min;
                    cout<<"\nMaximum Size: ";
                    cin>>max;
                    cout<<endl; 
                  
                    //Check if the array element is bigger than min and smaller than max, copy index if true
                    int counter = 0;
                    for(int i=0; i<LENGTH; i++){
                        if((length[i]>=min && length[i]<=max) && arrayFiltered[i] == true){
                            copyFilter[counter] = i;
                            counter++;
                        }
                        else if((length[i]>=min && length[i]<=max) && arrayFiltered[i]==false && numOfElements==0){
                            arrayFiltered[i] = true;
                            copyFilter[counter] = i;
                            counter++;
                        }
                    }

                    //Print how many results have  input value
                    FilterLessValue(arrayFiltered, length, count, min, numOfElements);
                    FilterGreaterValue(arrayFiltered, length, count, max, numOfElements);

                    break; //Loop back to main menu
                }

                //Filter fish by salinity
                if(secondAnswer=='s' ||secondAnswer=='S'){
                    //Get user input
                    cout<<"\nMinimum Salinity: ";
                    cin>>min;
                    cout<<endl;

                    //Check if the element is larger than min and and copy the index if true
                    int counter = 0;
                    for(int i=0; i<LENGTH; i++){
                        if(minSalinity[i]>=min && maxSalinity[i]>=min && arrayFiltered[i]==true){
                            arrayFiltered[i] = true;
                            copyFilter[counter] = i;
                            counter++;
                        }
                        else if(minSalinity[i]>=min && maxSalinity[i]>=min && arrayFiltered[i]==false && numOfElements==0){
                            arrayFiltered[i] = true;
                            copyFilter[counter] = i;
                            counter++;
                        }
                    }

                    //Print how many results have  input value
                    FilterOutRange(arrayFiltered, minSalinity, maxSalinity, count, min, numOfElements);

                    break; //Loop back to main menu
                }

                //Filter fish by temperature
                if(secondAnswer=='t' || secondAnswer=='T'){
                    //Get user input
                    cout<<"\nTank Temperature (C): ";
                    cin>>min;
                    cout<<endl;

                    //Check if temp is larger than the min and copy index if true
                    int counter = 0;
                    for(int i=0; i<LENGTH; i++){
                        if(maxTemp[i]>=min && arrayFiltered[i] ==true){
                            copyFilter[counter] = i;
                            counter++;
                        }
                        else if(maxTemp[i]>=min && arrayFiltered[i]==false){
                            arrayFiltered[i] = true;
                            copyFilter[counter] = i;
                            counter++;
                        }
                    }

                    //Print how many results have  input value
                    FilterOutRange(arrayFiltered, minTemp, maxTemp, count, min, numOfElements);

                    break; //Loop  main menu
                }

                //Filter fish by volume
                if(secondAnswer=='v'|| secondAnswer=='V'){
                    //Get user input
                    cout<<"\nTank Volume (gal): ";
                    cin>>max;
                    cout<<endl;

                    //Check if array element is smaller than the max and copy index if true
                    int counter = 0;
                    for(int i=0; i<LENGTH; i++){
                        if(minVolume[i]<=max && arrayFiltered[i]==true){
                            copyFilter[counter] = i;
                            counter++;
                        }
                        else if(minVolume[i]<=max && arrayFiltered[i]==false && numOfElements==100){
                            arrayFiltered[i] = true;
                            copyFilter[counter] = i;
                            counter++;
                        }
                    }

                    //Print how many results have  input value
                    tempElement = numOfElements; //Hold the previous number of elements
                    FilterLessValue(arrayFiltered, minVolume, count, max, numOfElements);
                    numOfElements = tempElement - numOfElements; //Current num of elements
                    cout<<numOfElements<<" results found."<<endl;

                    break; //Loop back to main menu
                } 

                //Filter fish by depth
                if(secondAnswer=='d'||secondAnswer=='D'){
                    //Get user input
                    cout<<"\nTank Depth (m): ";
                    cin>>min;
                    cout<<endl;

                    //Check if array element is less than the min and copy the index if true
                    int counter = 0;
                    for(int i=0; i<LENGTH; i++){
                        if((minDepth[i]<=min) && arrayFiltered[i]==true){
                            arrayFiltered[i] = true;
                            copyFilter[counter] = i;
                            counter++;
                        }
                        else if(minDepth[i]<=min && arrayFiltered[i]==false && numOfElements==100){
                            arrayFiltered[i] = true;
                            copyFilter[counter] = i;
                            counter++;
                        }
                    }
                    
                    //Print how many results have  input value
                    tempElement = numOfElements; //Copy the previous num of elements
                    FilterLessValue(arrayFiltered, minDepth, count, min, numOfElements);
                    numOfElements = tempElement -numOfElements;
                    cout<<numOfElements<<" results found."<<endl; //Print the current num of elements

                    break; //Loop back to main menu
                }              
            }

            //Loop back to the main menu if inputs are not valid
            if(secondAnswer!='c'&&'C'&&'e'&&'e'&&'l'&&'L'&&'s'&&'S'&&'t'&&'T'&&'v'&&'V'&&'D'&&'d'){
                cout<<endl;
                break;
            }
                
        }while(!cin.fail() || (secondAnswer!='c'&&'C'&&'e'&&'e'&&'l'&&'L'&&'s'&&'S'&&'t'&&'T'&&'v'&&'V'&&'D'&&'d'));
    }

    //-------------------------------------------PRINT RESULTS------------------------------------------------

    if(firstAnswer =='p' || firstAnswer =='P'){
        int resultNum = 1; //Store result number
        int counter2 = 0; //Index for copy filter
        for(int i=0; i<LENGTH; i++){
            //Print the resutls
            if (i == copyFilter[counter2]){
                nameCommon = commonName[i];
                nameScience = scientificName[i];
                fishLength = length[i];
                minSalin = minSalinity[i];
                maxSalin = maxSalinity[i];
                minTemperature = minTemp[i];
                maxTemperature = maxTemp[i];
                volume = minVolume[i];
                depth = minDepth[i];
                cout<<"\nResults #"<<resultNum<<endl;
                PrintResults(nameCommon, nameScience, fishLength, minSalin, maxSalin, minTemperature, maxTemperature,volume,depth);
                resultNum++;
                counter2++;
            }
        }

        cout<<"\n"<<resultNum-1<<" results found."<<endl;
        continue;
    }

    //-------------------------------------------RESET FILTERS------------------------------------------------

    if (firstAnswer == 'r' || firstAnswer =='R'){
        //Reset
        cin.clear();
        cin.ignore(1000,'\n');
        cout<<"\nResetting filters...\n"<<endl;
        //Reset the list of copied indexes
        for (int i=0; i<LENGTH; i++){
            copyFilter[i] = 0;
        }
        continue;
    }

    //-------------------------------------------QUIT PROGRAM------------------------------------------------

    if(firstAnswer=='q' || firstAnswer =='Q'){
        //Quit program
        cout<<"\nHave a nice day!"<<endl;
        return 0; 
    }

    }while(!cin.fail());
    
    return 0;
}

//---------------------------------------------------------FUNCTIONS----------------------------------------------------

/* Void PrintMenu prints out the main menu that the user first sees
 * Params: None
 */
void PrintMenu(void){
    //Results
    cout<<"[F]ilter Results\n[P]rint Results To Screen\n[R]eset Filters\n[Q]uit."<<endl;
    cout<<"Choice: ";
}

/* Converts the user inputted value to all lowercases
 * Params: string& fishName
 */
void CasefoldString(string& fishName){
    int length = fishName.length();
    for(int i =0; i<length;i++){
        fishName[i] = tolower(fishName[i]);
    }
}
/* Prints the results of filtered values
 * Params: Common name, science name, length of fish, min and max tolerable salinity, min and max tolerable temperature
 * min volume of tank, min depth of tank
 * No return value
 */
void PrintResults(string commonName, string scienceName, double length, double minSalin, double maxSalin, double minTemp, double maxTemp, double tankVol,double tankDepth){
    cout<<setprecision(1)<<fixed<<showpoint;
    cout<<"Common Name: "<<commonName<<endl;
    cout<<"Scientific Name: "<<scienceName<<endl;
    cout<<"Fish Length: "<<length<<" cm"<<endl;
    cout<<"Tolerable Salinity: "<<minSalin<<" - "<<maxSalin<<" ppt"<<endl;
    cout<<"Tolerable Temperature: "<<minTemp<<" - "<<maxTemp<<" C"<<endl;
    cout<<"Minimum Tank Size: "<<tankVol<<" gallons"<<endl;
    cout<<"Minimum Tank Depth: "<<tankDepth<<" meters"<<endl;
}

/* Reads chosen array and checks if the user input is found in any of the array values. Then it will print
 * the number of values (entries) that contaian input value.
 * Params: filterTrack (checks if the element meets condition),
 * fishName (gets either commonName or scientificName arrays)
 *  size (size of array), input (user inputted name), entries(number of entries)
 */ 
void FilterNotString(bool filterTrack[LENGTH], string fishName[LENGTH], int size, string input, int& entries){
    int count = 0;
    for(int i=0; i<size; i++){
        if(fishName[i].find(input,0) != std::string::npos){
            filterTrack[i] = true;
            count++;
        }
    }

    entries = count;

    cout<<"\n"<<entries<<" results found"<<endl;
}

/* Filters the array values based on a minimum value. Add to number of entries that are not filtered out if the
 * array value is over the minimum.
 * Params: filterTrack (gets array of elements that meet the condition), lessValue (minimum value array)
 * size (size of array), input (user inputted value), entries(number of entries)
 */ 
void FilterLessValue(bool filterTrack[LENGTH], double lessValue[LENGTH],int size, double input, int& entries){
    for(int i=0; i<LENGTH; i++){
        if(lessValue[i]<=input && filterTrack[i]==true){
            entries = entries - 1;
        }
    }
}

/* Filters the array values based on a maximum value. Add to number of entries that are not filtered out if the
 * array value is under the maximum.
 * Params: filterTrack (gets array of elements that meet the condition), greaterValue (max value array)
 * size (size of current arary), input (user inputted value), entries (current number of entries)
 */ 
void FilterGreaterValue(bool filterTrack[LENGTH], double greaterValue[LENGTH],int size, double input, int& entries){
    int totalEntries = entries;
    for(int i=0; i<LENGTH; i++){
        if(greaterValue[i]>=input && filterTrack[i] == true){
            entries = entries - 1;
        }
    }

    cout<<totalEntries + entries<<" results found."<<endl;
}
/* Filters the values of an array based on a minimum and maximum value. Add to number of entries (unfiltered values) if
 * the array value fits in between user inputted minimum and maximum value.
 * Params: filterTrack (gets array of elements that meet the condition), minValues (minimum value array)
 * maxValues (maximum value array), size (size of arrays), minsize(minimum user input), entries(number of entries)
 */ 
void FilterOutRange(bool filterTrack[LENGTH], double minValues[LENGTH], double maxValues[LENGTH], int size, double minsize, int& entries){
    int count = 0;
    for(int i =0; i<size; i++){
        if((minValues[i]<=minsize) && (maxValues[i]>=minsize)){
            count++;
        }
    }

    entries = count;

    cout<<entries<<" results found."<<endl;
}