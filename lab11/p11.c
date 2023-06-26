#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct _DisjointSet {
    int size;
    int *ptr_arr; // parent
} DisjointSets;

typedef struct _PrintDisjointSet {
    int size;
    int *ptr_arr; // wall
} PrintDisjointSets;

/*
    Initialize all cells to sets and maze.
*/
void init(DisjointSets *sets, PrintDisjointSets *maze, int n) {
    sets->size = n*n;
    sets->ptr_arr = (int*) malloc(sizeof(int) * (sets->size + 1));
    maze->size = 2*n*n + 2*n;
    maze->ptr_arr = (int*) malloc(sizeof(int) * maze->size);
    for (int i=1; i<=sets->size; i++) {
        sets->ptr_arr[i] = 0;
    }
    for (int i=0; i<maze->size; i++) {
        maze->ptr_arr[i] = 1;
    }
}

/*
    Find the set including the number
    and return the representative member of the set.
*/
int find(DisjointSets *sets, int x) {
    while(sets->ptr_arr[x] > 0) {
        x = sets->ptr_arr[x];
    }
    return x;
}
void union_(DisjointSets *sets, int i, int j) {
    int r1 = find(sets, i);
    int r2 = find(sets, j);
    if(sets->ptr_arr[r2] < sets->ptr_arr[r1]) {
        sets->ptr_arr[r1] = r2;
    } else {
        if(sets->ptr_arr[r1] == sets->ptr_arr[r2])
            sets->ptr_arr[r1]--;
        sets->ptr_arr[r2] = r1;
    }
}

/*
    Generate a maze that includes a path from Start position to End position 
    without any cycles.
*/
void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n) {
    int size = maze->size;
    int wall, cell1, cell2;
    int loop_condition;

    while(find(sets, 1) != find(sets, sets->size)) {
        /* select the random wall */
        do
        {
            loop_condition = 1;
            srand((unsigned int)time(NULL));
            wall = rand() % size;
            if(wall < n)
                continue;
            else if (wall % (2*n+1) == n)
                continue;
            else if (wall % (2*n+1) == 2*n)
                continue;
            else if (wall >= (2*n+1)*n)
                continue;
            else
                loop_condition = 0;
        } while(loop_condition);
        // vertical wall
        if (wall % (2*n+1) > n) {
            cell1 = wall / (2*n+1) * n + wall % (2*n+1) - n;
            cell2 = cell1 + 1;
        } else {    // horizontal wall
            cell1 = (wall / (2*n+1) -1 ) * n + wall % (2*n+1) + 1;
            cell2 = cell1 + n;
        }

        if(find(sets, cell1) != find(sets, cell2)) {
            union_(sets, cell1, cell2);
            maze->ptr_arr[wall] = 0;
        }
    }

}

/*
    Print the resulting maze.
*/
void printMaze(PrintDisjointSets *maze, int n) {
    for(int i=0; i<maze->size; i++) {
        if(i == n) {
            printf("\n   ");
            continue;
        }
        if(i == maze->size - (n+1)) {
            printf("\n");
            continue;
        }

        if (i % (2*n+1) < n) {
            if(maze->ptr_arr[i] == 1) {
                printf(" - ");
            } else {
                printf("   ");
            }
        } else {
            if (i % (2*n+1) == n) {
                printf("\n");
            }
            if(maze->ptr_arr[i] == 1) {
                printf("|  ");
            } else {
                printf("   ");
            }
            if (i % (2*n+1) == 2*n) {
                printf("\n");
            }
        }
    }
    printf("\n");
}

/*
    Free memory of the maze.
*/
void freeMaze(DisjointSets *sets, PrintDisjointSets *maze) {
    free(sets->ptr_arr);
    free(maze->ptr_arr);
    free(sets);
    free(maze);
}

int main(int argc,  char* argv[]) {
    int num;
    FILE *fi = fopen(argv[1], "r");
    fscanf(fi, "%d", &num);
    fclose(fi);

    DisjointSets *sets;
    PrintDisjointSets *maze;

    sets = (DisjointSets*) malloc(sizeof(DisjointSets));
    maze = (PrintDisjointSets*) malloc(sizeof(PrintDisjointSets));

    init(sets, maze, num);

    createMaze(sets, maze, num);
    printMaze(maze, num);
    freeMaze(sets, maze);
    return 0;

}
