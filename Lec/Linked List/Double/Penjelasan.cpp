#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    Node* Next;
    Node* prev;  // Menambahkan pointer prev untuk double linked list
} *head, *tail, *current;

void push_ultimate(int input) {
    current = (Node*)malloc(sizeof(Node)); // Mengalokasikan memori untuk node baru
    current->data = input; // Mengatur data untuk node baru
    current->Next = NULL; // Menginisialisasi pointer next ke NULL
    current->prev = NULL; // Menginisialisasi pointer prev ke NULL

    if (!head) { // Jika list kosong, atur head dan tail ke node baru
        head = tail = current;
    } else if (head->data > input) { // Sisipkan di awal jika input lebih kecil dari data head
        current->Next = head;
        head->prev = current;
        head = current;
    } else if (tail->data < input) { // Sisipkan di akhir jika input lebih besar dari data tail
        tail->Next = current;
        current->prev = tail;
        tail = current;
    } else { // Sisipkan di tengah
        Node *temp = head;
        while (temp->Next && temp->Next->data < input) { // Temukan posisi yang tepat untuk menyisipkan
            temp = temp->Next;
        }
        current->Next = temp->Next; // Atur next dari node baru
        if (temp->Next) {
            temp->Next->prev = current; // Atur prev dari node berikutnya
        }
        current->prev = temp; // Atur prev dari node baru
        temp->Next = current; // Atur next dari node sebelumnya
    }
}

void pop_ultimate(int input) {
    if (head == NULL) { // Jika list kosong, kembalikan
        return;
    }
    if (head->data == input) { // Jika node yang akan dihapus adalah head
        Node *temp = head; // Simpan node head
        head = head->Next; // Pindahkan head ke node berikutnya
        if (head) {
            head->prev = NULL; // Atur prev dari head baru ke NULL
        } else {
            tail = NULL;  // Jika list menjadi kosong, atur tail ke NULL
        }
        free(temp); // Bebaskan node head lama
    } else {
        Node *temp1 = head, *temp2 = head->Next;
        while (temp2 && temp2->data != input) { // Temukan node yang akan dihapus
            temp1 = temp1->Next;
            temp2 = temp2->Next;
        }
        if (temp2 && temp2->data == input) { // Jika node ditemukan
            temp1->Next = temp2->Next; // Atur next dari node sebelumnya
            if (temp2->Next) {
                temp2->Next->prev = temp1; // Atur prev dari node berikutnya
            } else {
                tail = temp1;  // Jika node yang akan dihapus adalah tail, perbarui tail
            }
            free(temp2); // Bebaskan node yang akan dihapus
        }
    }
}

int main(){


    return 0;
}