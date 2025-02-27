#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_TABLE 105

int collision_count[MAX_TABLE] = {0};

struct Node {
    char Name[40];
    char Phone[15];
    char Email[40];
    Node *Next;
} *head[MAX_TABLE], *tail[MAX_TABLE], *current;

// Hash function sendiri buat masukin indikator ke berapanya
int hash(const char *input) {
    int ascii = 0;
    for (int i = 0; i < strlen(input); i++) {
        ascii += input[i];
    }

    char temp[20]; // store sum ASCII dalam bentuk string
    sprintf(temp, "%d", ascii);

    int len = strlen(temp);
    int mid_index = len / 2;

    if (len % 2 == 0) { // Jika panjang genap, ambil dua digit tengah
        int middle_value = (temp[mid_index - 1] - '0') * 10 + (temp[mid_index] - '0');
        return middle_value;
    } else { // Jika panjang ganjil, ambil satu digit tengah
        return temp[mid_index] - '0';
    }
}

// Kasih push ultimate
void push_ultimate(const char *name, const char *phone, const char *email) {
    current = (Node*)malloc(sizeof(Node));
    current->Next = NULL;

    int position = hash(name);

    strcpy(current->Name, name);
    strcpy(current->Phone, phone);
    strcpy(current->Email, email);

    if (!head[position]) {
        head[position] = tail[position] = current;
    } else if (strcmp(head[position]->Name, name) > 0) {
        current->Next = head[position];
        head[position] = current;
        collision_count[position]++;
    } else if (strcmp(tail[position]->Name, name) < 0) {
        tail[position]->Next = current;
        tail[position] = current;
        collision_count[position]++;
    } else {
        Node *temp = head[position];
        while (temp->Next && strcmp(temp->Next->Name, name) < 0) {
            temp = temp->Next;
        }
        current->Next = temp->Next;
        temp->Next = current;
        collision_count[position]++;
    }
}

// kasih pop ultimate
void pop_ultimate(const char *name) {
    int position = hash(name);

    if (!head[position]) {
        return;
    } else if (strcmp(head[position]->Name, name) == 0) {
        Node *temp = head[position];
        head[position] = head[position]->Next;
        free(temp);
    } else {
        Node *temp = head[position];
        while (temp->Next && strcmp(temp->Next->Name, name) != 0) {
            temp = temp->Next;
        }
        if (temp->Next) {
            Node *temp2 = temp->Next;
            temp->Next = temp2->Next;
            free(temp2);
        }
    }
}

// kasih search
void search(char *name) {
    int position = hash(name); // cari posisi

    if (!head[position]) { // jika tidak ada data
        printf("Data not found\n");
        return;
    }

    // searching
    Node *temp = head[position]; 
    while (temp && strcmp(temp->Name, name) != 0) { 
        temp = temp->Next;
    }

    if (temp) { // jika data ditemukan
        printf("Name: %s\n", temp->Name);
        printf("Phone: %s\n", temp->Phone);
        printf("Email: %s\n", temp->Email);
    } else {
        printf("Data not found\n");
    }
}

// kasih view
void view(){
    for (int i = 0; i < MAX_TABLE; i++){
        if (head[i]){ // jika ada data
            printf("Index %d Collision %d: ", i, collision_count[i]);
            current = head[i];
            while (current){ // print semua data
                printf("%s -> ", current->Name);
                current = current->Next;
            }
            printf("NULL\n");
        }
    }
    system("pause");
}

int main(){
    int choice = -1;
    do {
        system("cls");
        printf("Contacts\n");
        printf("1. Add Contact\n");
        printf("2. Delete Contact\n");
        printf("3. Search Contact\n");
        printf("4. View Contact\n");
        printf("0. Exit\n");
        do {
            printf(">> ");
            scanf("%d", &choice);
            getchar();
        } while (choice < 0 || choice > 4);

        char name[40], phone[15], email[40];
        switch (choice){
        case 1:
            do {
                printf("Input Name: ");
                scanf("%[^\n]", name);
                getchar();
            } while (strlen(name) > 40 || strlen(name) == 0);

            do {
                printf("Input Phone: ");
                scanf("%[^\n]", phone);
                getchar();
            } while (strlen(phone) > 15);

            do {
                printf("Input Email: ");
                scanf("%[^\n]", email);
                getchar();
                if (strlen(email) > 40 || strstr(email, "@gmail.com") == NULL){
                    printf("Must be less than 40 characters and contain '@gmail.com'\n");
                } 
            } while (strlen(email) > 40 || strstr(email, "@gmail.com") == NULL);

            push_ultimate(name, phone, email);

            break;
        case 2:
            do { 
                printf("Input Name: ");
                scanf("%[^\n]", name);
                getchar();
            } while (strlen(name) > 40 || strlen(name) == 0);
            pop_ultimate(name);
            break;
        case 3:
            do {
                printf("Input Name: ");
                scanf("%[^\n]", name);
                getchar();
            } while (strlen(name) > 40 || strlen(name) == 0);
            search(name);
            break;
        case 4:
            view();
            break;
        }
    } while (choice != 0);
    return 0;
}