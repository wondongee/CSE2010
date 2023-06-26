#include <stdio.h>
#include <stdlib.h>

typedef struct Stack *PtrToNode;
typedef PtrToNode HeadStack;
typedef struct Stack{
    int* key;
    int top;
    int max_stack_size;
}Stack;

int IsEmpty(Stack* s) {
    if(s->top < 0) {
        return 1;
    } else {
        return 0;
    }
}
int IsFull(Stack* s) {
    if (s->top >= s->max_stack_size-1) {
        return 1;
    } else {
        return 0;
    }
}
Stack* CreateStack(int max) {
    HeadStack S;
    S = malloc(sizeof(struct Stack));
    if(S==NULL) {
        perror("Out of space!!!");
    }
    S->key = malloc(sizeof(char)*100);
    S->top = -1;
    S->max_stack_size = max;
    return S;
}
void Push(Stack* s, int x) {
    if(IsFull(s) == 1) {
        perror("Full stack");
    } else {
        s->key[++(s->top)] = x;
    }
}

int Pop(Stack* s) {
    if(IsEmpty(s) == 1) {
        perror("Empty stack");
        return 0;
    } else {
        int keyValue = s->key[s->top];
        s->top--;
        return keyValue;
    }
}

int Top(Stack* s) {
    if(IsEmpty(s) == 0) {
        return s->key[s->top];
    }
    perror("Empty stack");
    return 0;
}
void DeleteStack(Stack* s) {
    free(s->key);
}


void Postfix(Stack* s, char input_str) {
    int num1, num2, num3;
    switch(input_str) {
        case '+':
            num1 = Pop(s);
            num2 = Pop(s);
            num3 = num2 + num1;
            Push(s, num3);
            break;
        case '-':
            num1 = Pop(s);
            num2 = Pop(s);
            num3 = num2 - num1;
            Push(s, num3);
            break;
        case '*':
            num1 = Pop(s);
            num2 = Pop(s);
            num3 = num2 * num1;
            Push(s, num3);
            break;
        case '/':
            num1 = Pop(s);
            num2 = Pop(s);
            num3 = num2 / num1;
            Push(s, num3);
            break;
        case '%':
            num1 = Pop(s);
            num2 = Pop(s);
            num3 = num2 % num1;
            Push(s, num3);
            break;
        default:
            Push(s, input_str - '0');
    }
}

int main(int argc, char* argv[]){
    FILE* fi = fopen(argv[1], "r");
    Stack* stack = CreateStack(10);

    char c;
    printf("Top numbers: ");
    while(1) {
        fscanf(fi, "%c", &c);
        if(c == '#') {
            break;
        }
        Postfix(stack, c);
        printf("%d ", Top(stack));
    }
    printf("\n");
    printf("evaluation result: %d\n", Pop(stack));
    fclose(fi);
    DeleteStack(stack);
    return 0;
}
