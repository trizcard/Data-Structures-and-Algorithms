#include "binaryTree.h"

binaryTree* create(){
    binaryTree *bt = (binaryTree*) malloc(sizeof(binaryTree));
    if(bt != NULL){
        *bt = NULL;
    }
    return bt;
}
void destroy(binaryTree *bt){
    if(bt != NULL){
        freeNode(*bt);
        free(bt);
    }
}

// free node recursively
void freeNode(node *n){
    if(n == NULL){
        return;
    }
    freeNode(n->left);
    freeNode(n->right);
    free(n);
}

int insertTree(binaryTree *bt, DATA value){
    if(bt == NULL){ // if tree is not created yet or is already freed returns ERROR
        return -1;
    }
    node *newNode = (node*) malloc(sizeof(node)); // creates and allocate a new node
    if(newNode == NULL){ // if there is no memory available returns ERROR
        return -1;
    }

    newNode->info = value; // sets the value of the new node
    newNode->left = NULL; // sets the left child of the new node to NULL
    newNode->right = NULL; // sets the right child of the new node to NULL

    if(*bt == NULL){ // if the tree is empty, the new node is the root
        *bt = newNode;
    }
    else{
        node *currentNode = *bt;
        node *previousNode = NULL;

        while (currentNode != NULL){ // go through the whole tree
            previousNode = currentNode; 

            if (currentNode->info == newNode->info){
                free(newNode);
                return 0;
            }
            else if (currentNode->info > newNode->info){ // go to the left if new value is lesser than the node
                currentNode = currentNode->left;
            }
            else{ // go to the left if new value is greater than the node
                currentNode = currentNode->right;
            }
        }

        if (previousNode->info > newNode->info){ // insert on the left if value is lesser than the previous node
            previousNode->left = newNode;
        }
        else{ // insert on the right
            previousNode->right = newNode;
        }
        return 1; // sucess
    }
}

int removeTree(binaryTree *bt, DATA value){
    if(bt == NULL){ // if tree is not created yet or is already freed returns ERROR
        return -1;
    }

    if(*bt == NULL){ // if the tree is empty, return that value does not exist
        return 0;
    }
    
    node *currentNode = *bt;
    node *previousNode = NULL;

    while (currentNode != NULL){ // go through the whole tree
        if (currentNode->info == value){
            if (*bt == currentNode){
                *bt = removeNode(currentNode);
            }
            else if (previousNode->left == currentNode){
                previousNode->left = removeNode(currentNode);
            }
            else{
                previousNode->right = removeNode(currentNode);
            }
            return 1;
        }
        previousNode = currentNode;
        if (currentNode->info > value){ // go to the left if new value is lesser than the node
            currentNode = currentNode->left;
        }
        else{ // go to the left if new value is greater than the node
            currentNode = currentNode->right;
        }
    }
    return 0; // value isn't on the tree
}
node* removeNode(node* removedNode){
    node *firstNode, *secondNode;

    if (removedNode->left == NULL){
        secondNode = removedNode->right;
        free(removedNode);
        return(secondNode);
    }
    
    firstNode = removedNode;
    secondNode = removedNode->left;

    // search for the farthest node on the right, therefor, the highest value before the removed value
    while (secondNode->right != NULL){
        firstNode = secondNode;
        secondNode = secondNode->right;
    }

    if (firstNode != removedNode){
        firstNode->right = secondNode->left; // change the second node child to a first node child
        secondNode->left = removedNode->left; // second node occupies the removed node place
    }
    secondNode->right = removedNode->right;

    free(removedNode);
    return (secondNode);
}

int search(binaryTree *bt, DATA value){
    if(bt == NULL){ // if tree is not created yet or is already freed returns ERROR
        return -1;
    }

    if(*bt == NULL){ // if the tree is empty, return that value does not exist
        return 0;
    }
    
    node *currentNode = *bt;

    while(currentNode != NULL){
        if (currentNode->info == value){
            return 1;
        }
        else if (value < currentNode->info){
            currentNode = currentNode->left;
        }
        else{
            currentNode = currentNode->right;
        }
    }
    
    return 0;
}
int isEmpty(binaryTree *bt){
    if (bt == NULL){
        return -1;
    }
    if (*bt == NULL){
        return 1;
    }
    return 0;
}
int sizeRec(node *node){
    int size = 0;
    if(node->left != NULL){
        size += sizeRec(node->left);
    }
    if (node->right != NULL){
        size += sizeRec(node->right);
    }
    size++;
    return size;
}
int size(binaryTree *bt){
    if (bt == NULL){
        return -1;
    }
    if (*bt == NULL){
        return 0;
    }
    int size;
    size = sizeRec(*bt);
}
int heightRec(node *node){
    int height = 0;
    int heightLeft = 0, heightRight = 0;
    if(node->left != NULL){
        heightLeft = sizeRec(node->left);
    }
    if (node->right != NULL){
        heightRight = sizeRec(node->right);
    }

    if (heightLeft > heightRight){
        height += heightLeft;
    }
    else{
        height += heightRight;
    }
    height++;
    return height;
}
int height(binaryTree *bt){
    if (bt == NULL){
        return -1;
    }
    if (*bt == NULL){
        return 0;
    }
    return heightRec(*bt);
}

void printPreOrder(node *node){
    if(node == NULL){
        return;
    }
    if (node != NULL){
        printf("%d\n", node->info);
        printPreOrder(node->left);
        printPreOrder(node->right);
    }
}
void printInOrder(node *node){
    if(node == NULL){
        return;
    }
    if (node != NULL){
        printInOrder(node->left);
        printf("%d\n", node->info);
        printInOrder(node->right);
    }
}
void printPostOrder(node *node){
    if(node == NULL){
        return;
    }
    if (node != NULL){
        printPostOrder(node->left);
        printPostOrder(node->right);
        printf("%d\n", node->info);
    }
}