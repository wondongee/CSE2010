#include <stdio.h>
#include <stdlib.h>

typedef struct HeapStruct* Heap;
struct HeapStruct {
    int capacity;
    int size;
    int *element;
};

/* 
    create a heap with the size of 'heapSize'
*/
Heap CreateHeap(int heapSize) {
    Heap heap;
    heap = (Heap) malloc(sizeof(struct HeapStruct));
    heap->element = (int*) malloc(sizeof(int)*(heapSize+1));
    heap->size = 0; // size + 1?
    heap->element[0] = 9999999;
    heap->capacity = heapSize;
    return heap;
}

/* 
    find the key in the heap. Return 1 if the value exists.
    Otherwise, return 0 
*/
int Find(Heap heap, int value) {
    for(int i=1; i<=heap->size; i++) {
        if (heap->element[i] == value) {
            return 1;
        }
    }
    return 0;
}


/* 
    insert a new key to the max heap. You should find the right
    position for the new key to maintain the max heap.
    Print what key you inserted.
*/
void Insert(Heap heap, int value) {
    int i;
    if(heap->size >= heap->capacity) {
        printf("Insertion Error : Max Heap is full\n");
        return;
    }
    if(Find(heap, value) == 1) {
        printf("%d is already in the heap.\n", value);
        return;
    }
    for(i=++heap->size; heap->element[i/2]<value; i/=2) {
        heap->element[i] = heap->element[i/2];
    }
    heap->element[i] = value;
    printf("Insert %d \n", value);

}


/*
    delete the max in root node and reconstruct the heap
    to maintain max heap. Print what node you have deleted.
*/
void DeleteMax(Heap heap) {
    int i, child;
    int MaxElement, LastElement;
    if(heap->size == 0) {
        printf("Deletion error : Max Heap is empty!\n");
        return;
    }
    MaxElement = heap->element[1];
    LastElement = heap->element[heap->size--];
    for(i=1; i*2<=heap->size; i=child) {
        child = i*2;
        if(child != heap->size && heap->element[child+1] > heap->element[child]) {
            child++;
        }
        if(LastElement < heap->element[child]) {
            heap->element[i] = heap->element[child];
        } else {
            break;
        }   
    }
    heap->element[i] = LastElement;
    printf("Max elelement(%d) deleted\n", MaxElement);
}
/*
    print the entire heap in level order traversal
*/
void PrintHeap(Heap heap) {
    if(heap->size == 0) {
        printf("Max Heap is empty!\n");
        return;
    }
    for(int i=1; i<=heap->size; i++) {
        printf("%d ", heap->element[i]);
    }
    printf("\n");
}
//void FreeHeap(Heap heep);

int main(int argc, char* argv[]) {
    FILE *fi = fopen(argv[1], "r");
    char cv;
    Heap maxHeap;
    int value, maxValue;
    while(!feof(fi)) {
        fscanf(fi, "%c", &cv);
        switch(cv) {
        case 'n':
            fscanf(fi, "%d", &value);
            maxHeap = CreateHeap(value);
            break;
        case 'i':
            fscanf(fi, "%d", &value);
            Insert(maxHeap, value);
            break;
        case 'd':
            DeleteMax(maxHeap);
            break;
        case 'f':
            fscanf(fi, "%d", &value);
            if(Find(maxHeap, value))
                printf("%d is in the heap.\n", value);
            else
                printf("%d is not in the heap.\n", value);   
            break;
        case 'p':
            PrintHeap(maxHeap);
        }   
    }
}
