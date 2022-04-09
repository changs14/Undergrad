/* Stephaney Chang, 2001508920, CS202 Assignment 5
 * Description: This program mimics a coin box. Users can
 * print coins, use arithmetic, compare boxes, add coins and increment
 * coins based on menu input. 
 * Input: User input for menu selection
 * Output: Overloading of coins using arithmetic, comparison
 * assignment, etc.
 */

#include "americanCoinType.h"

using namespace std;

/************CONSTRUCTORS************/

/*Constructor: Initializes variables to 0 by default*/
coinsBox::coinsBox(){
    penny = 0;
    nickel = 0;
    dime = 0;
    quarter =0;
    fifty_centpiece = 0;
    name = new char[LEN];
}

/*Constructor: Inits and assigns member values based on input*/
coinsBox::coinsBox(int p, int nick, int d, int q, int f, char nam[LEN]){
    penny = p;
    nickel = nick;
    dime = d;
    quarter = q;
    fifty_centpiece = f;
    name = nam;
}

/*********DESTRUCTOR***********/

/*Destructor: Deletes the memory allocated in "name" member variable*/
coinsBox::~coinsBox(){
    delete [] name;
    name = nullptr;
}

/*********FRIEND FUNCTIONS********/

/* << operator overloading: Overload the << operator and print the
   contents of coin box, amount on cent and dollars, and address */
ostream &operator<<(ostream &out, const coinsBox &box){
    //Get cent and dollar amount for box and assign to var
    double cent = box.getTotalAmountinCent();
    double dollas = box.getTotalAmountinDollars();

    //Print the results of the coin box
    out<<box.name<<": ";
    out<<"Penny = "<<box.penny<<"; ";
    out<<"Nickel = "<<box.nickel<<"; ";
    out<<"Dime = "<<box.dime<<"; ";
    out<<"Quarter = "<<box.quarter<<"; ";
    out<<"Fifty Cent Piece = "<<box.fifty_centpiece<<"; ";
    out<<"Cent = "<<cent<<"; ";
    out<<"Dollars = "<<dollas<<"; ";
    out<<"Address = "<<&box.name;

    return out;
}

/* >> operator overloading: Overload input operator and ask user for 
   amount of coins for each coin type for and print the new results*/
istream &operator>>(istream &in, coinsBox &box){
    coinsBox newBox; //New temp box
    //Get uesr input for each coin type and add it
    //to the current box
    cout<<"Penny: "<<endl;
    in>>newBox.penny;
    box.penny = box.penny + newBox.penny;
    cout<<"Nickel: "<<endl;
    in>>newBox.nickel;
    box.nickel = box.nickel + newBox.nickel;
    cout<<"Dime: "<<endl;
    in>>newBox.dime;
    box.dime = box.dime + newBox.dime;
    cout<<"Quarter: "<<endl;
    in>>newBox.quarter;
    box.quarter = box.quarter + newBox.quarter;
    cout<<"Fifty Centpiece: "<<endl;
    in>>newBox.fifty_centpiece;
    box.fifty_centpiece = box.fifty_centpiece + newBox.fifty_centpiece;

    return in;
}

/*********GET COUNT FUNCTIONS***********/

/* Return amount of pennies*/
int coinsBox::getPennyCount() const{
    return penny;
}

/*Return amount of nickels */
int coinsBox::getNickelCount() const{
    return nickel;
}

/*Return amount of dimes*/
int coinsBox::getDimeCount() const{
    return dime;
}

/*Return amount of quarters*/
int coinsBox::getQuarterCount() const{
    return quarter;
}

/*Return amount of fifty cent piece*/
int coinsBox::getFiftycentpieceCount() const{
    return fifty_centpiece;
}

/*Calculate and return the total amount of coin in cents*/
double coinsBox::getTotalAmountinCent() const{
    double cent = 0.0; //Variable to hold cent amount
    //Calculate the total coins in cents
    cent = penny + (nickel*5) + (dime*10) + (quarter*25) + (fifty_centpiece *50);

    return cent;
}

