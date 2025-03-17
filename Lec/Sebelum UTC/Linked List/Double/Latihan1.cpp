#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int nomor;                 // Nomor lagu (otomatis increment)
    char judul[100];           // Judul lagu
    struct Node* next;         // Pointer ke node berikutnya
    struct Node* prev;         // Pointer ke node sebelumnya
} Node;

Node* head = NULL; // Head dari list
Node* tail = NULL; // Tail dari list
Node* current = NULL; // Pointer untuk navigasi lagu
int counter = 1; // Counter untuk nomor otomatis

// Fungsi membuat node baru
Node* createNode(const char* judul) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->nomor = counter++; // Nomor otomatis increment
    strcpy(newNode->judul, judul); // Copy judul lagu
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Menambahkan lagu ke akhir list
void addSong(const char* judul) {
    Node* newNode = createNode(judul);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    printf("Lagu '%s' berhasil ditambahkan!\n", judul);
}

// Menampilkan daftar lagu
void showSongs() {
    if (!head) {
        printf("Daftar lagu kosong!\n");
        return;
    }
    Node* temp = head;
    printf("Daftar Lagu:\n");
    while (temp) {
        printf("%d. %s\n", temp->nomor, temp->judul);
        temp = temp->next;
    }
}

// Fitur next song
void nextSong() {
    if (!current) {
        printf("Tidak ada lagu yang sedang diputar!\n");
        return;
    }
    if (current->next) {
        current = current->next;
        printf("Memutar lagu berikutnya: %s\n", current->judul);
    } else {
        printf("Sudah di akhir daftar lagu!\n");
    }
}

// Fitur previous song
void prevSong() {
    if (!current) {
        printf("Tidak ada lagu yang sedang diputar!\n");
        return;
    }
    if (current->prev) {
        current = current->prev;
        printf("Memutar lagu sebelumnya: %s\n", current->judul);
    } else {
        printf("Sudah di awal daftar lagu!\n");
    }
}

// Mode loop
void playLoop() {
    if (!current) {
        printf("Tidak ada lagu yang sedang diputar!\n");
        return;
    }
    printf("Mode Loop Aktif: Memutar list berulang.\n");
    tail->next = head; // Menghubungkan tail ke head
    head->prev = tail; // Menghubungkan head ke tail
}

// Mode play once
void playOnce() {
    if (!current) {
        printf("Tidak ada lagu yang sedang diputar!\n");
        return;
    }
    printf("Mode Play Once: Memutar list sekali.\n", current->judul);
    tail->next = NULL; // Memutuskan hubungan tail ke head
    head->prev = NULL; // Memutuskan hubungan head ke tail
}

// Main program
int main() {
    int pilihan;
    char judul[100];
    printf("=== Aplikasi Musik dengan Double Linked List ===\n");

    do {
        printf("\nMenu:\n");
        printf("1. Tambahkan Lagu\n");
        printf("2. Tampilkan Daftar Lagu\n");
        printf("3. Putar Lagu Pertama\n");
        printf("4. Lagu Berikutnya\n");
        printf("5. Lagu Sebelumnya\n");
        printf("6. Mode Loop\n");
        printf("7. Mode Play Once\n");
        printf("8. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar(); // Membersihkan newline di buffer

        switch (pilihan) {
            case 1:
                printf("Masukkan judul lagu: ");
                fgets(judul, sizeof(judul), stdin);
                judul[strcspn(judul, "\n")] = 0; // Menghapus newline
                addSong(judul);
                break;

            case 2:
                showSongs();
                break;

            case 3:
                if (head) {
                    current = head;
                    printf("Memutar lagu: %s\n", current->judul);
                } else {
                    printf("Daftar lagu kosong!\n");
                }
                break;

            case 4:
                nextSong();
                break;

            case 5:
                prevSong();
                break;

            case 6:
                playLoop();
                break;

            case 7:
                playOnce();
                break;

            case 8:
                printf("Keluar dari aplikasi.\n");
                break;

            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 8);

    return 0;
}
