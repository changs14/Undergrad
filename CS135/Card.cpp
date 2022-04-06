#ifndef CARD_H
#define CARD_H
#include "Card.h"
#endif

/*******************************
 *  CARD CLASS 
*******************************/
Card::Card(){
    //Init the member values
    Suit = '\0';
    Value = '\0';
    Weight = -1;
}

/* Card constructor: Inits the values of suit value and weight*/
Card::Card(char suit, char value){
    Suit = suit; //Assign suit
    Value = value; //Assign value

    //Assign weight based on value
    switch(Value){
        case 'A':
            Weight = 14;
            break;
        case 'K':
            Weight = 13;
            break;
        case 'Q':
            Weight = 12;
            break;
        case 'J':
            Weight = 11;
            break;
        case 'T':
            Weight = 10;
            break;
        case '9':
            Weight = 9;
            break;
        case '8':
            Weight = 8;
            break;
        case '7':
            Weight = 7;
            break;
        case '6':
            Weight =6;
            break;
        case '5':
            Weight = 5;
            break;
        case '4':
            Weight =4;
            break;
        case '3':
            Weight = 3;
            break;
        case '2':
            Weight = 2;
            break;
    }
}
/*Returns a string of a card based on suit and value*/
string Card::GetCard() const{
    string r; //Returning string to print
    string newS; //Suit as a string
    string newV; //Value as a string
    char s; //Current suit
    char v; //Current value

    //Get the suit and value of the card
    s = Suit;
    v = Value;

    //Assign the suit and value as a string
    newS =s;
    newV=v;

    r = "|[" + newS + newV + "]|";

    return r;
}

/*Returns true of false of LHS card is less than RHS card*/
bool Card::operator<(Card rhsCard) const{
    //Compare if current suit is less than RHS suit
    if(Suit<rhsCard.Suit){
        return (Suit<rhsCard.Suit);
    }
    else if(Suit == rhsCard.Suit){
        //Compare weight is suit is the same
        return(Weight<rhsCard.Weight);
    }
    else{
        return true;
    }
}

/*Return bool to compare the LHS deck to RHS deck*/
bool Card::operator>(Card rhsCard) const{
    //Compare if curr suit is larger than RHS suit
    if(Suit>rhsCard.Suit){
        return (Suit>rhsCard.Suit);
    }
    else if(Suit == rhsCard.Suit){
        //Compare weight if the suit is the same
        return(Weight>rhsCard.Weight);
    }
    else{
        return true;
    }
}

/*Return weight of a card*/
int Card::GetWeight() const{
    return Weight;
}

/*******************************
 *  DECK CLASS 
*******************************/
/*Deck Constructor: Init the members to NUll and 0*/
Deck::Deck(){ 
    Head = nullptr;
    SizeOfDeck = 0;
}

// Rule of Three
/*Deck Destructor: Delete nodes by calling ClearDeck() function*/
Deck::~Deck(){
    ClearDeck();
}

/*Operator = overloading. Clear the deck and assign new nodes 
 * and move the head to the next node while increasing deck size*/
void Deck::operator=(const Deck &copy){
    ClearDeck(); //Clear the deck
    Node * tempNode = copy.Head; //Copy node that holds the copy

    //Loop through the list
    for(int i=0;i<SizeOfDeck;i++){
        //Add card to deck
        AddToTopOfDeck(tempNode->card);
        //Update loop condition until end of deck
        tempNode = tempNode->next;
    } 
}

/*Deck copy constructor: Copy parameter*/
Deck::Deck(const Deck& copy){
    Head = nullptr;
    SizeOfDeck = 0;
    *this = copy;
}

/* operator [] overloading: Assign/move the current node to the next*/
Deck::Node* Deck::operator[](int index){
    Node * tempNode = Head; //Current node is the head
    //Index is invalid
    if(index<0 || index>=SizeOfDeck){
        return nullptr;
    }
    else{
        for(int i=0;i<index;i++){
            //Move the nodes to the next
            tempNode = tempNode->next;
        }
        return tempNode;
    }
}

