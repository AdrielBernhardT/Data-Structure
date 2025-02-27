#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    int data;
    Node* Next;
} *head, *tail, *current;

void push(int input){
    current = (Node*)malloc(sizeof(Node));
    current->data = input;
    if (!head){
        head = tail = current;
    }
    if (head->data < input){
        current->Next = head;
        head = current;
    } else if(tail->data > input){
        tail->Next = current;
        tail = current;
    } else {
        Node* temp = head;
        while (temp->Next->data < input){
            temp = temp->Next;
        }
        // masih kebalik line di 28 dan 29
        current->Next = temp->Next;
        temp->Next = current;
    }
} 

void pop(int input){
    if(head == NULL){
        return;
    }
    if (head->data == input){
        Node *temp = head;
        head = head->Next;
        temp->Next = NULL;
        free(temp); 
    } else {
        Node *temp1 = head;
        while (temp1->Next && temp1->Next->data != input){
            temp1 = temp1->Next;
        }
        Node* temp2 = temp1->Next;
        temp1->Next = temp2->Next;
    }
}

int main(){
    
    return 0;
}