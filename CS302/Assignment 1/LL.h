/* Name: Stephaney Chang
   NSHEID: 2001508920
   Class: CS 302
   Assignment: 1
   Description: Header file for function file LL.cpp and main program.
*/

#include <iostream>
#include "LL.cpp"

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
                const Iterator& operator ++(int); //Done
                const Iterator& operator --(int); //Done
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
        void headInsert(const T&); //Done
        void tailInsert(const T&); //Done
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
    next++;
    return *this;
}

/* const Iterator::operator--(int) - post fix operator that moves the iterator object on node to the left*/
const typename LL<T>::Iterator& LL<T>::Iterator::operator++(int){
    prev--;
    return *this;
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

    //Deep copy copy object into *this

    *this = copy;
}

/* Deep copy assignment operator deep copy rhs to *this */
const LL<T>& LL<T>::operator=(const LL<T>& rhs){
    //Deallocate *this object (left hand side or lhs)
    ~LL();

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
    Node * newNode = new Node;
    newNode->item = item;
    newNode->next = head;

    head = newNode;
}

/* Insert a new node to the back of the linked list*/
void LL<T>::tailInsert(const T& item){
    Node * newNode = new Node;
    newNode->item = item;
    newNode->prev = tail;

    tail = newNode;
}

/* Returns an Iterator object whose current field contains this->head*/
typename LL<T>::Iterator LL<T>::begin() const{

}


/* Returns an iterator object who contains this->tail*/
typename LL<T>::Iterator LL<T>::end() const{

}

/* Swap the location of node 1 it1.current with location of it2.current.*/  
void LL<type>::swapNodes(Iterator& it1, Iterator& it2){
    Node * tempNode = head; //First node of the list
    Node * left = nullptr; //Leftmost node
    Node * right = nullptr; //Rightmost node

    //Check if the nodes are the same
    if(it1 == it2 || head == nullptr){
        //Same node so no swapping can happen
        return;
    }

    //Check if either objects are the head
    if(it1 == head){
        left = it1; //it1 = head so left = head
        right = it2; //it2 is right after the head
        tempNode = nullptr;
    }
    else if(it2 == head){
        //Check if it2 is the head
        left = it2; //it2 = head so left = head;
        right = it1 //it1 is after the head
        tempNode = nullptr;
    }
    else{
        while(tempNode->next != nullptr)
        //While the next node is not the end of the list
        //Check if it1 is found first
        if(tempNode->next == it1){
            left = it1; //it1 is the head
            right = it2; //it2 comes after the head
            break;  //Swap is done
        }
        else if(tempNode=>next == it2){
            left = it2; //it2 is the head
            right = it1; //it1 comes after the head
            break; //Swap is done
        }

        tempNode = tempNode->next; //Loop condition

    }

    if(tempNode == nullptr){
        //Swap nodes and update the current head
        head = right;
        left->next = right->next;
        right->next = left;
    }
    else{
        //Swap position of nodes and update the previous left node
        Node * previous = tempNode;
        previous->next = right;
        left->next = right->next;
        right->next = left;
    }


}
