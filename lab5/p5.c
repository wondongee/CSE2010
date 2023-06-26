#include <stdio.h>
#include <stdlib.h>

struct TreeStruct {
    int size;
    int numOfNode;
    int* element;
};
typedef struct TreeStruct* Tree;

Tree CreateTree(int size) {
    Tree T;
    T = malloc(sizeof(struct TreeStruct));
    T->element = malloc(sizeof(int)*(size+1));
    T->size = size;
    T->numOfNode = 1;
    return T;
}

void Insert(Tree tree, int value) {
    if(tree->numOfNode > tree->size) {
        perror("Tree is full");
	return;
    }
    tree->element[tree->numOfNode] = value;
    tree->numOfNode++;
}

void printPreorder(Tree tree, int index) {
    printf("%d ", tree->element[index]);
    int index2 = index*2;
    if(index2 <= tree->size) {
        printPreorder(tree, index2);
    }
    if(index2+1 <= tree->size) {
        printPreorder(tree, index2+1);
    }
}

void printInorder(Tree tree, int index) {
    int index2 = index*2;
    if(index2 <= tree->size) {
        printInorder(tree, index2);
    }
    printf("%d ", tree->element[index]);
    if(index2+1 <= tree->size) {
        printInorder(tree, index2+1);
    }

}
void printPostorder(Tree tree, int index) {
    int index2 = index*2;
    if(index2 <= tree->size) {
        printPostorder(tree, index2);
    }
    if(index2+1 <= tree->size) {
        printPostorder(tree, index2+1);
    }
    printf("%d ", tree->element[index]);

}
void DeleteTree(Tree tree) {
    free(tree);
}

void printTree(Tree tree) {
    printf("Preorder: ");
    printPreorder(tree, 1);
    printf("\n");
    printf("Ineorder: ");
    printInorder(tree, 1);
    printf("\n");
    printf("Posteorder: ");
    printPostorder(tree, 1);
    printf("\n");
}

int main(int argc, char* argv[]) {
    FILE *fi;
    Tree tree;
    int treeSize;
    int tmpNum;

    fi = fopen(argv[1], "r");
    fscanf(fi, "%d", &treeSize);
    tree = CreateTree(treeSize);

    while(fscanf(fi, "%d", &tmpNum) == 1) {
        Insert(tree, tmpNum);
    }
    printTree(tree);
    DeleteTree(tree);

}
