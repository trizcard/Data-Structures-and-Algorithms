#include "AVL.h"

int main(){
    AVL *bt = create();
    for (int i = 0; i < 8; i++){
        int value;
        printf("\nInserted value: ");
        scanf("%d", &value);
        int insertionCheck;
        insertionCheck = insertTree(bt, value);
        switch (insertionCheck) {
        case -1:
            printf("Insertion Error\n");
            break;
        case 0:
            printf("Already on the tree\n");
            break;
        default:
            printf("Insertion Sucess\n");
            break;
        }
    }
    
    for (int i = 0; i < 8; i++){
        int value;
        printf("\nRemoved value: ");
        scanf("%d", &value);
        int remotionCheck;
        remotionCheck = removeTree(bt, value);
        switch (remotionCheck) {
        case -1:
            printf("Remotion Error\n");
            break;
        case 0:
            printf("Not on the tree\n");
            break;
        default:
            printf("Remotion Sucess\n");
            break;
        }
    }

    // find a number on the tree
    printf("\nWanted value: ");
    int value, found;
    scanf("%d", &value);
    found = search(bt, value);
    switch (found){
        case 0:
            printf("Not found\n");
            break;
        case 1:
            printf("Found!\n");
            break;
        default:
            printf("Error!\n");
            break;
    }

    // size of the tree
    int sizeTree;
    sizeTree = size(bt);
    printf ("\nThe size of the tree is %d\n", sizeTree);

    // height of the tree
    int heightTree;
    heightTree = height(bt);
    printf ("\nThe height of the tree is %d\n", heightTree);

    printPreOrder(*bt);
    printInOrder(*bt);
    printPostOrder(*bt);
    destroy(bt);
}