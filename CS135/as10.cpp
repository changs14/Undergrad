/* Name Stephaney Chang, 2001508920, CS1351002, Assignment 10
 * Description: Replicate the game Clue.
 * Input: User will input char value to answer menu questions.
 * For the main game user will input a file or guess. 
 * Output: Menu and game options. If guess is wrong, output a message.
 * If the guess is right, game will end and the answer will output.
 */ 

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <ctime>

using namespace std;

//GLOBAL VARIABLES
const int SIZE = 5; //Max number of rows arrays can hold
bool guessesBool[5] = {false};//Stores if guesses are chosen or not)

//DISPLAY FUNCTIONS
void displayStartMenu(); 
void displayGameMenu(); 
void displayTokens(); 
void displayFile(ifstream&);
void displaySolution(int[], string[], string[],string[]);

//GAME SET UP
void loadGameData(ifstream&, string[],string[],string[]); 
int gameSetUp(ofstream&, int[][2], int[],string[], string[],string[]);
int playGame(ifstream&, ofstream&, int, int[][2],int[],string[],string[],string[]); 

//IN GAME FUNCTIONS
bool compareGuess(int[],int[]); 
int getRandom(int); 
int getRandomItem(bool[], int);
void getSolution(int[], int); 
void giveClues(ofstream&, int, int[][2],string[],string[],string[],int[]);
int guessItem(string[], int); 
void makeGuess(int[], string[], string[], string[], int);
void markSolution(bool[],bool[],bool[], int[]);
void writeToFile(ofstream&, int, string[], string[], string[], int, int, int, bool); 

int main(){
    //ifstream variables
    ifstream inFile;
    ofstream outFile;
    char answer; //Store user input for main menu

    //CSV array variables
    string professor[SIZE]; //Store tokens
    string topic[SIZE]; //Store topics
    string room[SIZE]; //Store rooms

    //Stores the information of user guesses and solution
    int players[4][2];
    int solutions[3];
    
    //Store the number of players
    int numOfPlayers = 0;

    //Display the first menu and get user input
    displayStartMenu();
    cin>>answer;
    
    //MAIN GAME LOOP
    if (answer =='g' || answer == 'G'){
        //Main menu
        loadGameData(inFile, professor, topic, room);
        //Ask user for num of players and assign a random token to each person
        numOfPlayers = gameSetUp(outFile, players, solutions, professor, room, topic);
        //Start the main loop of the game
        playGame(inFile, outFile, numOfPlayers, players, solutions, professor, room, topic);
    }

    //QUIT THE PROGRAM
    if (answer =='q' || answer =='Q'){
        cout<<"Thanks for playing!"<<endl;
        return 0;
    }

    return 0;
}

/* Displays the first menu */
void displayStartMenu(){
    cout<<"**********************"<<endl;
    cout<<"Please choose from the menu\n[G]ame Set Up\n[Q]uit Menu"<<endl;
    cout<<"**********************"<<endl;
}

/* Displays the main game menu */
void displayGameMenu(){
    cout<<"**********************"<<endl;
    cout<<"Let's Play! Choose an Option:"<<endl;
    cout<<"[D]isplay Guesses\n[G]uess Solution\n[E]nd Turn\n[S]ee Solution and Quit"<<endl;
    cout<<"**********************"<<endl;
}

/* Displays the tokens users can choose from */
void displayTokens(){
    cout<<"**********************"<<endl;
    cout<<"Choose A Token"<<endl;
    cout<<"[A]ndro-Vask\n[F]onesca\n[J]orgensen\n[M]artin\n[R]afalski"<<endl;
    cout<<"**********************"<<endl;
}

/* displays the solution to the game
 * solution[0] - token, room, topic
 * solution - indexes of each string array
 * tokens[] - string token
 * rooms [] - string room 
 * topics [] - string topics
 */ 
void displaySolution(int solutions[], string tokens[], string rooms[],string topics[]){
    cout<<"The solution was "<<tokens[solutions[1]]<<" "<<rooms[solutions[1]]<<" "<<topics[solutions[2]]<<endl;
}

/* Read file and store items in an array
 * Params: ifstream inFile - get inFile
 * string tokens - stores name of players
 * string topics - stores the player's course
 * string rooms - stores course number?
*/
void loadGameData(ifstream &inFile, string tokens[], string topics[], string rooms[]){
    string line; //Used to get the first line of the input file to ignore
    string filename = "gamesetup.txt";

    //Open the txt file
    inFile.open(filename.c_str());
    getline(inFile, line, '\n');

    //Get data
    for(int i=0; i<SIZE; i++){
        getline(inFile, tokens[i], ',');
        getline(inFile, topics[i], ',');
        getline(inFile, rooms[i], '\n');
    }

    inFile.close(); //Close file
}

