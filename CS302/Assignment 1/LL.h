/* Name: Stephaney Chang
   NSHEID: 2001508920
   Class: CS 302
   Assignment: 1
   Description: Header file for function file LL.cpp and main program.
*/

#include <iostream>
//#include "LL.cpp"

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
                bool operator ==( const Iterator &) const; //Done
                bool operator !=( const Iterator &) const; //DOne

            private:
                Node* current;
        };

        //Constructors
        LL(); //Done
        LL(const LL <T>&); //Done
        const LL <T>& operator =(const LL<T>&);

        //Deconstrucors
        ~LL();  //Done

        //Other functions
        void headInsert(const T&); //Done
        void tailInsert(const T&); //Done
        Iterator begin () const;
        Iterator end() const;
        void swapNodes(Iterator&, Iterator &);  //Done?

    private:
        Node* head; //Leftmost node
        Node* tail; //Rightmost node
};

/********************************** ITERATOR CLASS FUNCTIONS ***************************************/


/* Iterator - default constructor sets current to null*/
template <typename T>
LL<T>::Iterator::Iterator(){
    current = nullptr;
}

/* Iterator(Node* ptr) - constructor that sets current to ptr*/
template <typename T>
LL<T>::Iterator::Iterator(Node* ptr){
    current = ptr;
}

/* Iterator::operator* () const - Overload the dereference operator. REturn data of node that Iterator object is pointing to*/
template <typename T>
T LL<T>::Iterator::operator*() const{
    return current->data;
}

/* const Iterator::oprator++(int) - post fix ++ opeartor that moves the iterator object one node to the right*/
template <typename T>
const typename LL<T>::Iterator& LL<T>::Iterator::operator++(int){
    this->current = this->current->next;
    return *this;
}

/* const Iterator::operator--(int) - post fix operator that moves the iterator object on node to the left*/
template <typename T>
const typename LL<T>::Iterator& LL<T>::Iterator::operator--(int){
    this->current = this->current->prev;  
    return *this;
}

/* LL<T>::operator==(const ITerator& rhs) - comparison operator comapres *this Iterator and rhs Iterator. check if they point to the same node
   Return true if they do, otherwise return false*/
template <typename T>
bool LL<T>::Iterator::operator==(const Iterator& rhs) const{
    return (rhs == *this);
}

/* LL<T>::operator!=(const Iterator& rhs) const - comparison operator compares *this iterator and rhs point to a different node.
   Return true if they do otherwise return false*/
template <typename T>
bool LL<T>::Iterator::operator!=(const Iterator& rhs) const{
    return (rhs != *this);
}


/************************************ LL CLASS FUNCTIONS *****************************************/

/* LL constructor - assigns head and tail to null*/
template <typename T>
LL<T>::LL(){
    head = nullptr;
}

/* Deep copy constructor for class LL. Deep copy the copy object into the *this object*/
template <typename T>
LL<T>::LL(const LL<T>& copy){   
    head = nullptr;
    tail = nullptr;

    //Deep copy copy object into *this
}

/* Deep copy assignment operator deep copy rhs to *this */
template <typename T>
const LL<T>& LL<T>::operator=(const LL<T>& rhs){
    if(&rhs != this){
        Node *curr = head;
        Node *nextNode;

        head = nullptr;

        while(curr != nullptr){
            nextNode = curr->next;
            delete curr;
            curr = nextNode;

        }

        Node * newNode = head;

        curr = rhs.head;

        while(curr != NULL){
            newNode = new Node;
            newNode->data = curr->data;
            newNode->next = nullptr;

            newNode = newNode->next;
            curr = curr->next;
        }
    }

    return *this;
}

/* Destructor for linked list*/
template <typename T>
LL<T>::~LL<T>(){
    //Deallocate the linked list
    Node * temp = head; //firstNode of the list
    Node * newNode = temp; //Node next to the current head

    while(temp!=nullptr){
        newNode = temp->next;   //Assign new node to the next node in the list
        delete temp; //Delete the current head
        temp = newNode; //the first node becomes the new node
    }

    //Clear values of head and tail
    head = nullptr;
    tail = nullptr;
}

/* Insert a new node to the front  of the linked list. Node data field must contain the contents in the item parameter.*/
template <typename T>
void LL<T>::headInsert(const T& item){
    Node * newNode = new Node;

    newNode->data = item;
    newNode->next = head;

    head = newNode;
}

/* Insert a new node to the back of the linked list*/
template <typename T>
void LL<T>::tailInsert(const T& item){
    Node * newNode = new Node;
    newNode->data = item;
    newNode->prev = tail;

    tail->next = newNode;
    tail = newNode;
}

/* Returns an Iterator object whose current field contains this->head*/
template <typename T>
typename LL<T>::Iterator LL<T>::begin() const{
    return head->next;
}


/* Returns an iterator object who contains this->tail*/
template <typename T>
typename LL<T>::Iterator LL<T>::end() const{
    return tail;
}

/* Swap the location of node 1 it1.current with location of it2.current.*/  
template <typename T>
void LL<T>::swapNodes(Iterator& it1, Iterator& it2){
    Node * temp = head; //First node of the list
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
        temp = nullptr;
    }
    else if(it2 == head){
        //Check if it2 is the head
        left = it2; //it2 = head so left = head;
        right = it1; //it1 is after the head
        temp = nullptr;
    }
    else{
        while(temp->next != nullptr)
        //While the next node is not the end of the list
        //Check if it1 is found first
        if(temp->next == it1){
            left = it1; //it1 is the head
            right = it2; //it2 comes after the head
            break;  //Swap is done
        }
        else if(temp->next == it2){
            left = it2; //it2 is the head
            right = it1; //it1 comes after the head
            break; //Swap is done
        }

        temp = temp->next; //Loop condition

    }

    if(temp == nullptr){
        //Swap nodes and update the current head
        head = right;
        left->next = right->next;
        right->next = left;
    }
    else{
        //Swap position of nodes and update the previous left node
        Node * previous = temp;
        previous->next = right;
        left->next = right->next;
        right->next = left;
    }

}

