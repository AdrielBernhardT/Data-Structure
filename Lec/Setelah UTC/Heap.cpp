#include <stdio.h>
#define max 100

// Struktur data MinHeap
struct MinHeap{
    int size;        // Menyimpan jumlah elemen saat ini dalam heap
    int arr[max];    // Array penyimpan elemen heap
};

// Fungsi untuk menukar dua elemen
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Mengembalikan indeks parent dari elemen ke-i
int parent(int i){
    return (i - 1) / 2;
}

// Mengembalikan indeks anak kiri dari elemen ke-i
int leftChild(int i){
    return (2 * i + 1);
}

// Mengembalikan indeks anak kanan dari elemen ke-i
int rightChild(int i){
    return (2 * i + 2);
}

// Menyisipkan elemen baru ke dalam MinHeap
void insert(MinHeap* heap, int value){
    // Cek apakah heap sudah penuh
    if(heap->size >= max){
        printf("Full");
        return;
    }

    // Tempatkan elemen di posisi paling akhir
    int i = heap->size;
    heap->arr[i] = value;
    heap->size++;

    // Lakukan proses upheap (heapify-up) agar tetap memenuhi sifat MinHeap
    while(i != 0 && heap->arr[parent(i)] > heap->arr[i]){
        swap(&heap->arr[parent(i)], &heap->arr[i]); // Tukar dengan parent jika lebih kecil
        i = parent(i); // Lanjutkan ke atas
    }
}

// Fungsi untuk menurunkan elemen ke posisi yang sesuai dalam heap (heapify-down)
void DownHeap(MinHeap* heap, int i){
    int smallest = i;                     // Asumsikan saat ini adalah yang terkecil
    int left = leftChild(i);              // Anak kiri
    int right = rightChild(i);            // Anak kanan

    // Cek apakah anak kiri lebih kecil
    if(left < heap->size && heap->arr[left] < heap->arr[smallest]){
        smallest = left;
    }
    // Cek apakah anak kanan lebih kecil
    if(right < heap->size && heap->arr[right] < heap->arr[smallest]){
        smallest = right;
    }

    // Jika ditemukan anak yang lebih kecil, tukar dan lanjutkan rekursif
    if(smallest != i){
        swap(&heap->arr[i], &heap->arr[smallest]);
        DownHeap(heap, smallest);
    }
}

// Menghapus dan mengembalikan elemen terkecil (root) dari MinHeap
int extract(MinHeap* heap){
    // Cek jika heap kosong
    if(heap->size <= 0){
        printf("Empty");
        return -1;
    }

    int root = heap->arr[0];                         // Ambil nilai minimum (root)
    heap->arr[0] = heap->arr[heap->size - 1];        // Pindahkan elemen terakhir ke root
    heap->size--;                                    // Kurangi ukuran heap

    DownHeap(heap, 0);                               // Perbaiki heap dari atas ke bawah
    return root;
}

// Menampilkan isi MinHeap
void printHeap(MinHeap* heap){
    for(int i = 0; i < heap->size; i++){
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

// Fungsi utama
int main(){
    MinHeap heap;
    heap.size = 0; // Inisialisasi heap kosong

    // Menyisipkan beberapa elemen ke dalam heap
    insert(&heap, 10);
    insert(&heap, 5);
    insert(&heap, 20);
    insert(&heap, 3);
    
    // Cetak isi heap setelah penyisipan
    printf("Heap after insertions: ");
    printHeap(&heap);

    // Hapus elemen terkecil (root) dan cetak heap setelahnya
    extract(&heap);
    printf("Heap after extraction: ");
    printHeap(&heap);
}