/*Displays file that user inputted */
void displayFile(ifstream &iFile){
    string filename;
    string line;
    ofstream outFile;

    //Ask user for input file to display
    do{
        cout<<"Please enter a file to display."<<endl;
        cin>>filename;
        cout<<"**********************"<<endl;
        iFile.open(filename.c_str());

        //Continue loop if input file is invalid            
        if(!iFile.is_open()){
            cout<<"Error. Please enter a valid file name."<<endl;
        }
    }while(iFile.fail());

    //Print data            
    while(getline(iFile, line)){
        cout<<line<<endl;
        cout<<"**********************"<<endl;
    }
                
    iFile.close();
}

/* Prompt user for number of players to a max of 4 players
 * Params: ofStream outFile - file written for each player
 * int players[][] - to a max of 4, players get 2 objects (token and room)
 * tokens - name of players
 * room - course number
 * topics - course names
 */ 
int gameSetUp(ofstream &outFile, int players[][2], int solutions[], string tokens[], string rooms[],string topics[]){
    int numOfPlayers = 0;
    string filename;
    char userToken;

    //Prompt user for input
    do{
        cout<<"Please enter number of players (up to 4)"<<endl;
        cin>>numOfPlayers;
        
        //Check for invalid inputs
        if(cin.fail()){
            cout<<"Error. The max number of players is 4."<<endl;
            cin.clear();
            cin.ignore(100,'\n');
            continue;
        }
        
        if(numOfPlayers>4 || numOfPlayers<0){
            cout<<"Error. The max number of players is 4."<<endl;
        }
        
        if(numOfPlayers<=4 && numOfPlayers>=0){
            break;
        }
        
    }while(!cin.fail());
    
    //Assign a token based on number of players
    do{
        for(int i=0; i<numOfPlayers; i++){
            displayTokens();
            cin>>userToken;
            
            //Output who's turn it is based on user chosen token
            if(userToken == 'A' || userToken =='a'){
                players[i][0] = 0;
                players[i][1] = 0;
                    
                }
            else if(userToken == 'f' || userToken =='F'){
                players[i][0] = 1;
                players[i][1] = 1;
            }
            else if(userToken =='j' || userToken =='J'){
                players[i][0] = 2;
                players[i][1] = 2;
            }
            else if(userToken == 'm' || userToken == 'M'){
                players[i][0] = 3;
                players[i][1] = 3;
            }
            else if(userToken =='R' || userToken =='r'){
                players[i][0] = 4;
                players[i][1] = 4;
            }
            else{
                cout<<"Error. Please enter a valid token."<<endl;
                i--;
                continue;
            }
            
        }
    }while(cin.fail());

    return numOfPlayers;
}

/* Main loop that displays player choices and their turns
 * Params: ifstream inFile - get data from player guess files
 * ofstream outFile - write player guesses to file
 * int players [][2] - number of players and their tokens and rooms
 * int solutiosn[] - stores the one answer (token and room)
 * tokens[] - list of tokens
 * rooms[] - list of rooms
 * topics[] - list of topics
 */ 