// Member Functions
/*Add a new Node and assign it to the Head of the Deck and increase size*/
void Deck::AddToTopOfDeck(Card card){
    Node * newNode = new Node; //Allocate memory for new node

    newNode->card = card; //Save card data
    newNode->next = Head;//Current head is now the next one
    Head = newNode;//new node is now the Head

    SizeOfDeck++; //Increase deck size

}

/*Remove the first node of list and decrease size*/
Card Deck::RemoveTopCard(){
    Node * topCard = Head; //Hold data to delete
    Card oldCard = topCard->card; //Save the Head card data

    Head = Head->next; //Move the current Head to the next node
    SizeOfDeck--; //Decrease deck size
    delete topCard; //Deallocate the previous head node
    topCard = nullptr;

    return oldCard; //return data
}

/* Shuffles the nodes in the deck using SwapCards function*/
void Deck::ShuffleDeck(){  
    srand(time(NULL)); //Randomize time

    int size = GetSizeOfDeck() * 3; //Random iteration
    int random = 0;//Random index

    //Shuffle the deck
    for(int i=0;i<size;i++){
        random = GetRandomCardIndex(); //get random index
        SwapCards((*this)[random], (*this)[random+1]);//Swap position
    }
}

// This is essentially the Destructor. Has use outside of destructor
/*Clears the linked list. To be called in the destructor*/
void Deck::ClearDeck(){
    Node * tempNode = Head; //tempNode will be the first node
    Node * newNode = tempNode; //Will become the next node from the head

    //Loop throguh until the list is empty
    while(tempNode != nullptr){
        newNode = tempNode->next; //newNode is the node next to head
        delete tempNode; //Delete the head
        tempNode = newNode; //The new first node is newNode
    }   
    Head = nullptr; //Clear values
    SizeOfDeck = 0; //Clear deck size
}

/*Sorts the deck Nodes by using SwapCards function*/
void Deck::SortDeck(){
    int size = GetSizeOfDeck(); //Size of deck to iterate

    //Sort the deck
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            //LHS card is less than RHS card
            if( (*this)[j]->card < (*this)[j + 1]->card ){
                SwapCards((*this)[j], (*this)[j+1]); //Switch position
            }
        }
    }

}

/*Switches the position of two card nodes*/
void Deck::SwapCards(Node* A, Node* B){
    Node * tempNode = Head; //tempNode is the first node in list
    Node * L = nullptr; //Holds left node
    Node* R = nullptr; //Holds right node


    //Check if the cards can be swapped
    if(A==B || Head == nullptr){
        //Can't swap the same node
        return;
    }

    //Check if A or B is the Head node
    if(A==Head){
        L = A; //A left because it is the head
        R = B; //B is after the head
        tempNode = nullptr;
    }
    else if(B==Head){
        L = B; //B left because it is the head
        R = A; //A is after the head
        tempNode = nullptr;
    }
    //A or B is not the Head node
    else{
        while(tempNode->next != nullptr){
            //A is the left side because it was found first
            if(tempNode->next == A){
                L = A;
                R = B;
                break;
            }
            //B is left side because it was found first
            else if(tempNode->next ==B){
                L=B;
                R=A;
                break;
            }
            //Update condition of the loop
            tempNode = tempNode->next;
        }
    } 

    //Found the previous left, left card and right card
    if(tempNode == nullptr){
        //Switch positons of the card and update the Head
        Head = R;
        L->next = R->next;
        R->next = L;
        
    }  
    else{
        //Switch positions of the card and update the left-previous
        Node * previous = tempNode;
        previous->next = R;
        L->next = R->next;
        R->next = L;
    }
}

// Getters
int Deck::GetSizeOfDeck() const{
    return SizeOfDeck;
}

bool Deck::isEmpty() const{
    if(SizeOfDeck == 0){
        return true;
    }
    return false;
}

int Deck::GetRandomCardIndex() const{
    return (rand() % SizeOfDeck);
}

void Deck::PrintDeck(){
    cout << "-------------------------" << endl;
    for(int i = 0; i < SizeOfDeck; i++){
        cout << (*this)[i]->card.GetCard();
        if((i + 1) % 4 == 0){
            cout << endl;
        }
    }
     cout << endl << "-------------------------" << endl;
}