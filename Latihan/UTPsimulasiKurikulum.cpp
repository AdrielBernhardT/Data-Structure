#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>

// Define Size
#define max 100

// Struct
struct data{
    char name[35];
    char id[10];
    char title[55];
    char borrowingId[10];
    int duration;
    data *next;
} *head[max], *tail[max], *current;

// Validation
bool choiceVal(int choice){
    return choice >= 1 && choice <= 4;
}

bool isDigit(char chars){
    return chars >= '0' && chars <= '9';
}

bool nameVal(){
    return strlen(current->name) >= 3 && strlen(current->name) <= 30;
}

bool idVal(){
    return (strlen(current->id) == 9 && current->id[0] == 'L' && current->id[1] == 'I' && current->id[2] == 'B' && current->id[3] == '-' && isDigit(current->id[4]) && isDigit(current->id[5]) && isDigit(current->id[6]) && isDigit(current->id[7]) && isDigit(current->id[8]));
}

bool titleVal(){
    return strlen(current->title) >= 3 && strlen(current->title) <= 50;
}

bool durationVal(){
    return current->duration >= 1 && current->duration <= 30;
}

// hashing
int hash(char *borrowID){
    int key = ((borrowID[2]-'0')*100)+((current->borrowingId[3]-'0')*10)+(current->borrowingId[4]-'0');
    key*=key;

    char keyStr[10];
    sprintf(keyStr, "%d", key);
    int len = strlen(keyStr);
    if (len%2 == 0){
        key = ((keyStr[len/2 - 1] - '0') * 10) + (keyStr[len/2] - '0');
    } else {
        key = keyStr[len/2] - '0';
    }
    return key%max;
}

// Menu 1
void Borrow(){
    srand(time(NULL));
    current = (data*)malloc(sizeof(data));
    do{
        printf("Enter your full name: ");
        scanf("%[^\n]", current->name); getchar();
        if(!nameVal()){
            printf("Input must be 3-30 Characters\n");
        }
    } while(!nameVal());
    
    do{
        printf("Enter your library ID (format: LIB-xxxxx): ");
        scanf("%s", current->id); getchar();
        current->id[9] = '\0';
        if(!idVal()){
            printf("Input must be start with \"LIB-\" and followed exactly 5 digits\n");
        }
    } while(!idVal());
    
    do{
        printf("Enter the book title: ");
        scanf("%[^\n]", current->title); getchar();
        if(!titleVal()){
            printf("Input must be 3-50 Characters\n");
        }
    } while(!titleVal());

    do{
        printf("Enter borrowing duration (1-30 days): ");
        scanf("%d", &current->duration); getchar();
        if(!durationVal()){
            printf("Input must be 1-30 days\n");
        }
    } while(!durationVal());

    // borrowingId
    for(int i = 0; i < 5; i++){
        if(i < 2){
            current->borrowingId[i] = current->title[i];
        } else {
            current->borrowingId[i] = (rand()%10) + '0';
        }
    }
    current->borrowingId[1] += ('A'-'a');
    current->borrowingId[5] = '\0';
    current->next = NULL;

    // push
    int key = hash(current->borrowingId);
    if(!head[key]){
        head[key]=tail[key]=current;
    } else {
        tail[key]->next = current;
        tail[key] = current;
    }

    // Success Message
    printf("-------------------------------------\n");
    printf("     Book Borrowed Successfully!\n");
    printf("-------------------------------------\n");
    printf("Borrowing ID : %s\n", current->borrowingId);
    printf("Borrower Name: %s\n", current->name);
    printf("Library ID   : %s\n", current->id);
    printf("Book Title   : %s\n", current->title);
    printf("Duration     : %d\n", current->duration);
    printf("-------------------------------------\n");
}

// Menu 2
void View(){
    bool flag = false;
    for(int i = 0; i < max; i++){
        if(head[i]){
            flag = true;
            break;
        }
    }
    if (flag == false){
        printf("=====================================\n");
        printf("No books borrowed yet.\n");
        printf("=====================================\n");
    } else {
        printf("=====================================\n");
        printf("        Borrowed Books List\n");
        printf("=====================================\n");
        for(int i = 0; i < max; i++){
            if(head[i]){
                current = head[i];
                while(current){
                    printf("Borrowing ID : %s\n", current->borrowingId);
                    printf("Borrower Name: %s\n", current->name);
                    printf("Library ID   : %s\n", current->id);
                    printf("Book Title   : %s\n", current->title);
                    printf("Duration     : %d\n", current->duration);
                    printf("-------------------------------------\n");
                    current = current->next;
                }
            }
        }
    }
}

// Menu 3
void Return(){
    bool flag = false;
    for(int i = 0; i < max; i++){
        if(head[i]){
            flag = true;
            break;
        }
    }
    if (flag == false){
        printf("=====================================\n");
        printf("No books found.\n");
        printf("=====================================\n");
    } else {
        char search[10];
        printf("Enter Borrowing ID to return: ");
        scanf("%s", search); getchar();
        int key = hash(search);

        if(!head[key]){
            printf("Data not found\n");
            return;
        } 
  
        data* temp = head[key];
        while (temp && strcmp(temp->borrowingId,search)!=0){
            temp = temp->next;
        }

        // Pop
        if(temp){
            if(temp == head[key]){
                head[key] = head[key]->next;
                free(temp);
            } else {
                data *temp2 = head[key];
                while(temp2->next!=temp){
                    temp2 = temp2->next;
                }
                temp2->next = temp->next;
                free(temp);
                printf("--------------------------------\n");
                printf("Book Returned Successfully!\n");
                printf("--------------------------------\n");
                printf("Borrowing ID :  %s has been removed.\n", search);
                printf("--------------------------------\n");
            }
        }

    }
}

int main(){
    int choice;
    do{
        printf("=================================\n");
        printf("BookHaven Library Management\n");
        printf("=================================\n");
        printf("1. Borrow Book\n");
        printf("2. View Borrowed Book\n");
        printf("3. Return a Book\n");
        printf("4. Exit\n");
        printf("=================================\n");
        do{
            printf("Enter your choice: ");
            scanf("%d", &choice); getchar();
            if(!choiceVal(choice)){
                printf("Input must be 1-4\n");
            }
        } while(!choiceVal(choice));

        if(choice == 1){
            Borrow();
        } else if(choice == 2){
            View();
        } else if(choice == 3){
            Return();
        }
        system("pause");
        system("cls");
    } while (choice != 4);
    return 0;
}