int playGame(ifstream &iFile, ofstream &outFile, int numOfPlayers, int players[][2], int solutions[], string tokens[], string rooms[], string topics[]){
    char menuAnswer = '\0';
    string line;
    string filename;
    
    //Guess variables
    int guessSize =3;
    int userGuess[3] = {0}; //Stores tokenGuess, roomGuess, and topicGuess
    int tokenGuess = 0; //Index of token
    int roomGuess =0; //Index of room
    int topicGuess = 0;; //Index of topic
    
    //Boolean that holds whether an element in array was already chosen or is a solution    
    bool markedProfessor[SIZE] = {false};
    bool markedTopic[SIZE] = {false};
    bool markedRoom[SIZE] = {false};
    
    bool isCorrect = false;
    
    int currentPlayer =0;
    
    //Randomize one solution and mark it as chosen
    getSolution(solutions, SIZE);
    markSolution(markedProfessor, markedRoom, markedTopic, solutions);
    //Show who wants to take a turn
    displayTokens();
    
    for(int i=0; i<numOfPlayers;i++){
        if(i == solutions[i]){
            markedProfessor[i] = true;
            markedTopic[i] = true;
            markedRoom[i] =true;
        }
    }
    
    //MAIN LOOP OF THE GAME
    do{
        for(int i=0; i<numOfPlayers; i++){
            //Keep track of what was chosen and NOT the solutions
            bool isGuess = false;
            currentPlayer = i;
            
            //Display current player and main game menu
            cout<<tokens[players[i][0]]<<" is up!"<<endl;
            displayGameMenu();
            cin>>menuAnswer;
            
            //Give a random token,room,topic to current user and output inputted file
            if(menuAnswer=='d' || menuAnswer=='D'){
                giveClues(outFile, currentPlayer, players, tokens, rooms, topics, solutions);
                displayFile(iFile);
            }
            
            //User guess: prompt user for their guess and check against current solution. Output if wrong or right
            if (menuAnswer=='g' || menuAnswer=='G'){
                currentPlayer = i;
                isGuess = true;
                makeGuess(userGuess, tokens, rooms, topics, guessSize);
                isCorrect = compareGuess(userGuess, solutions);
                
                if(isCorrect == true){
                    displaySolution(solutions, tokens, rooms, topics);
                    return 0;
                }
                
                //Get the guesses from the user and write it to their file
                tokenGuess = userGuess[0];
                roomGuess = userGuess[1];
                topicGuess = userGuess[2];
                writeToFile(outFile, currentPlayer, tokens, rooms, topics, tokenGuess, roomGuess, topicGuess, isGuess);
            }
            
            //Skip current player's turn
            if(menuAnswer=='e' || menuAnswer=='E'){
                continue;
                
            }
            
            //Display the solution and quit the program
            if (menuAnswer=='s' || menuAnswer =='S'){
                displaySolution(solutions, tokens, rooms, topics);
                return 0;
            }
        }    
    }while(menuAnswer!='s' && menuAnswer!='S');
    
    return 0;
}

/* compares the int values of gusess[] and solution[] and return true if all 3 elements are equal
 * guess[] - array that stores user guesses
 * solution[] - array that stores the randomized solution
 */
bool compareGuess(int guess[], int solution[]){
    int isTrue = 0; //Number of elements that are true
    
    //Check the guess against the solution
    for(int i = 0; i<3; i++){
        if(guess[i] == solution[i])
        isTrue++;
    }
    
    //Check if all 3 elements are the solution
    if (isTrue == 3){
        cout<<"Your guess was correct!"<<endl;
        return true;
    }
    else{
        cout<<"Some guesses are incorrect"<<endl;
        return false;
    }
}

/*Gets random number between 0 and numOfChoices-1*/
int getRandom(int numOfChoices){
    return rand() % numOfChoices;
}

/* Returns a random item from the token, room, and topics arrays
 * while keeping track of which items have already been chosen
 * storedGuesses - items have already been selected
 * size - size of the bool array
 * return - randomized index that hasn't been chosen
 */ 
int getRandomItem(bool storedGuesses[], int sizeBool){
    int randomIndex; //Randomized index
    //Get a random item
    do{
        randomIndex = getRandom(sizeBool);
        
        if(storedGuesses[randomIndex] == false){
           break;
        }
    }while(storedGuesses[randomIndex] == true);
    
    storedGuesses[randomIndex] = true;
    return randomIndex;
}

/* Generates a random solution for user to guess */
void getSolution(int solutions[], int solutionSize){
    int randomIndex; //Stores a random index to choose from
    srand(time(NULL)); //Randomize each time game is played

    //Get a random solution
    randomIndex = rand() % solutionSize;
    solutions[0] = randomIndex;
    solutions[1] = randomIndex;
    solutions[2] = randomIndex;
}

/* giveOutClues - randomly distributes items that is not the solution
 * outFile - write guesses to player file
 * numberOfPlayers - number of players playing the game
 * players - each player room and topic
 * tokens[] - string token 
 * rooms [] - string room 
 * topics [] - string topics
 * solution - token, room, topic
 */ 
void giveClues(ofstream &outFile, int numOfPlayers, int players[][2], string tokens[], string rooms[], string topics[], int solutions[]){
    int boolSize = 5; //Size bool array can hold
    guessesBool[solutions[0]] =true;

    //Write a randomized clue to user file if they chose to display file
    int randomIndex = getRandomItem(guessesBool, boolSize);
    guessesBool[randomIndex] = true;
    outFile.open(tokens[players[numOfPlayers][0]]+"_guesses.txt", ios::app);
    outFile<<tokens[randomIndex]<<","<<rooms[randomIndex]<<","<<topics[randomIndex]<<endl;
    outFile.close();
}

