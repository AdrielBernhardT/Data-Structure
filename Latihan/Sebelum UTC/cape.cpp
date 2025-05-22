#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct Queue {
    char Name[105];
    char Type[25];
    int convert;
    Queue* Next;
    Queue* Prev;
} *head, *tail, *current;

int counter = 0;

void Register(){
    current = (struct Queue*)malloc(sizeof(struct Queue));
    printf("Visitor Data Input:\nName:\n>> ");
    scanf("%[^\n]", current->Name); getchar();
    do
    {
        printf("Type:\n>> ");
        scanf("%s", current->Type); getchar();
    } while (strcmp(current->Type, "FAST_TRACK") != 0 && strcmp(current->Type, "REGULAR") != 0);

    printf("%s\n", current->Name);
    printf("%s\n", current->Type);
    
    if(strcmp(current->Type, "FAST_TRACK") == 0){
        current->convert = 1; 
    } else {
        current->convert = 2;
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
        struct Queue *temp = head;
        while (temp->Next->convert >= current->convert)
        {
            temp = temp->Next;
        }
        current->Next = temp->Next;
        current->Prev = temp;
        temp->Next->Prev = current;
        temp->Next = current;
    }
    counter++;
}

void Call(){
    for(int i = 0; i < 4; i++){
        if(!head){
            printf("No visitor left\n");
            break;
        }
        printf("%s ", head->Name);
        struct Queue* temp = head;
        head = head->Next;
        if (head) {
            head->Prev = NULL;
        } else {
            tail = NULL;
        }
        free(temp);
    }
}

int main(){

    return 0;
}