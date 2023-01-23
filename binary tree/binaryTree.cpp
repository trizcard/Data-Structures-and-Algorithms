#include <stdio.h>
#include <stdlib.h>
using namespace std;
typedef int DATA;

class node{
    private:
        DATA info;
        node *left = NULL;
        node *right = NULL;

    public:
        DATA getInfo();
        node* getLeft();
        node* getRight();
        int getSize();
        int getHeight();
        
        void setInfo(DATA);
        void setLeft(node*);
        void setRight(node*);

        void insert(DATA);
        node* removeNode();

        void printPreOrder();
        void printInOrder();
        void printPostOrder();
};

class binaryTree{
    private:
        node *root = NULL;
    
    public:
        bool insert(DATA);
        bool remove(DATA);
        bool search(DATA);

        bool isEmpty();
        int size();
        int height();

        void printPreOrder(); 
        void printInOrder(); 
        void printPostOrder();
};

// node methods
DATA node::getInfo(){
    return info;
}
node* node::getLeft(){
    return left;
}
node* node::getRight(){
    return right;
}
int node::getSize(){
    int size = 1;
    if(left != NULL){
        size += left->getSize();
    }
    if(right != NULL){
        size += right->getSize();
    }
    return size;
}
int node::getHeight(){
    int height = 1, leftNode = 0, rightNode = 0;
    if(left != NULL){
        leftNode = left->getHeight();
    }
    if(right != NULL){
        rightNode = right->getHeight();
    }
    if (leftNode > rightNode){
        height += leftNode;
    }
    else{
        height += rightNode;
    }
    return height;
}

void node::setInfo(DATA value){
    info = value;
}
void node::setLeft(node* n){
    left = n;
}
void node::setRight(node* n){
    right = n;
}

void node::insert(DATA value){
    info = value;
    left = NULL;
    right = NULL;
}
node* node::removeNode(){
    node *first, *second;

    if (left == NULL){
        second = right;
        return(second);
    }
    
    first->setInfo(info);
    first->setLeft(left);
    first->setRight(right);
    second = left;

    // search for the farthest node on the right, therefor, the highest value before the removed value
    while (second->getRight() != NULL){
        first = second;
        second = second->getRight();
    }

    if (first->getInfo() != info){
        first->setRight(second->getLeft()); // change the second node child to a first node child
        second->setLeft(left); // second node occupies the removed node place
    }
    second->setRight(right);

    return (second);
}

void node::printPreOrder(){
    if(this == NULL){
        return;
    }

    printf("%d\n", info);
    left->printPreOrder();
    right->printPreOrder();
}
void node::printInOrder(){
    if(this == NULL){
        return;
    }

    left->printInOrder();
    printf("%d\n", info);
    right->printInOrder();
}
void node::printPostOrder(){
    if(this == NULL){
        return;
    }

    left->printPostOrder();
    right->printPostOrder();
    printf("%d\n", info);
}

// binary tree methods
bool binaryTree::insert (DATA value){
    if (this == NULL){
        return false;
    }

    node *newNode = new node;
    newNode->insert(value);

    if(root == NULL){
        root = newNode;
        return true;
    }

    node *current = root;
    node *previous = NULL;

    while (current != NULL){
        previous = current;

        if (current->getInfo() == value){
            return false;
        }
        if (current->getInfo() > value){
            current = current->getLeft();
        }
        else{
            current = current->getRight();
        }
    }
    current = newNode;
    if(previous->getInfo() > newNode->getInfo()){
        previous->setLeft(newNode);
    }
    else{
        previous->setRight(newNode);
    }
    return true;
}
bool binaryTree::remove (DATA value){
    if (root == NULL){
        return false;
    }
    
    node *current = root;
    node *previous = NULL;

    while (current != NULL){
        if (current->getInfo() == value){
            if (root == current){
                root = current->removeNode();
            }
            else if (previous->getLeft() == current){
                previous->setLeft(current->removeNode());
            }
            else{
                previous->setRight(current->removeNode());
            }
            return true;
        }
        previous = current;

        if (current->getInfo() > value){
            current = current->getLeft();
        }
        else{
            current = current->getRight();
        }
    }

    return false;
}
bool binaryTree::search (DATA value){
    if (root == NULL){
        return false;
    }
    
    node *current = root;
    node *previous = NULL;

    while (current != NULL){
        previous = current;

        if (current->getInfo() == value){
            return true;
        }
        if (current->getInfo() > value){
            current = current->getLeft();
        }
        else{
            current = current->getRight();
        }
    }
    return false;
}

bool binaryTree::isEmpty(){
    return (root == NULL);
}
int binaryTree::size(){
    if (root == NULL){
        return 0;
    }
    return root->getSize();
}
int binaryTree::height(){
    if (root == NULL){
        return 0;
    }
    return root->getHeight();
}

void binaryTree::printPreOrder(){
    root->printPreOrder();
}
void binaryTree::printInOrder(){
    root->printInOrder();
}
void binaryTree::printPostOrder(){
    root->printPostOrder();
}

int main(){
    binaryTree bt;

    for (int i = 0; i < 8; i++){
        int value;
        printf("\nInserted value: ");
        scanf("%d", &value);
        bool insertionCheck;
        insertionCheck = bt.insert(value);
        if (insertionCheck) {
            printf("Insertion Sucess\n");
        }
        else{
            printf("Already on the tree or error\n");
        }
    }
    for (int i = 0; i < 8; i++){
        int value;
        printf("\nRemoved value: ");
        scanf("%d", &value);
        bool remotionCheck;
        remotionCheck = bt.remove(value);
        if (remotionCheck) {
            printf("Remotion Sucess\n");
        }
        else{
            printf("Not on the tree or error\n");
        }
    }
    
    printf("\nWanted: ");
    int value;
    scanf("%d", &value);
    bool found = bt.search(value);
    if(found){
        printf("Found!\n");
    }
    else{
        printf("Not found or error\n");
    }

    if(bt.isEmpty()){
        printf("It's empty\n");
    }
    else{
        printf("It's not empty\n");
    }

    printf("The size is: %d\n", bt.size());
    printf("The height is: %d\n", bt.height());

    bt.printPreOrder();
    bt.printInOrder();
    bt.printPostOrder();
}