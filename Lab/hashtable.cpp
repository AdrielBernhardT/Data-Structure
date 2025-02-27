#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_table 10

struct Node {
    char Name[40];
    Node* Next;
} *head[max_table], *tail[max_table], *current;

/*
Node *createNode(char input[]){
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->Name, input);
    newNode->Next = NULL;
    return newNode;
}
*/

int hash(const char *input){
    int ascii = 0;
    for (int i = 0; i < strlen(input); i++){
        ascii += input[i];
    }
    return ascii % max_table;
}

/*
void push(char *input){
    Node *newNode = createNode(input);
    int pos = hash(input);
    if (!head[pos]){
        head[pos] = tail = newNode;
    } else {
        tail->Next = newNode;
        tail = newNode;
    }
}
*/

void push_ultimate(const char *input){
    current = (Node*)malloc(sizeof(Node));
    current->Next = NULL;

    int position = hash(input);

    strcpy(current->Name, input);
    if (!head[position]){
        head[position]=tail[position]=current;
    } else if (strcmp(head[position]->Name, input) > 0){
        current->Next = head[position];
        head[position] = current;
    } else if (strcmp(tail[position]->Name, input) < 0){
        tail[position]->Next = current;
        tail[position] = current;
    } else {
        Node *temp = head[position];
        while (temp->Next && strcmp(temp->Next->Name, input) < 0){
            temp = temp->Next;
        }
        current->Next = temp->Next;
        temp->Next = current;
    }
}

void pop_ultimate(const char *input){
    int position = hash(input);

    if (!head[position]){
        return;
    } else if (strcmp(head[position]->Name, input) == 0){
        Node *temp = head[position];
        head[position] = head[position]->Next;
        free(temp);
    } else {
        Node *temp = head[position];
        while (temp->Next && strcmp(temp->Next->Name, input) != 0){
            temp = temp->Next;
        }
        if (temp->Next){
            Node *temp2 = temp->Next;
            temp->Next = temp2->Next;
            free(temp2);
        }
    }
}

void print(){
    for (int i = 0; i < max_table; i++){
        // if (head[i]){
            printf("Index %d: ", i);
            current = head[i];
            while (current){
                printf("%s -> ", current->Name);
                current = current->Next;
            }
            printf("NULL\n");
        // }
    }
}

int main(){
    // char inputan[40] = "Aldi";
    // push_ultimate(inputan);

    push_ultimate("Andi");
    push_ultimate("Budi");
    push_ultimate("Caca");
    push_ultimate("Dedi");
    push_ultimate("Euis");
    push_ultimate("Fafa");
    push_ultimate("Gaga");
    push_ultimate("Haha");
    push_ultimate("Ii");
    push_ultimate("Jaja");
    push_ultimate("Kaka");
    push_ultimate("Lili");
    push_ultimate("Mumu");
    push_ultimate("Nunu");
    push_ultimate("Opo");
    push_ultimate("Papa");
    push_ultimate("Qiqi");
    push_ultimate("Rara");
    push_ultimate("Sisi");
    push_ultimate("Tata");
    push_ultimate("Uu");
    push_ultimate("Vivi");
    push_ultimate("Wawa");
    push_ultimate("Xixi");
    push_ultimate("Yaya");
    push_ultimate("Zizi");
    print();

    pop_ultimate("Andi");
    pop_ultimate("Budi");
    pop_ultimate("Caca");
    pop_ultimate("Dedi");
    pop_ultimate("Euis");
    pop_ultimate("Fafa");
    pop_ultimate("Gaga");
    pop_ultimate("Haha");
    pop_ultimate("Ii");
    pop_ultimate("Jaja");
    pop_ultimate("Kaka");
    pop_ultimate("Lili");
    pop_ultimate("Mumu");
    pop_ultimate("Nunu");
    pop_ultimate("Opo");
    pop_ultimate("Papa");
    pop_ultimate("Qiqi");
    pop_ultimate("Rara");
    pop_ultimate("Sisi");
    pop_ultimate("Tata");
    pop_ultimate("Uu");
    pop_ultimate("Vivi");
    pop_ultimate("Wawa");
    pop_ultimate("Xixi");
    pop_ultimate("Yaya");
    pop_ultimate("Zizi");
    print();
    return 0;
}