/* displays the choices user can guess from (token room and topic) and stores their guess in the guess[] array as an index?
 * guess - store user guess
 * guessSize - size of the guess[] array
 */
int guessItem(int guess[], int guessSize){
    int userGuess =0; //Return value
    
    do{
        //Prompt token option
        cout<<"**********************"<<endl;
        cout<<"Enter a choice:"<<endl;
        cout<<"Enter 0 for Andro-Vasko"<<endl;
        cout<<"Enter 1 for Fonesca"<<endl;
        cout<<"Enter 2 for Jorgensen"<<endl;
        cout<<"Enter 3 for Martin"<<endl;
        cout<<"Enter 4 for Rafalski"<<endl;
        cout<<"**********************"<<endl;
        
        cin>>userGuess; //Get user input
        
        //Check if input is valid
        if(cin.fail() || (userGuess<0 || userGuess>4)){
            cin.clear();
            cin.ignore(100, '\n');
            cout<<"Error, please try again"<<endl;
            continue;
        }
        
    }while(userGuess<0 || userGuess>4);
    
    guess[0] = userGuess; //Assign guess token to array

    do{
        //Prompt room option
        cout<<"**********************"<<endl;
        cout<<"Enter a choice:"<<endl;
        cout<<"Enter 0 for CS172"<<endl;
        cout<<"Enter 1 for CS361"<<endl;
        cout<<"Enter 2 for CS176"<<endl;
        cout<<"Enter 3 for CS301"<<endl;
        cout<<"Enter 4 for CS175"<<endl;
        cout<<"**********************"<<endl;
        
        cin>>userGuess; //Get input
        
        //Check if input is valid
        if(cin.fail() || (userGuess<0 || userGuess>4)){
            cin.clear();
            cin.ignore(100, '\n');
            cout<<"Error, please try again"<<endl;
            continue;
        }
        
    }while(userGuess<0 || userGuess>4);
    
    guess[1] = userGuess; //Store next guess in array
    
    do{
        //Prompt topic options
        cout<<"**********************"<<endl;
        cout<<"Enter a choice:"<<endl;
        cout<<"Enter 0 for compilers"<<endl;
        cout<<"Enter 1 for object oriented programming"<<endl;
        cout<<"Enter 2 for assembly"<<endl;
        cout<<"Enter 3 for algorithms"<<endl;
        cout<<"Enter 4 for intro to programming"<<endl;
        cout<<"**********************"<<endl;
        
        cin>>userGuess; //Get user input
        
        //Check for invalid input
        if(cin.fail() || (userGuess<0 || userGuess>4)){
            cin.clear();
            cin.ignore(100, '\n');
            cout<<"Error, please try again"<<endl;
            continue;
        }
    
    }while(userGuess<0 || userGuess>4);
    
    guess[2] = userGuess; //Assign last value to array
    
    return userGuess; //Return user guess
    
}

/* Sets the guesses array to be compared to the solutions array
 * guesses - guesses by player
 * tokens[] - string token names
 * rooms [] - string rooms
 * topics [] - string topic names
 * size - size of each item array
 */
void makeGuess(int guesses[], string tokens[], string rooms[], string topics[], int size){
    //Calls guess item 
    guessItem(guesses, size); 
}

/* Tracks which index is the solution.
 * trackTokens - bool keeps solution token
 * trackRooms - bool keeps solution room
 * track Topics - bool keeps solution topic
 * solution - token, room, topic
 */
void markSolution(bool trackTokens[], bool trackRooms[], bool trackTopics[], int solutions[]){
    for(int i =0; i<SIZE; i++){
        if(i == solutions[i]){
            trackTokens[i] = true;
            trackRooms[i] = true;
            trackTopics[i] = true;
        }
    }
}

/* Writes a players guesses to a file using guess array
 * outFile - write to player file
 * player - int of current player token
 * tokens[] - string tokens
 * rooms [] - string rooms
 * topics [] - string topics
 * tokenGuess - int of player guessed token
 * roomGuess - int of player guessed room
 * topicGuess - int of player guessed topic
 * isGuess - bool true if writing during guess option
 */ 
void writeToFile(ofstream &outFile, int playerIndex, string tokens[], string rooms[], string topics[], int tokenGuess, int roomGuess, int topicGuess, bool isGuess){
    if(isGuess==true){
        outFile.open(tokens[playerIndex]+"_guesses.txt");
        outFile<<tokens[tokenGuess]<<" "<<rooms[roomGuess]<<" "<<topics[topicGuess]<<endl;
        outFile.close();
    }
}