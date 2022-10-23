/* Name: Stephaney Chang
   NSHEID: 2001508920
   Class: CS 302
   Assignment: 3
   Description: Header file for assignment 4
*/

#include <iostream>
#include <string>

class binTree {
  struct binTreeNode {
    char letter;
    int frequency;
    binTreeNode *left, *right;
  };

public:
  // Construtors
  binTree();
  binTree(char, int);
  binTree(binTree *, binTree *);
  ~binTree();

  // Misc functions
  int getFrequency() const;
  std::string getPrefixCode(char);

private:
  std::string getPrefixCode(binTreeNode *, char);
  void destroyTree(binTreeNode *);

  // Variables
  binTreeNode *root;
};

// CONSTRUCTORS
binTree::binTree() { root = nullptr; }

binTree::binTree(char letter, int frequency) {
  root = new binTreeNode;
  root->letter = letter;
  root->frequency = frequency;

  // Set children to nulls
  root->left = nullptr;
  root->right = nullptr;
}

binTree::binTree(binTree *t1, binTree *t2) {
  // Constructor combines two trees together
  root = new binTreeNode;
  root->letter = '\0';
  root->left = t1->root;
  root->right = t2->root;
  root->frequency = root->left->frequency + root->right->frequency;
}

binTree::~binTree() { destroyTree(root); }

void binTree::destroyTree(binTreeNode *r) {
  // REcursive deallocate post order

  // Check if tree is empty
  if (r == nullptr) {
    return;
  }

  destroyTree(r->left);
  destroyTree(r->right);

  delete r;
}

int binTree::getFrequency() const { return root->frequency; }

std::string binTree::getPrefixCode(char letter) {
  std::string code = binTree::getPrefixCode(root, letter);

  return code;
  
}

std::string binTree::getPrefixCode(binTreeNode *r, char letter) {
  std::string code;
  
  if (r==nullptr){
    return nullptr;
  }

  if(r->letter == letter){
    code = letter;
    return code;
  }

  return binTree::getPrefixCode(r, letter);
}
