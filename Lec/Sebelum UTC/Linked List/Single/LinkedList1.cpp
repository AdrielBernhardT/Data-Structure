#include <stdio.h>
#include <stdlib.h>

// Definisi Node
struct Node {
    int data;
    struct Node* next;
};

// Fungsi untuk membuat node baru
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Fungsi rekursif untuk mencari data di Linked List
struct Node* searchNode(struct Node* head, int target) {
    // Basis: Jika node kosong, kembalikan NULL (tidak ditemukan)
    if (head == NULL) {
        return NULL;
    }

    // Jika data ditemukan, kembalikan pointer ke node tersebut
    if (head->data == target) {
        return head;
    }

    // Rekursi: Cari di node berikutnya
    return searchNode(head->next, target);
}

// Fungsi untuk mencetak Linked List
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

// Driver Program
int main() {
    // Membuat linked list
    struct Node* head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(40);

    // Cetak Linked List
    printf("Linked List: ");
    printList(head);

    // Cari node dengan nilai 30
    int target = 30;
    struct Node* result = searchNode(head, target);

    if (result != NULL) {
        printf("Node dengan data %d ditemukan!\n", result->data);
    } else {
        printf("Node dengan data %d tidak ditemukan.\n", target);
    }

    return 0;
}