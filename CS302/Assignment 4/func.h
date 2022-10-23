/* Name: Stephaney Chang
   NSHEID: 2001508920
   Class: CS 302
   Assignment: 3
   Description: Header file for assignment 4
*/

#include <iostream>
#include <string>

class binTree
{
    struct binTreeNode
    {
        char letter;
        int frequency;
        binTreeNode * left, * right;
    };

    public:
        //Construtors
        binTree();
        binTree(char, int);
        binTree(binTree*, binTree*);
        ~binTree();
        
        //Misc functions
        int getFrequency() const;
        std::string getPrefixCode(char);

    private:
        std::string getPrefixCode(binTreeNode*, char);
        void destroyTree(binTreeNode*);

        //Variables
        binTreeNode * root;
};

//CONSTRUCTORS
binTree::binTree()
{
    root = nullptr;
}

binTree::binTree(char letter, int frequency)
{
    root = new binTreeNode;
    root.letter = letter;
    root.frequency = frequency;

    //Set children pointers to nullptr
}

binTree::binTree(binTree* t1; binTree* t2)
{
    //Constructor combines two trees together
    root = new binTreeNode;
    root.letter = '\0';
    root->left = t1.root;
    root->right = t2.root;
    root.frequency = t1.frequency + t2.frequency;
}

binTree::~binTree(){
    destroyTree(root);
}

void binTree::destroyTree(binTreeNode* r)
{
    //REcursive deallocate post order
}

void binTree::getFrequency() const
{
    return root.frequency;
}

std::string binTree::getPrefixCode(char letter)
{

}

std::string binTree::getPrefixCode(binTreeNode *r, char letter)
{

}
