#include "AVL.h"

AVL* create(){
    AVL *bt = (AVL*) malloc(sizeof(AVL));
    if(bt != NULL){
        *bt = NULL;
    }
    return bt;
}
void destroy(AVL *bt){
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

int heightNode(node *node){
    int left, right;
    if (node->left == NULL){
        left = -1;
    }
    else{
        left = node->left->height;
    }
    if (node->right == NULL){
        right = -1;
    }
    else{
        right = node->right->height;
    }

    if (left > right){
        return (left + 1);
    }
    else{
        return (right + 1);
    }
}

int insertTree(AVL *bt, DATA value){
    int ins;
    if(bt == NULL){ // if tree is not created yet or is already freed returns ERROR
        return -1;
    }
    
    if(*bt == NULL){ // if the node is empty
        node *newNode = (node*) malloc(sizeof(node)); // creates and allocate a new node
        if(newNode == NULL){ // if there is no memory available returns ERROR
            return -1;
        }

        newNode->info = value; // sets the value of the new node
        newNode->height = 0; // sets teh height of the new node
        newNode->left = NULL; // sets the left child of the new node to NULL
        newNode->right = NULL; // sets the right child of the new node to NULL
        *bt = newNode;
        return 1;
    }
    
    node *currentNode = *bt;

    if (currentNode->info == value){
        return 0;
    }
    else if (currentNode->info > value){ // go to the left if new value is lesser than the node
        ins = insertTree(&(currentNode->left), value);
        if(ins == 1){
            if(balanceFactor(currentNode) >= 2){
                if(value < (*bt)->left->info){
                    rotationLL(bt);
                }else{
                    rotationLR(bt);
                }
            }
        }
    }
    else{ // go to the right if new value is greater than the node
        ins = insertTree(&(currentNode->right), value);
        if(ins == 1){
            if(balanceFactor(currentNode) >= 2){
                if(value > (*bt)->right->info){
                    rotationRR(bt);
                }else{
                    rotationRL(bt);
                }
            }
        }
    }

    currentNode->height = heightNode(currentNode);
    return ins;
}

int removeTree(AVL *bt, DATA value){
    int ins;

    if(bt == NULL){ // if tree is not created yet or is already freed returns ERROR
        return -1;
    }

    if(*bt == NULL){ // if the tree is empty, return that value does not exist
        return 0;
    }
    
    if (value < (*bt)->info){ // go to the left if new value is lesser than the node
        ins = removeTree(&(*bt)->left, value);
        if (ins == 1 && balanceFactor(*bt) >= 2){
            int left = -1, right = -1;
            if ((*bt)->right->left != NULL){
                left = (*bt)->right->left->height;
            }
            if ((*bt)->right->right != NULL){
                right = (*bt)->right->right->height;
            }
            if (left <= right){
                rotationRR(bt);
            }
            else{
                rotationRL(bt);
            }
        }
    }
    else if ((*bt)->info < value){ // go to the right if new value is greater than the node
        ins = removeTree(&(*bt)->right, value);
        if (ins == 1 && balanceFactor(*bt) >= 2){
            int left = -1, right = -1;
            if ((*bt)->left->left != NULL){
                left = (*bt)->left->left->height;
            }
            if ((*bt)->left->right != NULL){
                right = (*bt)->left->right->height;
            }
            if (right <= left){
                rotationLL(bt);
            }
            else{
                rotationLR(bt);
            }
        }
    }
    else {
        removeNode(bt);
        return 1;
    }
    (*bt)->height = heightNode(*bt);
    return ins; // value isn't on the tree
}
void removeNode(AVL *bt){
    if(((*bt)->left == NULL) || ((*bt)->right == NULL)){
        node *oldNode = (*bt);
        if((*bt)->left != NULL){
            (*bt) = (*bt)->left;
        }
        else {
            (*bt) = (*bt)->right;
        }
        free(oldNode);
    }
    else { 
        node *temp = (*bt)->right;
        node *aux = temp->left;

        while(aux != NULL){
            temp = aux;
            aux = aux->left;
        }

        (*bt)->info = temp->info;
        removeTree(&(*bt)->right, (*bt)->info);

        if(balanceFactor((*bt)) >= 2){
            int left = -1, right = -1;
            if ((*bt)->left->left != NULL){
                left = (*bt)->left->left->height;
            }
            if ((*bt)->left->right != NULL){
                right = (*bt)->left->right->height;
            }
            if(right <= left){
                rotationLL(bt);
            }
            else {
                rotationLR(bt);
            }
        }
    }
    if ((*bt) != NULL){
        (*bt)->height = heightNode((*bt));
    }
    return;
}

int balanceFactor(node *node){
    int left, right;
    if (node->left == NULL){
        left = -1;
    }
    else{
        left = node->left->height;
    }
    if (node->right == NULL){
        right = -1;
    }
    else{
        right = node->right->height;
    }
    return labs(left - right);
}
void rotationLL(AVL *bt){
    node *aux;
    aux = (*bt)->left;
    (*bt)->left = aux->right;
    aux->right = *bt;

    (*bt)->height = heightNode(*bt);
    if(aux->left != NULL && (aux->left->height > (*bt)->height)){
        aux->height = aux->left->height + 1;
    }
    else{
        aux->height = (*bt)->height + 1;
    }

    *bt = aux;
}
void rotationRR(AVL *bt){
    node *aux;
    aux = (*bt)->right;
    (*bt)->right = aux->left;
    aux->left= (*bt);

    (*bt)->height = heightNode((*bt));
    if(aux->right != NULL && (aux->right->height > (*bt)->height)){
        aux->height = aux->right->height + 1;
    }
    else{
        aux->height = (*bt)->height + 1;
    }

    (*bt) = aux;
}
void rotationLR(AVL *bt){
    rotationRR(&(*bt)->left);
    rotationLL(bt);
}
void rotationRL(AVL *bt){
    rotationLL(&(*bt)->right);
    rotationRR(bt);
}

int search(AVL *bt, DATA value){
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
int isEmpty(AVL *bt){
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
int size(AVL *bt){
    if (bt == NULL){
        return -1;
    }
    if (*bt == NULL){
        return 0;
    }
    return sizeRec(*bt);
}
int height(AVL *bt){
    if (bt == NULL){
        return -1;
    }
    if (*bt == NULL){
        return 0;
    }
    return ((*bt)->height + 1);
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