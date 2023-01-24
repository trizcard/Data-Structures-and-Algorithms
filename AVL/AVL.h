#include <stdio.h>
#include <stdlib.h>
typedef int DATA; // defines the type of data on the binary tree

typedef struct node {
    DATA info;
    int height;
    struct node *left;
    struct node *right;
}node;
typedef node* AVL; 

// allocates memory and free for a binary tree
AVL* create();
void destroy(AVL *bt);
void freeNode(node *n);

int insertTree(AVL *bt, DATA value); // returns -1 if error, 0 if already exists, 1 if inserted
int removeTree(AVL *bt, DATA value); // returns -1 if error, 0 if not found, 1 if removed
void removeNode(AVL *bt);

// balance factor
int balanceFactor(node *node);
void rotationLL(AVL *bt);
void rotationRR(AVL *bt);
void rotationLR(AVL *bt);
void rotationRL(AVL *bt);

int search(AVL *bt, DATA value); // returns -1 if error, 0 if not found, 1 if found
int isEmpty(AVL *bt); // returns -1 if error, 0 if not empty, 1 if empty
int sizeRec(node *node); // recursive function
int size(AVL *bt); // returns -1 if error, else the size of the tree
int heightRec(node *node); // recursive function 
int height(AVL *bt); // returns -1 if error, else the height of the tree

void printPreOrder(node *node); // prints the tree in pre-order
void printInOrder(node *node); // prints the tree in-order
void printPostOrder(node *node); // prints the tree in post-order
