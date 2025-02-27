#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    Node* Next;
} *head, *tail, *current;

void push_ultimate(int input){
    current = (Node*)malloc(sizeof(Node));
    current->data = input; // Lupa isi data
    if(!head){
        head=tail=current;
    }
    if (head->data < input){ // Head Push
        current->Next=head;
        head = current;
    } else if(tail->data > input){ // Tail Push
        tail->Next = current;
        tail = current;
    } else { // Mid Push
        // Belum apal buat push mid
        Node* temp = head;
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