#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_length 100

typedef struct HashTable {
    int size;
    int *list;
} HashTable;

/* division function (h(k) = k mod m, where m is the size of hash table) */
int hash(int key, int size) {
    return key % size;
}

/* If the key exists in hash table, return the index number
 * If not exist, return 0 */
int find(int key, HashTable *H) {
    int indexNum = hash(key, H->size);
    int firstIndex = indexNum;
    while(1) {
        if(indexNum == H->size) {
            indexNum = 0;
        }
        if(key == H->list[indexNum]) {
            return 1;
        }
        indexNum = indexNum + 1;
        if(firstIndex == indexNum) {
            return 0;
        }
    }
    return 0;
}

/*
 * open addressing with linear probing (F(i) = i)
 * When insert the key, print a message
 * "%d is inserted at address %d", key, the index of hash table
 * If a collision occurs, print a message
 * "%d collision has been occured with %d", key, the key in place
 */
void insert(int key, HashTable *H) {
    int indexNum = hash(key, H->size);
    int firstIndex = indexNum;
    while(1) {
        if(indexNum == H->size) {
            indexNum = 0;
        }
        if(key == H->list[indexNum]) {
            break;
        }
        if(H->list[indexNum] == 0) {
            H->list[indexNum] = key;
            printf("%d is inserted at address %d\n", key, indexNum);
            break;
        } else {
            printf("%d collision has been occured with %d\n", key, H->list[indexNum]);
        }
        indexNum = indexNum + 1;
        if(firstIndex == indexNum) {
            printf("Table is full\n");
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    FILE *f;
    f = fopen(argv[1], "r");
    int size, indexnumber;
    int i, tmp;
    char index[max_length];
    char *ptr1, *ptr2, *ptr3;
    char *ptrtmp[3];

    /* 
     * first : ptr1
     * HashTable size 저장
     */
    fgets(index, 100, f);
    /* index를 " " 기준으로 잘린 문자열 ptr1, 자르고 남은 문자열 : ptrtmp 저장 */
    ptr1 = strtok_r(index, " ", &ptrtmp[0]);
    size = atoi(ptr1); /* ptr1을 정수로 변환하여 size에 저장 */

    HashTable *table;
    table = malloc(sizeof(HashTable));
    table->size = size;
    table->list = malloc(sizeof(int)*table->size);
    for(i=0; i<table->size; i++) {
        table->list[i] = 0;
    }

    /*
     * second : ptr2
     */
    fgets(index, 100, f);
    ptr2 = strtok_r(index, " ", &ptrtmp[1]);
    while(ptr2 != NULL) {
        indexnumber = atoi(ptr2);
        insert(indexnumber, table);
        ptr2 = strtok_r(NULL, " ", &ptrtmp[1]);
    }

    /*
     * second : ptr2
     */
    fgets(index, 100, f);
    ptr3 = strtok_r(index, " ", &ptrtmp[2]);
    while(ptr3 != NULL) {
        indexnumber = atoi(ptr3);
        tmp = find(indexnumber, table);
        if(tmp == 0) {
            printf("%d is not in the table\n", indexnumber);
        } else {
            printf("%d is in the table\n", indexnumber);
        }
        ptr3 = strtok_r(NULL, " ", &ptrtmp[2]);
    }

    return 0;

}
