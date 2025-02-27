#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patient {
    char Name[105];
    int umur;
    char status[5];
    int convert;
    patient* Next;
    patient* Prev;
} *head, *tail, *current;

void inputQueue(){
    current = (struct patient*)malloc(sizeof(struct patient));
    printf("Patient Data Input:\nName:\n>> ");
    scanf("%[^\n]", current->Name); getchar();
    printf("Age:\n>> ");
    scanf("%d", &current->umur); getchar();
    printf("Status:\n>> ");
    scanf("%s", current->status); getchar();

    printf("%s\n", current->Name);
    printf("%d\n", current->umur);
    printf("%s\n", current->status);
    
    if(strcmp(current->status, "Low") == 0){
        current->convert = 1; 
    } else if (strcmp(current->status, "Mid") == 0){
        current->convert = 2;
    } else if (strcmp(current->status, "High") == 0){
        current->convert = 3;
    }

    current->Next = NULL;
    current->Prev = NULL;


    if (!head){
        head=tail=current;
    } 
    if (head->convert < current->convert){
        head->Prev = current;
        current->Next = head;
        head = current;
    } else if (tail->convert > current->convert){
        tail->Next = current;
        current->Prev = tail;
        tail = current;
    }else {
        struct patient *temp = head;
        while (temp->Next->convert >= current->convert)
        {
            temp = temp->Next;
        }
        current->Next = temp->Next;
        current->Prev = temp;
        temp->Next->Prev = current;
        temp->Next = current;
    }
}

int counter = 1;
void viewQueue(){
    struct patient *temp = head;
    while(temp != NULL){
        printf("Patient %d\n", counter++);
        printf("Name   : %s\n", temp->Name);
        printf("Age    : %d\n", temp->umur);
        printf("Status : %s\n", temp->status);
        printf("------------------------------\n");
        temp = temp->Next;
    }
}

int main(){
    int choice;
    do
    {
        do
        {
            printf("Hospital Queue\n");
            printf("1. Input Patient\n");
            printf("2. View Queue\n");
            printf("3. Exit\n");
            printf(">> ");
            scanf("%d", &choice); getchar();
        } while (choice < 1 || choice > 3);
        
        if (choice == 1){
            inputQueue();
        } else if (choice == 2){
            viewQueue();
            counter = 1;
        }
    }  while (choice != 3);
    return 0;
}