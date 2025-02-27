#include <stdio.h>
#include <stdlib.h>

struct Node{
    int isinya;
    Node* Next;
} *head, *tail, *current;

void push_ultimate(int input){
    current = (Node*)malloc(sizeof(Node));
    current->isinya = input;
    if (!head){
        head = tail = current;
    }
    if (head->isinya < input){
        current->Next = head;
        head = current;
    } else if (tail->isinya > input){
        tail->Next = current;
        tail = current;
    } else {
        Node *temp = head;
        while (temp->Next->isinya < input){
            temp = temp->Next;
        }
        current->Next = temp->Next;
        temp->Next = current;
    }   
}

void pop_ultimate(int input){
    if (head == NULL){
        return;
    }
    if(head->isinya == input){
        Node *temp = head;
        head = head->Next;
        temp->Next = NULL;
        free(temp);
    } else {
        Node *temp1 = head, *temp2 = head->Next;
        while (temp2 -> isinya < input){
            temp1 = temp1->Next;
            temp2 = temp2->Next;
        }
        temp1->Next = temp2->Next;
        temp2->Next = NULL;
        free(temp2);
    }
}