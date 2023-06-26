#include <stdio.h>
#include <stdlib.h>

typedef struct _Queue {
    int size;
    int *key;
    int front;
    int rear;
} Queue;

Queue* CreateQueue(int X) {
    Queue* Q = malloc(sizeof(Queue));
    Q->key = malloc(sizeof(int)*X);
    Q->size = X;
    Q->front = 0;
    Q->rear = -1;
    return Q;
}

void Enqueue(Queue *Q, int item) {
    Q->key[++Q->rear] = item;
}

int IsEmpty(Queue *Q) {
    return Q->front > Q->rear;
}

int Dequeue(Queue *Q) {
    return Q->key[Q->front++];
}

typedef struct _Graph {
    int size;
    int *vertex;
    int **edge;
} Graph;

Graph* CreateGraph(int X) {
    Graph* G = malloc(sizeof(Graph));
    G->size = X;
    G->vertex = (int*)malloc(sizeof(int)*X);
    G->edge = (int**)malloc(sizeof(int*)*X);
    for(int i=0; i<G->size; i++) {
        G->edge[i] = calloc(X, sizeof(int));
    }
    return G;
}

void InsertEdge(Graph *G, int u, int v) {
    int i, j;
    for(i=0; i<G->size; i++) {
        if(u  == G->vertex[i]) {
            break;
        }
    }
    for(j=0; j<G->size; j++) {
        if(v == G->vertex[j]) {
            break;
        }
    }
    G->edge[i][j] = 1;
}

void Topsort (Graph *G) {
    Queue* Q;
    int *Indegree;
    Indegree = calloc(G->size, sizeof(int));
    Q = CreateQueue(G->size);

    for(int j=0; j<G->size; j++) {
        int sum = 0;
        for(int i=0; i<G->size; i++) {
            sum = sum + G->edge[i][j];
        }
        Indegree[j] = sum;
        if(Indegree[j] == 0) {
            Enqueue(Q, G->vertex[j]);
        }
    }

    while(!IsEmpty(Q)) {
        int num = Dequeue(Q);
        int i;
        printf("%d ", num);
        for(i=0; i<G->size; i++) {
            if(num == G->vertex[i]) {
                break;
            }
        }
        for(int j=0; j<G->size; j++) {
            if(Indegree[j] != 0) {
                Indegree[j] = Indegree[j] - G->edge[i][j];
                G->edge[i][j] = 0;
                if (Indegree[j] == 0) {
                    Enqueue(Q, G->vertex[j]);
                }
            }                                
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *fi = fopen(argv[1], "r");
    int X, u, v;

    fscanf(fi, "%d", &X);
    
    Graph *G = CreateGraph(X);

    for(int i=0; i<X; i++) {
        fscanf(fi, "%d", &G->vertex[i]);
    }
    while(fscanf(fi, "%d %d", &u, &v) != EOF) {
        InsertEdge(G, u, v);
    }
    Topsort(G);
    return 0;
}
