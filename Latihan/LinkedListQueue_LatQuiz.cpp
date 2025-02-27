#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct Visitor {
    char Name[105];
    char Type[25];
    int convert;
    Visitor* Next;
    Visitor* Prev;
} *head, *tail, *current;

int counter = 0;

void Register(){
    current = (struct Visitor*)malloc(sizeof(struct Visitor));
    printf("Visitor Data Input:\nName:\n>> ");
    scanf("%[^\n]", current->Name); getchar();
    do{
        printf("Type: ");
        scanf("%s", current->Type); getchar();
        if (strcmp(current->Type, "FAST_TRACK") != 0 && strcmp(current->Type, "REGULER") != 0){
            printf("Invalid input\n");
        }
    } while (strcmp(current->Type, "FAST_TRACK") != 0 && strcmp(current->Type, "REGULER") != 0);

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
    } else if (head->convert < current->convert){
        head->Prev = current;
        current->Next = head;
        head = current;
    } else if (tail->convert > current->convert){
        tail->Next = current;
        current->Prev = tail;
        tail = current;
    }else {
        struct Visitor *temp = head;
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
        struct Visitor* temp = head;
        head = head->Next;
        if (head) {
            head->Prev = NULL;
        } else {
            tail = NULL;
        }
        free(temp);
    }
}

void Remove(char *nama){
    struct Visitor *temp = head;
    while (temp && strcmp(temp->Name, nama) != 0)
    {
        temp = temp->Next;
    }
    if (!temp){
        printf("Visitor not found\n");
        return;
    }
    if (temp == head){
        head = head->Next;
        if (head){
            head->Prev = NULL;
        } else {
            tail = NULL;
        }
    } else if (temp == tail){
        tail = tail->Prev;
        tail->Next = NULL;
    } else {
        temp->Prev->Next = temp->Next;
        temp->Next->Prev = temp->Prev;
    }
    free(temp);
    counter--;
}


int main(){
    int n;
    char nama[101];
    do {
        system("cls");

        printf("Istana Boneka\n");
        printf("1. Register\n");
        printf("2. Call\n");
        printf("3. Remove\n");
        printf("4. Exit\n");

        do {
            printf("Choose: ");
            scanf("%d", &n); getchar();
            if (n < 1 || n > 3) {
                printf("Invalid input\n");
            }
        } while (n < 1 || n > 4);

        if (n == 1) {
            Register();
        } else if (n == 2) {
            Call();
        } else if (n == 3) {
            scanf("%s", nama); getchar();
            Remove(nama);
        }

        system("pause");
    } while (n != 4);

    return 0;
}