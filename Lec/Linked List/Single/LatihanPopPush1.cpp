#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    Node* next;
} *head, *tail, *current;

void push_ultimate(int input){
    current = (Node*)malloc(sizeof(Node));
    current->data = input;
    if (!head){
        head=tail=current;
    }
    if (head->data < input){
        current->next = head;
        head = current;
    } else if(tail->data > input){
        tail->next = current;
        tail = current;
    } else {
        Node *temp = head;
        while (temp->data < input){
            temp = temp->next;
        }
        current->next = temp->next;
        temp->next = current;
    }
}

void pop_ultimate(int input){
    if (head == NULL){
        return;
    } 
    if (head->data == input){ // Pop Head
        Node* temp = head;
        head = head->next;
        temp->next = NULL;
        free(temp);
    } else { // Pop Mid
        Node *temp1 = head, *temp2 = head->next;
        while (temp2->data < input){
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        temp1->next = temp2->next;
        temp2->next = NULL;
        free(temp2);
    }
}

int main(){

}