#include <stdio.h>
#include <stdlib.h>

const int INF = (int)2e9;

typedef struct Node {
    int vertex;
    int dist;
    int prev;
} Node;

typedef struct Graph {
    int size;
    Node* nodes;
    int** matrix;
} Graph;

typedef struct Heap {
    int capacity;
    int size;
    Node* elements;
} Heap;

int IsEmpty(Heap* H) {
    return H->size == 0;
}

Heap* createMinHeap(int X) {
    Heap* heap;
    heap = malloc(sizeof(struct Heap));
    heap->elements = (Node*) malloc(sizeof(struct Node) * (X+1));
    heap->size = 0;
    heap->elements[0].dist = -9999;
    heap->capacity = X;
    return heap;
}

void insert(Heap* H, Node N) {
    int i;
    for(i=++H->size; H->elements[i/2].dist > N.dist; i /= 2) {
        H->elements[i] = H->elements[i/2];
    }
    H->elements[i] = N;
}

Node deleteMin(Heap* H) {
    int i, child;
    Node MinElement, LastElement;
    
    MinElement = H->elements[1];
    LastElement = H->elements[H->size--];
    
    for(i=1; i*2 <= H->size; i=child) {
        child = i*2;
        if(child != H->size && H->elements[child+1].dist < H->elements[child].dist) {
            child++;
        }
        if(LastElement.dist > H->elements[child].dist) {
            H->elements[i] = H->elements[child];
        } else {
            break;
        }
    }
    H->elements[i] = LastElement;
    return MinElement;
}

void decreaseKey(Heap* H, Node N) {

}


Graph* createGraph(int X) {
    Graph* G = malloc(sizeof(Graph));

    G->size = X;

    G->nodes = malloc(sizeof(struct Node) * (X+1));
    for(int n=0; n<G->size+1; n++) {
        G->nodes[n].vertex = n;
        G->nodes[n].dist = INF;
        G->nodes[n].prev = 0;
    }

    G->matrix = (int**)malloc(sizeof(int*)*(X+1));
    for(int i=0; i<G->size+1; i++) {
        G->matrix[i] = calloc(X+1, sizeof(int));
    }
    return G;
}

Graph* findShortestPath(Graph* G, int s) {
    G->nodes[s].dist = 0;
    G->nodes[s].prev = 1;
    for(int i=1; i<G->size+1; i++) {
        if(G->matrix[s][i] != 0) {
            G->nodes[i].dist = G->matrix[s][i];
            G->nodes[i].prev = s;
        }
    }

    Heap* heap;
    heap = createMinHeap(G->size);
    for(int i=1; i<G->size+1; i++) {
        insert(heap, G->nodes[i]);
    }

    while(!IsEmpty(heap)) {
        Node u;
        u = deleteMin(heap);
        for(int i=1; i<G->size+1; i++) {
            if(G->matrix[u.vertex][i] != 0) {
                if(u.dist + G->matrix[u.vertex][i] < G->nodes[i].dist ) {
                    G->nodes[i].dist = u.dist + G->matrix[u.vertex][i];
                    G->nodes[i].prev = u.vertex;
                }
            }
        }
    }
    return G;
}

void printShortestPath(Graph* G) {
    for(int i=2; i<G->size+1; i++) {
        if(G->nodes[i].dist != INF) {
            int j = i;
            while(G->nodes[j].prev != 1) {
                printf("%d <- ", G->nodes[j].vertex);
                j = G->nodes[j].prev;
            }
            printf("%d <- 1 cost : %d\n", G->nodes[j].vertex, G->nodes[i].dist);
        } else {
            printf("%d can not be reached.\n", G->nodes[i].vertex);
        }
    }
}


int main(int argc, char* argv[]) {
    FILE *fi = fopen("argv[1]", "r");
    int size;

    fscanf(fi, "%d", &size);
    Graph* G = createGraph(size);

    int node_s, node_d, weight;
    while(fscanf(fi, "%d %d %d", &node_s, &node_d, &weight) != EOF) {
        G->matrix[node_s][node_d] = weight;
    }

    G = findShortestPath(G, 1);
    printShortestPath(G);

    return 0;
}
