#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Class Struct
struct Guest {
    char Name[105];
    char Type[10];
    int convert;
    Guest* Next;
    Guest* Prev;
} *head, *tail, *current;

int counter = 0; // Counter Guest

void Register(){
    current = (Guest*)malloc(sizeof(Guest));
    printf("Data Input\n");
    printf("Name : ");
    scanf("%[^\n]", current->Name); getchar();
    do{
        printf("Type [VVIP|VIP|Reg] : ");
        scanf("%s", current->Type); getchar();
        if(strcmp(current->Type,"VVIP") != 0 && strcmp(current->Type,"VIP") != 0 && strcmp(current->Type,"Reg") != 0){
            printf("Invalid Input\n");
        }
    } while(strcmp(current->Type,"VVIP") != 0 && strcmp(current->Type,"VIP") != 0 && strcmp(current->Type,"Reg") != 0);

    if(strcmp(current->Type,"VVIP") == 0){
        current->convert = 1;
    } else if(strcmp(current->Type,"VIP") == 0){
        current->convert = 2;
    } else {
        current->convert = 3;
    }

    current->Next = NULL;
    current->Prev = NULL;

    if(!head){
        head=tail=current;
    } else if (head->convert > current->convert){
        current->Next = head;
        head->Prev = current;
        head = current;
    } else if (tail->convert <= current->convert){
       tail->Next = current;
       current->Prev = tail;
       tail = current; 
    } else {
        Guest* temp = head;
        while(temp->convert <= current->convert){
            temp = temp->Next;
        }
        
        current->Next = temp;
        current->Prev = temp->Prev;
        temp->Prev = current;
        current->Prev->Next = current;
    }
    counter++;
}

void Call(int input){
    for(int i = 0; i < input; i++){
        if(!head){ // If ga ada Head lagi
            printf("No Visitor Left\n");
            break;
        }
        printf("%s, your room is ready\n", head->Name);

        // Pop Head
        Guest* temp = head;
        head = head->Next;
        if (head) { // Kalau masih ada Head
            head->Prev = NULL;
        } else { // Kalau ga ada head lagi
            tail = NULL;
        }
        free(temp);
        counter--;
    }
}

void Remove(char* Target){
    Guest* temp = head;

    while (temp && strcmp(temp->Name,Target) != 0){
        temp = temp->Next;
    }

    if (!temp){
        printf("Guest Not Found\n");
        return;
    }

    if(temp == head){
        head = head->Next;
        if (head){
            head->Prev = NULL;
        } else {
            tail = NULL;
        }
    } else {
        while (temp->Next && strcmp(temp->Next->Name,Target) != 0){
            temp = temp->Next;
        }
        Guest* temp2 = temp->Next;
        temp2->Prev = temp->Prev;
        temp->Prev->Next = temp2;

        free(temp);
    }
    counter--;
}

int main(){
    int choice;
    do{
        system("cls");
        printf("Hotel Guest Queue\n");
        printf("1. Register\n");
        printf("2. Call\n");
        printf("3. Remove\n");
        printf("4. Exit\n");
        do
        {
            printf(">> ");
            scanf("%d", &choice); getchar();
            if(choice < 1 || choice > 4){
                printf("Invalid input\n");
            }
            if(choice == 1){
                Register();
            } else if(choice == 2){
                int input;
                printf("Available Room: ");
                scanf("%d", &input); getchar();
                Call(input);
            } else if(choice == 3){
                char Target[105];
                printf("Cancel Order Name: ");
                scanf("%[^\n]", Target); getchar();
                Remove(Target);
            }
            system("pause");
        } while (choice < 1 || choice > 4);
        
    } while (choice != 4);

    return 0;
}