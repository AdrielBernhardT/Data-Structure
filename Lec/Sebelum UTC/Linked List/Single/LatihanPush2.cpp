#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    Node* Next;
} *head, *tail, *current;

void push_ultimate(int input){
    current = (Node*)malloc(sizeof(Node));
    current->data = input;
    if (!head){
        head=tail=current;
    }
    if (head->data < input){
        current->Next = head;
        head=current;
    } else if (tail->data > input){
        tail->Next = current;
        tail = current;
    } else {
        Node *temp = head;
        while (temp->Next->data < input){
            temp = temp->Next;
        }
        current->Next = temp->Next;
        temp->Next = current;
    }
}

int main(){

    return 0;
}