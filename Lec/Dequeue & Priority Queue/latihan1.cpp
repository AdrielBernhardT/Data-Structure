#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patient {
    char Name[105];
    int umur;
    char status[5];
    int convert;
} inputan;

int counter = 0, max = 5;

struct patient* current = (struct patient*)malloc(sizeof(struct patient)*10);

void inputQueue(){
    if (counter == max){ // kalau counter itu penuh (= max)
        printf("Full Queue\n");
        return;
    }

    printf("Patient Data Input:\nName:\n>> ");
    scanf("%[^\n]", inputan.Name); getchar();
    printf("Age:\n>> ");
    scanf("%d", &inputan.umur); getchar();
    printf("Status:\n>> ");
    scanf("%s", inputan.status); getchar();

    if(strcmp(inputan.status, "Low") == 0){
        inputan.convert = 1; 
    } else if (strcmp(inputan.status, "Mid") == 0){
        inputan.convert = 2;
    } else if (strcmp(inputan.status, "High") == 0){
        inputan.convert = 3;
    }
    
    int index = counter-1;

    while(index>=0 && current[index].convert < inputan.convert){
        current[index+1] = current[index];
        index--;
    }
    current[index+1] = inputan; 
    counter++;
}

void viewQueue(){
    for (int i = 0; i < counter; i++){
        printf("Patient %d\n", i+1);
        printf("Name   : %s\n", current[i].Name);
        printf("Age    : %d\n", current[i].umur);
        printf("Status : %s\n", current[i].status);
        printf("------------------------------\n");
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
        }
    }  while (choice != 3);
    return 0;
}