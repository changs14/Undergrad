/* Name: Stephaney Chang
   NSHEID: 2001508920
   Class: CS 302
   Assignment: 1
   Description:
*/

#include <iostream>

using namespace std;

template <typename T>
class LL{

    // contents of each node
    struct Node{
    T data;
    Node* prev;
    Node* next;
    };

    // iterator class to allow access of each node in main
    public:
        class Iterator{
            public:
                friend class LL;
                Iterator (); //Done
                Iterator(Node *); //Done
                T operator *() const;
                const Iterator& operator ++(int);
                const Iterator& operator --(int);
                bool operator ==( const Iterator &) const;
                bool operator !=( const Iterator &) const;

            private:
                Node* current;
        };

        //Constructors
        LL(); //Done
        LL(const LL <T>&);
        const LL <T>& operator =(const LL<T>&);

        //Deconstrucors
        ~LL();  //Done

        //Other functions
        void headInsert(const T&);
        void tailInsert(const T&);
        Iterator begin () const;
        Iterator end() const;
        void swapNodes(Iterator&, Iterator &);

    private:
        Node* head; //Leftmost node
        Node* tail; //Rightmost node
};

/********************************** ITERATOR CLASS FUNCTIONS ***************************************/


/* Iterator - default constructor sets current to null*/
LL<T>::Iterator::Iterator(){
    current = nullptr;
}

/* Iterator(Node* ptr) - constructor that sets current to ptr*/
LL<T>Iterator::Iterator(Node* ptr){
    current = ptr;
}

/* Iterator::operator* () const - Overload the dereference operator. REturn data of node that Iterator object is pointing to*/
T LL<T>::Iterator::operator*() const{
    return *this;
}

/* const Iterator::oprator++(int) - post fix ++ opeartor that moves the iterator object one node to the right*/
const typename LL<T>::Iterator& LL<T>::Iterator::operator++(int){

}

/* const Iterator::operator--(int) - post fix operator that moves the iterator object on enode to the left*/
const typename LL<T>::Iterator& LL<T>::Iterator::operator++(int){

}

/* LL<T>::operator==(const ITerator& rhs) - comparison operator comapres *this Iterator and rhs Iterator. check if they point to the same node
   Return true if they do, otherwise return false*/
bool LL<T>::operator==(const Iterator& rhs) const{
    return (rhs == *this);
}

/* LL<T>::operator!=(const Iterator& rhs) const - comparison operator compares *this iterator and rhs point to a different node.
   Return true if they do otherwise return false*/
bool LL<T>::operator!=(const Iterator& rhs) const{
    return (rhs != *this);
}


/************************************ LL CLASS FUNCTIONS *****************************************/

/* LL constructor - assigns head and tail to null*/
LL<T>::LL(){
    head = nullptr;
    tail = nullptr;
}

/* Default constructor for class LL. Deep copy the copy object into the *this object*/
LL<T>::LL(const LL<T>& copy){   
    head = nullptr;
    tail = nullptr;

    *this = copy;
}

/* Deep copy assignment operator deep copy rhs to *this */
const LL<T>& LL<T>::operator=(const LL<T>& rhs){
    //Deallocate *this object (left hand side or lhs)
    //Perform deep copy
    //Check for self assignment

    return *this;
}

/* Destructor for linked list*/
LL<T>::~LL<T>(){
    //Deallocate the linked list
    Node * tempNode = head; //firstNode of the list
    Node * newNode = tempNode; //Node next to the current head
    Node * tempNode2 = tails; //last node of the list

    while(tempNode!=nullptr){
        newNode = tempNode->next;   //Assign new node to the next node in the list
        delete tempNode; //Delete the current head
        tempNode = newNode; //the first node becomes the new node
    }

    //Clear values of head and tail
    head = nullptr;
    tail = nullptr;
}

/* Insert a new node to the front  of the linked list. Node data field must contain the contents in the item parameter.*/
void LL<T>::headInsert(const T& item){

}

/* Insert a new node to the back of the linked list*/
void LL<T>::tailInsert(const T& item){

}

/* Returns an Iterator bject whose current field contains this->head*/
typename LL<T>::Iterator LL<T>::begin() const{

}


/* Returns an iterator object who contains this->tail*/
typename LL<T>::Iterator LL<T>::end() const{

}

/* Swap the location of node 1 it1.current with location of it2.current.*/  
void LL<type>::swapNodes(Iterator& it1, Iterator& it2){

}