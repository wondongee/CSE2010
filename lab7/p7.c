#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;
struct AVLNode {
    ElementType Element;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

int Height(Position P) {
    if(P == NULL) {
        return -1;
    } else {
        return P->Height;
    }
}
Position SingleRotateWithLeft(Position Node) {
    Position TmpNode;
    TmpNode = Node->Left;

    Node->Left = TmpNode->Right;
    TmpNode->Right = Node;

    Node->Height = MAX( Height(Node->Left), Height(Node->Right) ) + 1;
    TmpNode->Height = MAX( Height(TmpNode->Left), Height(Node)) + 1;

    return TmpNode;
}

Position SingleRotateWithRight(Position Node) {
    Position TmpNode;
    TmpNode = Node->Right;

    Node->Right = TmpNode->Left;
    TmpNode->Left = Node;

    Node->Height = MAX( Height(Node->Left), Height(Node->Right) ) + 1;
    TmpNode->Height = MAX( Height(Node), Height(TmpNode->Right) ) + 1;

    return TmpNode;
}

Position DoubleRotateWithLeft(Position Node) {
    Node->Left = SingleRotateWithRight(Node->Left);
    return SingleRotateWithLeft(Node);
}

Position DoubleRotateWithRight(Position Node) {
    Node->Right = SingleRotateWithLeft(Node->Right);
    return SingleRotateWithRight(Node);
}

AVLTree Insert(ElementType X, AVLTree T) {
    if(T == NULL) {
        T = malloc(sizeof(struct AVLNode));
        if(T == NULL) {
            perror("Out of space!!");
        } else {
            T->Element = X;
            T->Left = NULL;
            T->Right = NULL;
            T->Height = 0;
        }
    } else if (X < T->Element) {
        T->Left = Insert(X, T->Left);
        if( Height(T->Left) - Height(T->Right) == 2) {
            if(X < T->Left->Element) {
                T = SingleRotateWithLeft(T);
            } else if (X > T->Left->Element) {
                T = DoubleRotateWithLeft(T);
            }
        }
    } else if (X > T->Element) {
        T->Right = Insert(X, T->Right);
        if( Height(T->Right) - Height(T->Left) == 2) {
            if(X > T->Right->Element) {
                T = SingleRotateWithRight(T);
            } else if (X < T->Right->Element) {
                T = DoubleRotateWithRight(T);
            }
        }
    } else if(X == T->Element) {
        perror("Insertion Error: [key] already in the tree!");
        return T;
    }
    T->Height = MAX( Height(T->Left), Height(T->Right) ) + 1;
    return T;
}

void PrintInorder(AVLTree T) {
    if(T == NULL) {
        return;
    }
    PrintInorder(T->Left);
    printf("%d(%d) ", T->Element, T->Height);
    PrintInorder(T->Right);
}

void DeleteTree(AVLTree T) {
    if(T->Left != NULL) {
        DeleteTree(T->Left);
    }
    if(T->Right != NULL) {
        DeleteTree(T->Right);
    }
    free(T);
}

int main(int argc, char* argv[]) {
    FILE *fi = fopen(argv[1], "r");
    AVLTree myTree = NULL;
    int key;

    while(fscanf(fi, "%d", &key) != EOF) {
        myTree = Insert(key, myTree);
        PrintInorder(myTree);
        printf("\n");
    }
    DeleteTree(myTree);
}
