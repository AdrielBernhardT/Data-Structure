#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    char Nama[15];
    struct Node *next;
} *head, *tail, *current;

void pushmid(){
    current = (struct Node*)malloc(sizeof(struct Node));
    printf("Input Nama: ");
    scanf("%[^\n]", current->Nama);getchar();
    current->next = NULL;
    if(!head){
        head=tail=current;
    } else if (strcmp(current->Nama, head->Nama) == 0){
        current->next = head;
        head = current;
    } else {
        struct Node *temp = head;
        while(strcmp(temp->next->Nama, current->Nama) < 0){
            temp = temp->next;
        }
    }
} 

void popmid(char target[]){
    if(head == NULL){
        return;
    }
    if (strcmp(head->Nama, target) == 0){ // Pop Head
        struct Node *temp = head;
        head = head->next;
        temp -> next = NULL;
        free(temp);
    } else { // Pop Mid
         Node *temp1 = head;
        Node *temp2 = head->next;
        while(strcmp(temp2->Nama, target) != 0){
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        temp1->next = temp2->next;
        temp2->next = NULL;
        free(temp2);
    }
}

int main(){
    // popmid("Budi");

    return 0;
}