/*Calculate the amount of dollars using total amount of cents and return*/
double coinsBox::getTotalAmountinDollars() const{
    double dollars = 0.0; //Variable to hold dollar amount
    double cents = getTotalAmountinCent(); //Hold cent amount
    dollars = cents/100; //Convert cent to dollars

    return dollars;
}

/*********SET FUNCTIONS************/

/* Assigns a value to penny member*/
void coinsBox::setPennyCount(int c){
    penny = c;
}

/*Assigns a value to nickel member*/
void coinsBox::setNickelCount(int c){
    nickel = c;
}

/*Assigns a value to dime member*/
void coinsBox::setDimeCount(int c){
    dime = c;
}

/*Assigns a value to quarter member*/
void coinsBox::setQuarterCount(int c){
    quarter = c;
}

/*Assigns a value to fiftycentpiece member*/
void coinsBox::setFiftycentpieceCount(int c){
    fifty_centpiece = c;
}

/*Assigns a name to the coin box via string*/
void coinsBox::setName(string s){
    //Go through string and assign name to the box
    for(int i=0;i<s.length();i++){
        name[i] = s[i];
    }
}

/********** ARITHMETIC OVERLOAD ************/

/* Operator + overloading. Create a new temp box and add 
   the coins in box 1 and 2 and assign the total to temp box*/
coinsBox coinsBox::operator+(const coinsBox &box) const{
    coinsBox newBox; //Create new box

    //Add box 1 and 2 and assign the new value to the new box
    newBox.penny = this->penny + box.penny;
    newBox.nickel = this->nickel + box.nickel;
    newBox.dime = this->dime + box.dime;
    newBox.quarter = this->quarter + box.quarter;
    newBox.fifty_centpiece = this->fifty_centpiece + box.fifty_centpiece;
    newBox.getTotalAmountinCent();
    newBox.getTotalAmountinDollars();

    return newBox;

}

/*Operator - overloading: Create temp box and subtract the
  coins in box 1 and 2 and assign total to temp box */
coinsBox coinsBox::operator-(const coinsBox &box) const{
    coinsBox newBox; //Create new temp box

    //Subtract from current box to next box and assign the value to a new box
    newBox.penny = this->penny - box.penny;
    newBox.nickel = this->nickel - box.nickel;
    newBox.dime = this->dime - box.dime;
    newBox.quarter = this->quarter - box.quarter;
    newBox.fifty_centpiece = this->fifty_centpiece - box.fifty_centpiece;
    newBox.getTotalAmountinCent();
    newBox.getTotalAmountinDollars();

    return newBox;

}

/* Operator * overloading: Create a new box and multiply
   box 1 and 2 and assign new value to temp box */
coinsBox coinsBox::operator*(const coinsBox &box) const{
    coinsBox newBox; //Create new temp box

    //Multiply current box coins and next box and assign it to the new box
    newBox.penny = this->penny * box.penny;
    newBox.nickel = this->nickel * box.nickel;
    newBox.dime = this->dime * box.dime;
    newBox.quarter = this->quarter * box.quarter;
    newBox.fifty_centpiece = this->fifty_centpiece * box.fifty_centpiece;

    return newBox;
}

/************ASSIGNMENT OVERLOAD*************/

/*Operator = overloading. Assign new values to the memeber values and return current box*/
coinsBox& coinsBox::operator=(const coinsBox &box){
    //Assign inputted box values to current box
    penny = box.penny;
    nickel = box.nickel;
    dime = box.dime;
    quarter = box.quarter;
    fifty_centpiece = box.fifty_centpiece;
    name = box.name;

    return *this;
}

