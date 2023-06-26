#include <stdio.h>
#include <stdlib.h>

typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

struct Node {
    ElementType element;
    Position next;
};

List MakeEmptyList() {
    List l = (List)malloc(sizeof(struct Node));
    l -> element = -999;
    l -> next = NULL;
    return l;
}

int isLast(Position p, List l) {
    return p->next == NULL;

}

Position FindPrevious(ElementType x, List l) {
    Position P;
    P = l;
    while(P->next != NULL) {
        if(P->next->element == x) {
            return P;
        }
        P = P -> next;
    }
    return NULL;
    
}

void Delete(ElementType x, List l) {
    Position P, TmpCell;
    P = FindPrevious(x, l);
    /* Assumption of header us */
    if(!isLast(P, l)) {
        TmpCell = P->next;
        P->next = TmpCell->next;
        free(TmpCell);
    } else {
        TmpCell = P->next;
        P->next = NULL;
        free(TmpCell);
    }
}



Position Find(ElementType x, List l) {
    Position P;
    P = l->next;
    while(P != NULL) {
        if(P->element == x) {
            return P;
        }
        P = P->next;
    }
    return NULL;  
}

void Insert(ElementType x, Position p, List l) {
    Position TmpCell;
    TmpCell = malloc(sizeof(struct Node));
    if(TmpCell == NULL) {
        //FatalError("Out of space!!!");
        return;
    }
    TmpCell->element = x;
    TmpCell->next = p->next;
    p->next = TmpCell;
}

void DeleteList(List l) {
    Position P, Tmp;
    P = l->next; /* Header assumed */
    l->next = NULL;
    while(P!=NULL) {
        Tmp = P->next;
        free(P);
        P = Tmp;
    }
}

void PrintList(List l) {
    PtrToNode tmp = NULL;
    tmp = l -> next;
    if(tmp == NULL) {
        printf("list is empty!\n");
        return;
    }
    while(tmp != NULL) {
        printf("key: %d\t", tmp->element);
        tmp = tmp -> next;
    }
    printf("\n");
};

int main(int argc, char *argv[]) {
    char command;
    int key1, key2;
    FILE *input, *output;
    Position header = NULL, tmp = NULL;

    if(argc <= 1) {
        printf("Please enter an input file.");
        return 0;
    } else {
        input = fopen("simple.txt", "r");
    }

    header = MakeEmptyList();
    while(1) {
        command = fgetc(input);
        if(feof(input)) break;
        switch(command) {
            case 'i':
                fscanf(input, "%d %d", &key1, &key2);
                tmp = Find(key2, header);
                Insert(key1, tmp, header);
                break;
            case 'd':
                fscanf(input, "%d", &key1);
                Delete(key1, header);
                break;
            case 'f':
                fscanf(input, "%d", &key1);
                tmp = FindPrevious(key1, header);
                if(isLast(tmp, header)) {
                    printf("Could not find %d in the list.\n", key1);
                } else if (tmp->element > 0) {
                    printf("Key of the previous node of %d is %d.\n", key1, tmp->element);
                } else {
                    printf("key of the previoud node of %d is header.\n", key1);
                }
                break;
            case 'p':
                PrintList(header);
                break;
            defalut:
                printf("Invalid command line");
        }
    }
    DeleteList(header);
    fclose(input);

    return 0;
}