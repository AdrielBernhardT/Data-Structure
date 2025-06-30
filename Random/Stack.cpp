#include <stdio.h>
#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

// Inisialisasi stack
void init(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack overflow!\n");
    } else {
        s->data[++(s->top)] = value;
    }
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        return -1;
    } else {
        return s->data[(s->top)--];
    }
}

int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    } else {
        return s->data[s->top];
    }
}

int main() {
    Stack s;
    init(&s);

    push(&s, 10);
    push(&s, 20);
    printf("Top: %d\n", peek(&s)); // Output: 20
    printf("Popped: %d\n", pop(&s)); // Output: 20

    printf("Top: %d\n", peek(&s)); // Output: 10
    printf("Popped: %d\n", pop(&s)); // Output: 10

    printf("Popped: %d\n", pop(&s)); // Output: Stack underflow!

    return 0;
}