/*Operator overloading -=. Minus box values from memeber values and return*/
coinsBox& coinsBox::operator-=(const coinsBox &box){
    //-= box2 from box 1 
    penny -= box.penny;
    nickel -= box.nickel;
    dime -= box.dime;
    quarter -= box.quarter;
    fifty_centpiece -= box.fifty_centpiece;

    //If values less than 0, set coins value to 0
    if(penny<0 && nickel<0 && dime<0 && quarter<0 && fifty_centpiece<0){
        penny = 0;
        nickel =0;
        dime = 0;
        quarter =0;
        fifty_centpiece=0;
    }
    
    return *this;
}

/**********INCREMENT/DECREMENT OVERLOAD***********/

/* ++ overloading: Post-increment the coins and return*/
coinsBox coinsBox::operator++(){
    //Post-increment the coins 
    penny++;
    nickel++;
    dime++;
    quarter++;
    fifty_centpiece++;

    return *this;
}

/* ++ overloading: Pre-increment the coins and return */
coinsBox coinsBox::operator++(int a){
    //Pre-increment the coins 
    ++penny;
    ++nickel;
    ++dime;
    ++quarter;
    ++fifty_centpiece;

    return *this;
}

/* -- overloading: post-decrement coins. If over 0, return else
  return 0 for negative numbers */
coinsBox coinsBox::operator--(){
    //Decrement the coins
    penny--;
    nickel--;
    dime--;
    quarter--;
    fifty_centpiece--;

    //Check if the values are negative and if so, make each coin = 0
    if(penny<0 && nickel<0 && dime<0 && quarter<0 && fifty_centpiece<0){
        penny = 0;
        nickel =0;
        dime = 0;
        quarter =0;
        fifty_centpiece=0;
    }

    return *this;
}

/* -- overloading: pre-decrement coins. If over 0, return else
  return 0 for negative numbers */
coinsBox coinsBox::operator--(int a){
    //Pre-decrement coins
    --penny;
    --nickel;
    --dime;
    --quarter;
    --fifty_centpiece;

    //Check if the values are negative and if so, make each coin = 0
    if(penny<0 && nickel<0 && dime<0 && quarter<0 && fifty_centpiece<0){
        penny = 0;
        nickel =0;
        dime = 0;
        quarter =0;
        fifty_centpiece=0;
    }

    return *this;
}

/*************RELATIONAL OVERLOAD************/

/* Return bool true if all coins in the box 1 and 2 are equal, else return false*/
bool coinsBox::operator==(const coinsBox &box) const{
    return (penny==box.penny && nickel == box.nickel && dime == box.dime &&
            quarter == box.quarter && fifty_centpiece == box.fifty_centpiece);
}

/*Return true if all coins in box 1 and 2 do NOT equal, else return false*/
bool coinsBox::operator!=(const coinsBox & box) const{
    return (penny!=box.penny && nickel != box.nickel && dime != box.dime &&
            quarter != box.quarter && fifty_centpiece != box.fifty_centpiece);
}

/*Return true if all coins from box 1 is less than or equal to 2 else return false*/
bool coinsBox::operator<=(const coinsBox &box) const{
    return (penny<=box.penny && nickel <= box.nickel && dime <= box.dime &&
            quarter <= box.quarter && fifty_centpiece <= box.fifty_centpiece);
}

/*Return true if all coins from box 1 is less than box 2 else return false*/
bool coinsBox::operator<(const coinsBox &box) const{
    return (penny<box.penny && nickel<box.nickel && dime<box.dime &&
            quarter<box.quarter && fifty_centpiece<box.fifty_centpiece);
}

/*Return true if all coins in box 1 is greater than or equal to box 2 else return false*/
bool coinsBox::operator>=(const coinsBox &box) const{
    return (penny>=box.penny && nickel >= box.nickel && dime >= box.dime &&
            quarter >= box.quarter && fifty_centpiece >= box.fifty_centpiece);
}

/*Return true if all coins in box 1 is greater than box 2 else return false*/
bool coinsBox::operator>(const coinsBox &box) const{
    return (penny>box.penny && nickel>box.nickel && dime>box.dime &&
            quarter>box.quarter && fifty_centpiece>box.fifty_centpiece);
}