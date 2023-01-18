#include <stdio.h>
#include <stdlib.h>
typedef int DATA; // defines the type of data on the binary tree

typedef struct node {
    DATA info;
    struct node *left;
    struct node *right;
}node;
typedef node* binaryTree; 

// allocates memory and free for a binary tree
binaryTree* create();
void destroy(binaryTree *bt);
void freeNode(node *n);

int insertTree(binaryTree *bt, DATA value); // returns -1 if error, 0 if already exists, 1 if inserted
int removeTree(binaryTree *bt, DATA value); // returns -1 if error, 0 if not found, 1 if removed
node* removeNode(node* removedNode);

int search(binaryTree *bt, DATA value); // returns -1 if error, 0 if not found, 1 if found
int isEmpty(binaryTree *bt); // returns -1 if error, 0 if not empty, 1 if empty
int size(binaryTree *bt); // returns -1 if error, else the size of the tree
int height(binaryTree *bt); // returns -1 if error, else the height of the tree

void printPreOrder(binaryTree *bt); // prints the tree in pre-order
void printInOrder(binaryTree *bt); // prints the tree in-order
void printPostOrder(binaryTree *bt); // prints the tree in post-order