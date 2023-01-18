#include "binaryTree.h"

int main(){
    binaryTree *bt = create();
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
            printf("Insertion Sucess");
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
            printf("Remotion Sucess");
            break;
        }
    }
    destroy(bt);
}