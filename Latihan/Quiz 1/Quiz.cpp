#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#define max_table 10

// Vulnerability Queue
struct Queue{
    int ID;
    int impact;
    int likelihood;
    int priority;
    char status[10];
    Queue* Next;
} *head, *tail, *current;

// Hash Queue
struct Node {
    int ID;
    int impact;
    int likelihood;
    int priority;
    Node* Next;
} *kepala[max_table], *ekor[max_table], *sekarang;

// Hash ID
int hash(int ID){
    return ID % max_table;
}

// Push Vulnerability Queue
void push_Ultimate(int ID, int impact, int likelihood){
    current = (Queue*)malloc(sizeof(Queue));
    current->Next = NULL;

    
    current->ID = ID;
    current->impact = impact;
    current->likelihood = likelihood;
    
    // priority
    if(impact && likelihood){
        current->priority = 4;
        strcpy(current->status, "Critical");
    } else if(impact && !likelihood){
        current->priority = 3;
        strcpy(current->status, "High");
    } else if(!impact && likelihood){
        current->priority = 2;
        strcpy(current->status, "Medium");
    } else {
        current->priority = 1;
        strcpy(current->status, "Low");
    }

    // Input ke Queue
    if (!head){ // Kalau ga ada head
        head=tail=current;
    } else if (head->priority < current->priority){ // Kalau head priority lebih rendah
        current->Next = head;
        head = current;
    } else if (tail->priority > current->priority){ // Kalau tail priority lebih tinggi
        tail->Next = current;
        tail = current;
    } else {
        Queue *temp = head;
        while (temp->Next && temp->Next->priority >= current->priority){
            temp = temp->Next;
        }
        current->Next = temp->Next;
        temp->Next = current;
    }
}


// Push Hash
void push_hash(){
    Node *sekarang = (Node*)malloc(sizeof(Node));
    sekarang->Next = NULL;
    
    int position = hash(head->ID); // Bikin index dari ID

    sekarang->ID = head->ID;
    sekarang->impact = head->impact;
    sekarang->likelihood = head->likelihood;
    sekarang->priority = head->priority;
    
    if (!kepala[position]){ // Kalau ga ada head di index itu
        kepala[position]=ekor[position]=sekarang;
    } // Ku urutin sekalian pas di setiap indexnya dari berdasarkan prioritas 
    else if (kepala[position]->priority < sekarang->priority){ // Kalau kepala priority lebih rendah
        sekarang->Next = kepala[position];
        kepala[position] = sekarang;
    } else if (ekor[position]->priority > sekarang->priority){ // Kalau ekor priority lebih tinggi
        ekor[position]->Next = sekarang;
        ekor[position] = sekarang;
    } else {
        Node *temp = kepala[position];
        while (temp->Next && temp->Next->ID < head->ID){
            temp = temp->Next;
        }
        sekarang->Next = temp->Next;
        temp->Next = sekarang;
    }
}

void Call(){
    printf("Vulnerability Queue:\n");
    while(true){
        if(!head){
            printf("No queue left\n");
            break;
        }
        
        printf("ID: %d - %s\n", head->ID, head->status);

        // Setiap sebelum bener bener di dequeue, push ke Hash
        push_hash();

        // dequeue process
        struct Queue* temp = head;
        head = head->Next;
        if (!head) {
            tail = NULL;
        }
        free(temp);
    }
}

void printHash(){
    printf("Stored Processed Vulneralabilities:\n");
    for (int i = 0; i < max_table; i++){
        if (kepala[i]) {
            printf("Index %d: ", i);
            sekarang = kepala[i];
            printf("ID:");
            while (sekarang){
                printf(" %d -> ", sekarang->ID);
                sekarang = sekarang->Next;
            }
            printf("NULL\n");
        } 
    }
}

int main(){
    // printf("ID (int), Impact (bool), Likelihood (bool)\n");
    push_Ultimate(3001, 0, 0);
    push_Ultimate(3002, 1, 1);
    push_Ultimate(3003, 1, 0);
    push_Ultimate(3004, 0, 1);
    push_Ultimate(3005, 1, 1);
    push_Ultimate(3113, 1, 1);

    Call();
    puts("\nProcessing vulnerabilities...");
    system("pause");
    system("cls");
    printHash();
    return 0;
}