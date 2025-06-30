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

// Cek apakah stack kosong
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Cek apakah stack penuh
int isFull(Stack *s) {
    return s->top == MAX - 1;
}

// Menambahkan elemen ke stack
void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack overflow!\n");
    } else {
        s->data[++(s->top)] = value;
    }
}

// Menghapus elemen dari stack
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        return -1;
    } else {
        return s->data[(s->top)--];
    }
}

// Melihat elemen di puncak stack
int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    } else {
        return s->data[s->top];
    }
}

// Contoh penggunaan
int main() {
    Stack s;
    init(&s);

    push(&s, 10);
    push(&s, 20);
    printf("Top: %d\n", peek(&s)); // Output: 20
    printf("Popped: %d\n", pop(&s)); // Output: 20
    printf("Popped: %d\n", pop(&s)); // Output: 10
    printf("Popped: %d\n", pop(&s)); // Output: Stack underflow!

    return 0;
}